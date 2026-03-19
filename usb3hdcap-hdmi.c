// SPDX-License-Identifier: GPL-2.0
/*
 * USB3HDCAP HDMI init - MST3367 setup, signal detection, CSC
 */

#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/usb.h>
#include <linux/v4l2-dv-timings.h>

#include "usb3hdcap.h"

/* ------------------------------------------------------------------ */
/* Component scaler mode table                                        */
/* ------------------------------------------------------------------ */

struct component_mode {
	int vtotal_min, vtotal_max;
	int width, height;
	int refresh_rate;
	int interlaced;
	/* MST3367 bank 0 scaler registers */
	u8 reg_03, reg_05, reg_06, reg_07;
	u8 reg_1e, reg_1f;
	u16 scaler_htotal;
	u16 hde_off;
	u8 vde_off;
	/* V4L2: SD interlaced modes use std, HD modes use timings */
	v4l2_std_id std;
	struct v4l2_dv_timings timings;
};

/*
 * Values from Windows driver table $140303810
 * TODO: add 50Hz variants
 * 
 * The hardware supports 240p over component (one of the great things about
 * this card), but the Windows driver doesn't attempt to distinguish. I
 * won't either
 */
static const struct component_mode component_modes[] = {
	/* 480i */
	{  250,  275,   720,  240, 60, 1, 0x08,0x08,0x08,0x18, 0x44,0x04, 0x35a, 0x76, 0x12,
	   V4L2_STD_525_60 },
	/* 576i */
	{  300,  320,   720,  288, 50, 1, 0x08,0x08,0x08,0x18, 0x44,0x04, 0x360, 0x83, 0x16,
	   V4L2_STD_625_50 },
	/* 480p */
	{  515,  535,   720,  480, 60, 0, 0x20,0x08,0x08,0x18, 0x33,0x03, 0x35a, 0x79, 0x24,
	   0, V4L2_DV_BT_CEA_720X480P59_94 },
	/* 1080i */
	{  555,  585,  1920,  540, 60, 1, 0x58,0x38,0x20,0x30, 0x11,0x01, 0x898, 0xeb, 0x14,
	   0, V4L2_DV_BT_CEA_1920X1080I60 },
	/* 576p */
	{  615,  635,   720,  576, 50, 0, 0x18,0x08,0x08,0x18, 0x33,0x03, 0x360, 0x83, 0x2c,
	   0, V4L2_DV_BT_CEA_720X576P50 },
	/* 720p */
	{  740,  760,  1280,  720, 60, 0, 0x58,0x38,0x20,0x30, 0x11,0x01, 0x672,0x12b, 0x19,
	   0, V4L2_DV_BT_CEA_1280X720P60 },
	/* 1080p */
	{ 1115, 1135,  1920, 1080, 60, 0, 0xe8,0x38,0x30,0xa0, 0x00,0x00, 0x898, 0xc1, 0x29,
	   0, V4L2_DV_BT_CEA_1920X1080P60 },
};

/*
 * Known CEA timing table - maps (htotal, vtotal, hactive) to full
 * v4l2_dv_timings.  HD htotal = standard * 1.5 (MST3367 counter rate).
 * 1080p30 omitted: same htotal/vtotal as 1080p60, can't distinguish.
 */
struct hdmi_std {
	int htotal_min, htotal_max;
	int vtotal_min, vtotal_max;
	int hactive;
	struct v4l2_dv_timings timings;
};

static const struct hdmi_std hdmi_stds[] = {
	/*  htotal      vtotal     ha */
	{  790,  810,  520,  530,  640, V4L2_DV_BT_CEA_640X480P59_94 },
	{  848,  868,  520,  530,  720, V4L2_DV_BT_CEA_720X480P59_94 },
	{  854,  874,  620,  630,  720, V4L2_DV_BT_CEA_720X576P50 },
	{ 2960, 2980,  745,  755, 1280, V4L2_DV_BT_CEA_1280X720P50 },
	{ 2465, 2485,  745,  755, 1280, V4L2_DV_BT_CEA_1280X720P60 },
	/* not sure about this one. it matches the timings for 30, but my laptop
	   claims to be outputting 60... */
	{ 2740, 2760, 1120, 1130, 1920, V4L2_DV_BT_CEA_1920X1080P30 },
	{ 3950, 3970, 1120, 1130, 1920, V4L2_DV_BT_CEA_1920X1080P50 },
	{ 2190, 2210, 1120, 1130, 1920, V4L2_DV_BT_CEA_1920X1080P60 },
	{ 3290, 3310, 1120, 1130, 1920, V4L2_DV_BT_CEA_1920X1080P60 },
};

/* ------------------------------------------------------------------ */
/* MST3367 bank select helper                                         */
/* ------------------------------------------------------------------ */

static int mst_bank(struct usb3hdcap *hdcap, int bank)
{
	if (hdcap->mst_current_bank == bank)
		return 0;
	hdcap->mst_current_bank = bank;
	return u3hc_i2c_write(hdcap, ADDR_MST3367, 0x00, bank);
}

/* ------------------------------------------------------------------ */
/* MST3367 register configuration                                     */
/* ------------------------------------------------------------------ */

static void mst3367_config(struct usb3hdcap *hdcap)
{
	/*
	 * Largely based on mst3367-drv.c by Steven Toth and Ghidra decompilation
	 * of the Windows x64 driver
	 */

	/* Bank 0 initial config */
	mst_bank(hdcap, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x51, 0x80);
	//u3hc_i2c_write(hdcap, ADDR_MST3367, 0x13, 0x08);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb7, 0x02);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x41, 0x6f);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb8, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb0, 0x14);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xae, 0x04);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xad, 0x05);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb1, 0xc0);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb2, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb3, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb4, 0x55);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb4, 0x54);

	/* Bank 1: TMDS/HDCP */
	mst_bank(hdcap, 0x01);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x0f, 0x02);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x16, 0x30);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x17, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x18, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x19, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1a, 0x50);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x2a, 0x07);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x24, 0x40);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x30, 0x80);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x31, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x32, 0x00);

	/* Bank 2: video/audio config */
	mst_bank(hdcap, 0x02);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x08, 0x03);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x01, 0x61);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x02, 0xf5);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x03, 0x02);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x04, 0x01);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x05, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x06, 0x08);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1c, 0x1a);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1d, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1e, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1f, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x25, 0xa2);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x07, 0x04);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x17, 0xc0);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x19, 0xff);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1a, 0xff);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1b, 0xfc);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x20, 0x00);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x21, 0xfc, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x22, 0x26);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x27, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x2e, 0xa1);

	/* HDCP reset + PLL */
	mst_bank(hdcap, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xab, 0x15);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xac, 0x15);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb8, 0x10);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb8, 0x00);

	mst_bank(hdcap, 0x02);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x07, 0xf4); /* PLL reset */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x07, 0x04); /* PLL run */

	/* HDMI port select (overridden for component later) */
	mst_bank(hdcap, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x51, 0x81);

	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb7, 0x00);

	/* FUN_140249ec8, absolutely no idea what this does */
	mst_bank(hdcap, 0x02);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x01, 0x0f, 0x60);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x04, 0xff, 0x01);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x06, 0x08);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x09, 0xff, 0x20);

	mst_bank(hdcap, 0x00);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x54, 0xef, 0x00); /* clear bit 4 */
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0xac, 0xff, 0x80); /* set bit 7 */
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x00, 0xff, 0x80);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0xce, 0xff, 0x80); /* set bit 7 */
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0xcf, 0xfa, 0x02); /* clear bits 0,2; set bit 1 */

	/*
		8c28 is "CustomCompanyEndoCamProperty" (0 in my registry)
		7674 is "CustomAnalogVideoInputBandwidthProperty" (1 on my machine)
	    if (*(int *)(param_1 + 0x8c28) == 0) {
			uVar1 = *(uint *)(param_1 + 0x7674);
			local_18 = 0x3040006;
			uVar2 = (ulonglong)uVar1 / 6;
			local_14 = 0x107;
			bVar5 = read_mst(param_1,CONCAT71((int7)(uVar2 >> 8),0x80),0xd0);
			bVar4 = read_mst(param_1,0x80,0xcf);
			bVar3 = *(byte *)((longlong)&local_18 + (ulonglong)(uVar1 + (int)uVar2 * -6));
			bVar4 = bVar3 << 7 | bVar4 & 0x7f;
			bVar5 = (bVar3 >> 1 ^ bVar5) & 3 ^ bVar5;
	    }
		... which has this effect:
	*/
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0xd0, 0xfc, 0x00);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0xcf, 0x7f, 0x00);

	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x00, 0x7f, 0x00);
	mst_bank(hdcap, 0x00);
}

/* ------------------------------------------------------------------ */
/* CPLD init + poll helper                                            */
/* ------------------------------------------------------------------ */

static void cpld_init(struct usb3hdcap *hdcap, u8 mux_val)
{
	int k, status;

	/*
	  	cVar3 = i2c_read(param_1,0x98,0x3b,0);
		if (cVar3 != '\0') {
			uVar5 = *(uint *)(param_1 + 0x6840);
			if ((uVar5 == 2) || (uVar5 == 3)) {
				local_res8[0] = -0x80;
				i2c_write(param_1,0x98,0x3b,local_res8,1);
				uVar5 = *(uint *)(param_1 + 0x6840);
			}
			if (uVar5 < 2) {
				local_res8[0] = '\x02';
				i2c_write(param_1,0x98,0x3b,local_res8,1);
			}
		}
	*/

	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x3b, mux_val);

	/*
		local_res8[0] = '\x05';
		i2c_write(param_1,0x98,0x20,local_res8,1);
		cVar3 = FUN_140226fc4(param_1);
		local_res8[0] = '\x01';
		i2c_write(param_1,0x98,0,local_res8,1);
		local_res8[0] = (-(cVar3 != '\0') & 0xfeU) - 2;
		i2c_write(param_1,0x98,0x10,local_res8,1);
	*/
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x20, 0x05);
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x00, 0x01);

	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x10, hdcap->has_mcu ? 0xfc : 0xfe);

	for (k = 0; k < 50; k++) {
		status = u3hc_i2c_read(hdcap, ADDR_CPLD, 0x01);
		if (status >= 0x03)
			break;
		msleep(20);
	}

	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x01, 0x02);
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x11, 0xfc);
}

/* ------------------------------------------------------------------ */
/* CSC matrix                                                         */
/* Component YPbPr differs from HDMI in 5 registers.                  */
/* ------------------------------------------------------------------ */

static void mst3367_identity_csc(struct usb3hdcap *hdcap)
{
	bool comp = (hdcap->input == INPUT_COMPONENT);
	u8 old_ab;

	mst_bank(hdcap, 0x00);

	/*
		bVar3 = read_mst(param_1,0,0xab);
		send_mst(param_1,0,0xab,bVar3 & 0x7f | 0x80);
  	*/
	u3hc_i2c_rmw_get_old(hdcap, ADDR_MST3367, 0xab, 0x7f, 0x80, &old_ab);

	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x90, 0x15);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x91, 0x15);
	/*
	  	iVar1 = *(int *)(lVar2 + 0x60);
		if (*(int *)(lVar2 + 0x5c) == 1) {
			cVar5 = (-(iVar1 != 0) & 0x11U) + 0x55;
		}
		else {
			cVar5 = (-(iVar1 != 0) & 0x22U) + 0x40;
		}
		send_mst(param_1,0,0x92,cVar5);
	*/
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x92, comp ? 0x66 : 0x62);

	/* start from FUN_140249474 */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xac, comp ? 0x15 : 0x95);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xad, 0x05);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1e, 0x11);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1f, 0x01);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x9c, comp ? 0x00 : 0x3f);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x9b, 0x10);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x96, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x95, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xa2, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xa1, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x9a, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x99, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x94, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x93, 0x10);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xa0, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x9f, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x9e, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x9d, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x98, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x97, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xa4, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xa3, 0x10);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xa6, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xa5, 0x20);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xa8, comp ? 0x80 : 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xa7, comp ? 0x03 : 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xaa, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xa9, 0x20);
	/* end from FUN_140249474 */

	/*
		bVar4 = read_mst(param_1,0,0xb0);
		send_mst(param_1,0,0xb0,bVar4 & 0xc2 | 0x21);
		send_mst(param_1,0,0xab,bVar3 & 0x7f);
  	*/
	/* 
		from hdcapm driver:
		0x25 = RX_OUTPUT_YUV422 / 10.BITS / EXTERNAL SYNC,
		0x21 = RX_OUTPUT_YUV422 / 08.BITS / EMBEDDED SYNC,
		0x24 = RX_OUTPUT_YUV422 / 10.BITS / EXTERNAL SYNC,
		0x20 = RX_OUTPUT_YUV422 / 08.BITS / EXTERNAL SYNC
	*/
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0xb0, 0xc2, 0x21);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xab, old_ab & 0x7f);

	/* some kind of output enable */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb3, 0x00);

	mst_bank(hdcap, 0x02);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x27, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x20, 0x00);
}

/* ------------------------------------------------------------------ */
/* Signal detection polling                                           */
/* ------------------------------------------------------------------ */

static const struct v4l2_dv_timings *match_hdmi_timing(
	int htotal,
	int vtotal,
	int hactive)
{
	int k;

	for (k = 0; k < ARRAY_SIZE(hdmi_stds); k++) {
		const struct hdmi_std *s = &hdmi_stds[k];

		if (htotal < s->htotal_min || htotal > s->htotal_max)
			continue;
		if (vtotal < s->vtotal_min || vtotal > s->vtotal_max)
			continue;
		if (hactive != s->hactive)
			continue;
		return &s->timings;
	}
	return NULL;
}

static int hdmi_poll_signal(struct usb3hdcap *hdcap)
{
	int k, status;

	vendor_out(hdcap, REQ_STREAM, 0x0000, 0, NULL, 0);

	for (k = 0; k < 100; k++) {
		mst_bank(hdcap, 0x00);
		status = u3hc_i2c_read(hdcap, ADDR_MST3367, 0x55);
		if (status < 0) {
			msleep(100);
			continue;
		}

		if (k % 10 == 0)
			dev_info(hdcap->dev,
				"HDMI signal poll[%d]: lock=0x%02x\n",
				k, status);

		if (status == 0x7f) {
			const struct v4l2_dv_timings *std;
			int htotal, vtotal, hactive;
			int pll;

			htotal = (u3hc_i2c_read(hdcap, ADDR_MST3367, 0x6a) << 8 |
				  u3hc_i2c_read(hdcap, ADDR_MST3367, 0x6b)) & 0xfff;
			vtotal = (u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5b) << 8 |
				  u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5c)) & 0x7ff;

			mst_bank(hdcap, 0x02);
			hactive = (u3hc_i2c_read(hdcap, ADDR_MST3367, 0x29) << 8 |
				   u3hc_i2c_read(hdcap, ADDR_MST3367, 0x28)) & 0x1fff;

			dev_info(hdcap->dev,
				"HDMI locked: htotal=%d vtotal=%d hactive=%d\n",
				htotal, vtotal, hactive);

			std = match_hdmi_timing(htotal, vtotal, hactive);
			if (!std) {
				dev_err(hdcap->dev,
					"unsupported HDMI timing: htotal=%d vtotal=%d hactive=%d\n",
					htotal, vtotal, hactive);
				return -ERANGE;
			}
			hdcap->detected_timings = *std;
			hdcap->width = std->bt.width;
			hdcap->height = std->bt.height;
			hdcap->bpl = hdcap->width * 2;
			hdcap->interlaced = 0;

			/* "DISABLE AUTO POSITION" idk why windows does this here */
			mst_bank(hdcap, 0x00);
			u3hc_i2c_write(hdcap, ADDR_MST3367, 0xe2, 0x00);

			/* PLL re-toggle */
			mst_bank(hdcap, 0x02);
			pll = u3hc_i2c_read(hdcap, ADDR_MST3367, 0x07);
			u3hc_i2c_write(hdcap, ADDR_MST3367, 0x07, pll | 0x10);
			u3hc_i2c_write(hdcap, ADDR_MST3367, 0x07, pll & ~0x10);

			return 0;
		}

		/* Not locked yet */
		u3hc_i2c_write(hdcap, ADDR_MST3367, 0xe2, 0x00);
		msleep(100);
	}

	dev_err(hdcap->dev, "No HDMI signal lock after 10s\n");
	return -ETIMEDOUT;
}

/* ------------------------------------------------------------------ */
/* ADC front-end config (component/VGA only)                          */
/* ------------------------------------------------------------------ */

static void mst3367_adc_config(struct usb3hdcap *hdcap)
{
	/* not sure what any of these do other than only being used in the 
	   analog path */
	mst_bank(hdcap, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x00, 0x80);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x24, 0xc0);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x00, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x21, 0x01);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x04, 0x00);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x10, 0xdf, 0x40);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x11, 0x2d);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x20, 0xc0);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x21, 0x04);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x0e, 0xff, 0x30);
}

static const struct component_mode *match_component_mode(int vtotal)
{
	int k;

	for (k = 0; k < ARRAY_SIZE(component_modes); k++) {
		const struct component_mode *m = &component_modes[k];

		if (vtotal < m->vtotal_min || vtotal > m->vtotal_max)
			continue;
		return m;
	}
	return NULL;
}

/* ------------------------------------------------------------------ */
/* Component scaler register write                                    */
/* ------------------------------------------------------------------ */

static void component_write_scaler(
	struct usb3hdcap *hdcap,
	const struct component_mode *m)
{
	int ht = m->scaler_htotal - 1;
	int is_720_low_rr = m->width == 1280 && m->height == 720 
			&& (m->refresh_rate == 24 
				|| m->refresh_rate == 25 
				|| m->refresh_rate == 30);

	mst_bank(hdcap, 0x00);

	/* edge case from windows driver */
	/*
		if (((*(int *)(uVar30 + 0x30) == 0x500) && (*(int *)(uVar30 + 0x34) == 0x2d0)) &&
           ((*(int *)(uVar30 + 0x38) == 0x1e ||
            ((*(int *)(uVar30 + 0x38) == 0x19 || (*(int *)(uVar30 + 0x38) == 0x18)))))) {
          uVar37 = 0;
        }
        else {
          uVar37 = 4;
        }
        send_mst(param_1,0,0x12,uVar37);
	*/
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x12, is_720_low_rr ? 0x00 : 0x04);


	/* filter/gain */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x03, m->reg_03);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x05, m->reg_05);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x06, m->reg_06);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x07, m->reg_07);

	/* cutoff */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x08, 0xa0);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x09, 0xc0);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x0a, 0xa0);

	/* gain */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x0b, 0x80);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x0c, 0x60);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x0d, 0x80);

	/* no idea */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x18, 0x10);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x19, 0x10);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1a, 0x10);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1b, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1c, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1d, 0x00);

	/* output timing */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x01, ht >> 4);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x02, (ht & 0x0f) << 4);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1e, m->reg_1e);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1f, m->reg_1f);

	/* output data enable start pos after sync */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x80, (m->hde_off >> 8) & 0x0f);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x81, m->hde_off & 0xff);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x82, (m->width >> 8) & 0xff);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x83, m->width & 0xff);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x84, m->vde_off);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x85,
		  ((m->height >> 8) & 0x0f) | (m->interlaced ? 0x20 : 0x00));
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x86, m->height & 0xff);

	/* sync */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x2d, 0x11);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x2e, 0x11);
	/* reg 0x39 = reg_05 + reg_06 - 0x78 (from decompiled code) */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x39, (u8) (m->reg_05 + m->reg_06 - 0x78));
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x2c, 0x9d);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x3a, 0x0c);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x3b, 0x08);

	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x10, 0xfa, 0x05); /* set bits 0,2 */
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x0f, 0xff, 0x20); /* set bit 5 */
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x17, 0xff, 0x02); /* set bit 1 */
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x2f, 0xff, 0x02); /* set bit 1 */
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x60, 0xfb, 0x00); /* clear bit 2 */
}

/* ------------------------------------------------------------------ */
/* Component ADC signal polling                                       */
/* ------------------------------------------------------------------ */

static int component_poll_signal(
	struct usb3hdcap *hdcap,
	const struct component_mode **detected)
{
	const struct component_mode *mode;
	int k, status, vtotal, htotal;
	int signal_count = 0;

	vendor_out(hdcap, REQ_STREAM, 0x0000, 0, NULL, 0);

	/*
	 * Signal detection per decompiled Windows driver:
	 *   0x14 & 0x90 == 0x90: fully synced
	 *   0x14 & 0x90 == 0x80: H lock
	 */
	for (k = 0; k < 100; k++) {
		int signal_type;

		mst_bank(hdcap, 0x00);

		/* trigger timing measurement? */
		u3hc_i2c_write(hdcap, ADDR_MST3367, 0x0e, 0x40);

		status = u3hc_i2c_read(hdcap, ADDR_MST3367, 0x14);
		/* needed ? */
		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x15);

		/* Check signal presence from 0x14 bits 7,4 */
		signal_type = status & 0x90;
		if (signal_type == 0x90 || signal_type == 0x80 ||
		    (signal_type == 0x00 && (status & 0x02)))
			signal_count++;
		else
			signal_count = 0;

		/* Read H timing */
		htotal = ((u3hc_i2c_read(hdcap, ADDR_MST3367, 0x57) & 0x3f) << 8) |
			  u3hc_i2c_read(hdcap, ADDR_MST3367, 0x58);

		/* scale ADC sample rate to htotal like Windows driver */
		if (htotal > 0)
			u3hc_i2c_write(hdcap, ADDR_MST3367, 0x11,
				  (htotal < 0x401 ? 0x400 : htotal) >> 7);

		/* Read V timing, idk if this is actually needed? */
		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x59);
		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5a);

		/* Read Vtotal */
		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5b);
		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5c);

		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5d);
		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5e);
		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5f);

		/* PLL status */
		mst_bank(hdcap, 0x02);
		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x11);
		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x12);
		u3hc_i2c_write(hdcap, ADDR_MST3367, 0x20, 0x00);

		if (k % 10 == 0)
			dev_info(hdcap->dev,
				"component poll[%d]: 0x14=0x%02x count=%d\n",
				k, status, signal_count);

		if (signal_count < 3) {
			msleep(100);
			continue;
		}

		/* Signal stable - read vtotal and determine format */
		mst_bank(hdcap, 0x00);
		vtotal = ((u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5b) & 0x07) << 8) |
			  u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5c);

		dev_info(hdcap->dev,
			"component locked: vtotal=%d htotal=%d 0x14=0x%02x\n",
			vtotal, htotal, status);

		mode = match_component_mode(vtotal);
		if (!mode) {
			dev_err(hdcap->dev,
				"unsupported component timing: vtotal=%d\n",
				vtotal);
			return -ERANGE;
		}
		hdcap->width = mode->width;
		hdcap->height = mode->height;
		hdcap->interlaced = mode->interlaced;
		hdcap->bpl = hdcap->width * 2;
		hdcap->detected_timings = mode->timings;
		hdcap->std = mode->std;
		*detected = mode;
		return 0;
	}

	dev_err(hdcap->dev, "No component signal lock after 10s\n");
	return -ETIMEDOUT;
}

/* ------------------------------------------------------------------ */
/* Main HDMI init entry point                                         */
/* ------------------------------------------------------------------ */

int usb3hdcap_hdmi_init(struct usb3hdcap *hdcap)
{
	int ret;

	hdcap->mst_current_bank = -1;

	mst3367_config(hdcap);

	/* TW9900 power-down */
	u3hc_i2c_write(hdcap, ADDR_TW9900, 0x06, 0x0e);
	u3hc_i2c_write(hdcap, ADDR_TW9900, 0x1a, 0x40);

	/* CPLD init with HDMI input mux */
	cpld_init(hdcap, 0x02);

	u3hc_i2c_read(hdcap, ADDR_CPLD, 0x20);
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x20, 0x05);

	/* probably not needed */
	u3hc_i2c_read(hdcap, ADDR_CPLD, 0x20);
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x20, 0x05);

	ret = hdmi_poll_signal(hdcap);
	if (ret < 0)
		return ret;

	/* need a different matrix for other sources, captures from windows */
	/* confirm this. For example on Nintendo Switch the colors are weird */
	mst3367_identity_csc(hdcap);

	dev_info(hdcap->dev, "hdmi_init: complete (%dx%d)\n",
		hdcap->width, hdcap->height);
	return 0;
}

/* ------------------------------------------------------------------ */
/* Main component init entry point                                    */
/* ------------------------------------------------------------------ */

int usb3hdcap_component_init(struct usb3hdcap *hdcap)
{
	const struct component_mode *mode;
	int ret, use_height;

	hdcap->mst_current_bank = -1;

	mst3367_config(hdcap);

	/* TW9900 power-down */
	u3hc_i2c_write(hdcap, ADDR_TW9900, 0x06, 0x0e);
	u3hc_i2c_write(hdcap, ADDR_TW9900, 0x1a, 0x40);

	/* CPLD init with component input mux */
	cpld_init(hdcap, 0x80);

	/* Component source select (MST3367 internal ADC for YPbPr) */
	mst_bank(hdcap, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x51, 0x21);

	/* Component CPLD routing, bit 4 = component input? */
	u3hc_i2c_read(hdcap, ADDR_CPLD, 0x20);
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x20, 0x15);

	mst3367_adc_config(hdcap);

	/* Wait for ADC to stabilize, windows driver does this but might be able
	   to decrease wait */
	msleep(1000);

	/* Final CPLD verify */
	u3hc_i2c_read(hdcap, ADDR_CPLD, 0x20);
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x20, 0x15);

	ret = component_poll_signal(hdcap, &mode);
	if (ret < 0)
		return ret;

	/* CPLD data path enable (bit 1 set when CPLD 0x20 bit 4 is set) */
	u3hc_i2c_rmw(hdcap, ADDR_CPLD, 0x00, 0xff, 0x02);

	component_write_scaler(hdcap, mode);

	mst3367_identity_csc(hdcap);

	use_height = hdcap->interlaced ? hdcap->height * 2 : hdcap->height;
	dev_info(hdcap->dev, "component_init: complete (%dx%d%s)\n",
		hdcap->width, use_height,
		hdcap->interlaced ? "i" : "p");
	return 0;
}
