// SPDX-License-Identifier: GPL-2.0
/*
 * USB3HDCAP MST3367 support: HDMI and component
 */

#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/math64.h>
#include <linux/usb.h>
#include <linux/v4l2-dv-timings.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-dv-timings.h>

#include "usb3hdcap.h"

const struct v4l2_dv_timings_cap usb3hdcap_hdmi_timings_cap = {
	.type = V4L2_DV_BT_656_1120,
	.bt = {
		.min_width = 640,
		.max_width = 1920,
		.min_height = 480,
		.max_height = 1080,
		.min_pixelclock = 25175000, /* 640x480p60 */
		.max_pixelclock = 148500000, /* 1080p60 */
		.standards = V4L2_DV_BT_STD_CEA861 | V4L2_DV_BT_STD_DMT,
		.capabilities = V4L2_DV_BT_CAP_PROGRESSIVE |
				V4L2_DV_BT_CAP_INTERLACED,
	},
};

int usb3hdcap_hdmi_enum_dv_timings(struct v4l2_enum_dv_timings *timings)
{
	return v4l2_enum_dv_timings_cap(timings, &usb3hdcap_hdmi_timings_cap,
					NULL, NULL);
}

/* ------------------------------------------------------------------ */
/* Component scaler mode table                                        */
/* ------------------------------------------------------------------ */

struct component_mode {
	int refresh_rate;
	/* MST3367 bank 0 ADC/scaler registers (ref: SetADParameters) */
	u8 pllgain, clpdly, clpdur, hsopw;
	u8 adc_bw0, adc_bw1;
	u16 scaler_htotal;
	u16 hde_off;
	u8 vde_off;
	struct v4l2_dv_timings timings;
};

#define U3HC_DV_BT_CEA_720X240P59_94 { \
	.type = V4L2_DV_BT_656_1120, \
	V4L2_INIT_BT_TIMINGS(720, 240, 0, 0, \
		13500000, 19, 62, 57, 4, 3, 15, 0, 0, 0, \
		V4L2_DV_BT_STD_CEA861, \
		V4L2_DV_FL_IS_CE_VIDEO | V4L2_DV_FL_HAS_PICTURE_ASPECT | \
		V4L2_DV_FL_HAS_CEA861_VIC, { 4, 3 }, 8) \
}

#define U3HC_DV_BT_CEA_720X288P50 { \
	.type = V4L2_DV_BT_656_1120, \
	V4L2_INIT_BT_TIMINGS(720, 288, 0, 0, \
		13500000, 12, 63, 69, 2, 3, 19, 0, 0, 0, \
		V4L2_DV_BT_STD_CEA861, \
		V4L2_DV_FL_IS_CE_VIDEO | V4L2_DV_FL_HAS_PICTURE_ASPECT | \
		V4L2_DV_FL_HAS_CEA861_VIC, { 4, 3 }, 23) \
}

/*
 * Values from Windows driver table $140303810 + 240p and 288p
 */
static const struct component_mode component_modes[] = {
	/*    pll   clp   clp   hsop  adc   adc                     */
	/*Hz  gain  dly   dur   w     bw0   bw1   sclht  hde    vde */
	{ 60, 0x08, 0x08, 0x08, 0x18, 0x44, 0x04, 0x35a, 0x076, 0x12,
	  V4L2_DV_BT_CEA_720X480I59_94 },
	{ 60, 0x08, 0x08, 0x08, 0x18, 0x44, 0x04, 0x35a, 0x077, 0x13,
	  U3HC_DV_BT_CEA_720X240P59_94 },
	{ 50, 0x08, 0x08, 0x08, 0x18, 0x44, 0x04, 0x360, 0x083, 0x16,
	  V4L2_DV_BT_CEA_720X576I50 },
	{ 50, 0x08, 0x08, 0x08, 0x18, 0x44, 0x04, 0x360, 0x083, 0x17,
	  U3HC_DV_BT_CEA_720X288P50 },
	{ 60, 0x20, 0x08, 0x08, 0x18, 0x33, 0x03, 0x35a, 0x079, 0x24,
	  V4L2_DV_BT_CEA_720X480P59_94 },
	{ 50, 0x18, 0x08, 0x08, 0x18, 0x33, 0x03, 0x360, 0x083, 0x2c,
	  V4L2_DV_BT_CEA_720X576P50 },
	{ 24, 0x58, 0x38, 0x20, 0x30, 0x11, 0x01, 0xce4, 0x12b, 0x19,
	  V4L2_DV_BT_CEA_1280X720P24 },
	{ 25, 0x58, 0x38, 0x20, 0x30, 0x11, 0x01, 0xf78, 0x12b, 0x19,
	  V4L2_DV_BT_CEA_1280X720P25 },
	{ 30, 0x58, 0x38, 0x20, 0x30, 0x11, 0x01, 0xce4, 0x12b, 0x19,
	  V4L2_DV_BT_CEA_1280X720P30 },
	{ 50, 0x58, 0x38, 0x20, 0x30, 0x11, 0x01, 0x7bc, 0x12b, 0x19,
	  V4L2_DV_BT_CEA_1280X720P50 },
	{ 60, 0x58, 0x38, 0x20, 0x30, 0x11, 0x01, 0x672, 0x12b, 0x19,
	  V4L2_DV_BT_CEA_1280X720P60 },
	{ 50, 0x58, 0x38, 0x20, 0x30, 0x11, 0x01, 0xa50, 0x0eb, 0x14,
	  V4L2_DV_BT_CEA_1920X1080I50 },
	{ 60, 0x58, 0x38, 0x20, 0x30, 0x11, 0x01, 0x898, 0x0eb, 0x14,
	  V4L2_DV_BT_CEA_1920X1080I60 },
	{ 24, 0xe8, 0x38, 0x30, 0x60, 0x00, 0x00, 0xabe, 0x0eb, 0x29,
	  V4L2_DV_BT_CEA_1920X1080P24 },
	{ 25, 0xe8, 0x38, 0x30, 0x60, 0x00, 0x00, 0xa50, 0x0eb, 0x29,
	  V4L2_DV_BT_CEA_1920X1080P25 },
	{ 30, 0xe8, 0x38, 0x30, 0x60, 0x00, 0x00, 0x898, 0x0eb, 0x29,
	  V4L2_DV_BT_CEA_1920X1080P30 },
	{ 50, 0xe8, 0x38, 0x30, 0x60, 0x00, 0x00, 0xa50, 0x0eb, 0x29,
	  V4L2_DV_BT_CEA_1920X1080P50 },
	{ 60, 0xe8, 0x38, 0x30, 0x60, 0x00, 0x00, 0x898, 0x0eb, 0x29,
	  V4L2_DV_BT_CEA_1920X1080P60 },
};

const struct v4l2_dv_timings_cap usb3hdcap_component_timings_cap = {
	.type = V4L2_DV_BT_656_1120,
	.bt = {
		.min_width = 720,
		.max_width = 1920,
		.min_height = 240,
		.max_height = 1080,
		.min_pixelclock = 13500000, /* 480i */
		.max_pixelclock = 148500000, /* 1080p60 */
		.standards = V4L2_DV_BT_STD_CEA861,
		.capabilities = V4L2_DV_BT_CAP_PROGRESSIVE |
				V4L2_DV_BT_CAP_INTERLACED,
	},
};

int usb3hdcap_component_enum_dv_timings(struct v4l2_enum_dv_timings *timings)
{
	if (timings->index >= ARRAY_SIZE(component_modes))
		return -EINVAL;

	timings->timings = component_modes[timings->index].timings;
	return 0;
}

bool usb3hdcap_component_timings_supported(const struct v4l2_dv_timings *t,
					   void *handle)
{
	int k;

	for (k = 0; k < ARRAY_SIZE(component_modes); k++)
		if (v4l2_match_dv_timings(t, &component_modes[k].timings, 0, false))
			return true;
	return false;
}

static int mst_bank(struct usb3hdcap *hdcap, int bank)
{
	if (hdcap->mst_current_bank == bank)
		return 0;
	hdcap->mst_current_bank = bank;
	return u3hc_i2c_write(hdcap, ADDR_MST3367, 0x00, bank);
}

static void mst3367_config(struct usb3hdcap *hdcap)
{
	mst_bank(hdcap, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x51, 0x80);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x13, 0x08);
	/* RxTmdsHotPlug: all off */
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0xb7, 0xff, 0x02);
	/* RxGeneralInit */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x41, 0x6f);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb8, 0x00);
	/* RxVideoInit */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb0, 0x14);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0xae, ~0x04, 0x04);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xad, 0x05); /* low-pass filter */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb1, 0xc0);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb2, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb3, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb4, 0x55);
	/* RxAudioInit */
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0xb4, ~0x03, 0x00);

	/* RxTmdsInit */
	mst_bank(hdcap, 0x01);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x0f, 0x02);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x16, 0x30);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x17, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x18, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x19, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1a, 0x50);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x2a, ~0x07, 0x07);
	/* RxHdcpInit */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x24, 0x40);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x25, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x30, 0x80);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x31, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x32, 0x00);

	mst_bank(hdcap, 0x02);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x08, 0x03);
	/* RxAudioInit (cont'd) */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x01, 0x61);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x02, 0xf5);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x03, ~0x02, 0x02);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x04, 0x01);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x05, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x06, 0x08);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1c, 0x1a);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1d, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1e, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1f, 0x00);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x25, 0xff ^ 0xa2, 0xa2);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x02, 0x7f, 0x80);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x07, ~0x04, 0x04);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x17, 0xc0);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x19, 0xff);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1a, 0xff);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1b, 0xfc);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x20, 0x00);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x21, ~0x03, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x22, 0x26);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x27, 0x00);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x2e, 0xff ^ 0xa1, 0xa1);

	mst_bank(hdcap, 0x00);

	if (hdcap->has_mcu) {
		u3hc_i2c_rmw(hdcap, ADDR_CPLD, 0x01, 0xff, 0x03);
		u3hc_i2c_write(hdcap, ADDR_CPLD, 0x11, 0xfc);
	}

	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0xb7, 0xff, 0x02);

	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xab, 0x15); /* COLOR.RANGE */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xac, 0x15); /* COLOR.RANGE */

	/* RxHdcpReset */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb8, 0x10);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb8, 0x00);

	/* RxHdmiReset */
	mst_bank(hdcap, 0x02);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x07, 0xf4);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x07, 0x04);

	/* RxSwitchSource: 0x81 = HDMI TMDS.A */
	mst_bank(hdcap, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x51, 0x81);

	if (hdcap->has_mcu) {
		u3hc_i2c_rmw(hdcap, ADDR_CPLD, 0x01, 0xfd, 0x01);
		u3hc_i2c_write(hdcap, ADDR_CPLD, 0x11, 0xfc);
	}

	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0xb7, 0xfd, 0x00);
	msleep(200);

	/* FUN_00016640: RxHdmiInit / BT.656 output enable */
	mst_bank(hdcap, 0x02);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x01, 0x0f, 0x60);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x04, 0xff, 0x01);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x06, 0x08);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x09, 0xff, 0x20);

	mst_bank(hdcap, 0x00);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x54, 0xef, 0x00);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0xac, 0xff, 0x80);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0xce, 0xff, 0x80);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0xcf, 0xfa, 0x02);

	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x00, 0x7f, 0x00);
	mst_bank(hdcap, 0x00);
}

static void cpld_init(struct usb3hdcap *hdcap, u8 mux_val)
{
	int k, status;

	/*
	 * cVar3 = i2c_read(param_1,0x98,0x3b,0);
	 * if (cVar3 != '\0') {
	 *   uVar5 = *(uint *)(param_1 + 0x6840);
	 *   if ((uVar5 == 2) || (uVar5 == 3)) {
	 *     local_res8[0] = -0x80;
	 *     i2c_write(param_1,0x98,0x3b,local_res8,1);
	 *     uVar5 = *(uint *)(param_1 + 0x6840);
	 *   }
	 *   if (uVar5 < 2) {
	 *     local_res8[0] = '\x02';
	 *     i2c_write(param_1,0x98,0x3b,local_res8,1);
	 *   }
	 * }
	 */

	if (u3hc_i2c_read(hdcap, ADDR_CPLD, 0x3b) != 0)
		u3hc_i2c_write(hdcap, ADDR_CPLD, 0x3b, mux_val);

	/*
	 * local_res8[0] = '\x05';
	 * i2c_write(param_1,0x98,0x20,local_res8,1);
	 * cVar3 = FUN_140226fc4(param_1);
	 * local_res8[0] = '\x01';
	 * i2c_write(param_1,0x98,0,local_res8,1);
	 * local_res8[0] = (-(cVar3 != '\0') & 0xfeU) - 2;
	 * i2c_write(param_1,0x98,0x10,local_res8,1);
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

	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x01, hdcap->has_mcu ? 0x03 : 0x02);
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x11, 0xfc);
}

/* Identity CSC for component YPbPr */
static const u8 csc_identity_component[] = {
	0x10, 0x00,  0x00, 0x00,  0x00, 0x00, /* M11, M12, M13 */
	0x00, 0x00,  0x10, 0x00,  0x00, 0x00, /* M21, M22, M23 */
	0x00, 0x00,  0x00, 0x00,  0x10, 0x00, /* M31, M32, M33 */
	0x20, 0x00,  0x03, 0x80,  0x20, 0x00, /*  A1,  A2,  A3 */
};

/* Identity CSC for HDMI YCbCr */
static const u8 csc_identity_hdmi[] = {
	0x10, 0x00,  0x00, 0x00,  0x00, 0x00,
	0x00, 0x00,  0x10, 0x00,  0x00, 0x00,
	0x00, 0x00,  0x00, 0x00,  0x10, 0x00,
	0x20, 0x00,  0x00, 0x00,  0x20, 0x00,
};

/* BT.601 for SD (width <= 720) */
static const u8 csc_r2y_sd[] = {
	0x08, 0x02,  0x04, 0xc5,  0xfd, 0x4d,
	0xf9, 0x4a,  0x09, 0x5b,  0xfa, 0xb1,
	0xfe, 0xb4,  0x01, 0xd2,  0x08, 0x02,
	0x20, 0x00,  0x00, 0x00,  0x20, 0x00,
};

/* BT.709 for HD (width > 720) */
static const u8 csc_r2y_hd[] = {
	0x08, 0x02,  0x03, 0x65,  0xfe, 0x28,
	0xf8, 0xb9,  0x0b, 0x65,  0xf9, 0xd6,
	0xff, 0x45,  0x01, 0x27,  0x08, 0x02,
	0x20, 0x00,  0x00, 0x00,  0x20, 0x00,
};

#define COLOR_RGB 0x00
#define COLOR_YUV422 0x20
#define COLOR_YUV444 0x40

void mst3367_write_csc(struct usb3hdcap *hdcap)
{
	bool comp = (hdcap->input == INPUT_COMPONENT);
	const u8 *csc;
	u8 old_ab, reg_92;
	bool limited = false;
	/* this can be overridden by the source */
	bool bt601 = hdcap->width <= 720;
	int k;

	if (comp) {
		reg_92 = 0x66;
		csc = csc_identity_component;
	} else {
		int pkt_status;
		int color = 0;
		int quant = 0;
		int colorimetry = 0;

		mst_bank(hdcap, 0x02);
		pkt_status = (u3hc_i2c_read(hdcap, ADDR_MST3367, 0x0c) & 0x3f) << 8 |
			     (u3hc_i2c_read(hdcap, ADDR_MST3367, 0x0b) & 0xff);
		if (u3hc_i2c_read(hdcap, ADDR_MST3367, 0x0e) & 0x08)
			pkt_status |= 0x8000;

		/* ref: RxHdmiPacketColor */
		if (pkt_status & 0x8) {
			/* 0x00 = RGB, 0x20 = YUV422, 0x40 = YUV444 */
			color = u3hc_i2c_read(hdcap, ADDR_MST3367, 0x48) & 0x60;
			/* 0 = default, 1 = limited, 2 = full */
			quant = u3hc_i2c_read(hdcap, ADDR_MST3367, 0x4a);
			quant = quant < 0 ? 0 : (quant >> 2) & 0x03;
			limited = quant == 1;
			/* 0 = not stated, 1 = BT.601, 2 = BT.709 */
			colorimetry = u3hc_i2c_read(hdcap, ADDR_MST3367, 0x49);
			colorimetry = colorimetry < 0 ? 0 : colorimetry >> 6;
		}

		dev_info(hdcap->dev,
			 "CSC: pkt_status=0x%04x color=0x%02x quant=%d colorimetry=%d\n",
			 pkt_status, color, quant, colorimetry);

		if (color == COLOR_RGB) {
			reg_92 = limited ? 0x55 : 0x40;
			csc = bt601 ? csc_r2y_sd : csc_r2y_hd;
			dev_info(hdcap->dev, "CSC: HDMI RGB, %s R2Y\n",
				 bt601 ? "BT.601" : "BT.709");
		} else {
			bt601 = colorimetry == 1;
			reg_92 = limited ? 0x66 : 0x62;
			csc = csc_identity_hdmi;
			dev_info(hdcap->dev,
				 "CSC: HDMI YCbCr (0x%02x), %s\n",
				 color, bt601 ? "BT.601" : "BT.709");
		}
	}

	hdcap->mst_bt601 = bt601;

	mst_bank(hdcap, 0x00);

	/* BLANK.OUTPUT while changing CSC */
	u3hc_i2c_rmw_get_old(hdcap, ADDR_MST3367, 0xab, 0x7f, 0x80, &old_ab);

	/* COLOR.RANGE */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x90, 0x15);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x91, 0x15);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x92, reg_92);

	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0xac, ~0x3f, 0x15);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xad, 0x05);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1e, 0x11);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1f, 0x01);

	for (k = 0; k < 24; k++)
		u3hc_i2c_write(hdcap, ADDR_MST3367, 0x93 + k, csc[k]);

	if (!comp)
		u3hc_i2c_write(hdcap, ADDR_MST3367, 0xa7, limited ? 0x04 : 0x00);

	/* RX_OUTPUT_YUV422 / 08.BITS / EMBEDDED SYNC */
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0xb0, 0xc2, 0x21);
	/* NORMAL.OUTPUT (un-blank) */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xab, old_ab & 0x7f);

	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xb3, 0x00);

	mst_bank(hdcap, 0x02);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x27, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x20, 0x00);
}

/* ------------------------------------------------------------------ */
/* Signal detection polling                                           */
/* ------------------------------------------------------------------ */

#define HDMI_VTOTAL_TOLERANCE	5
#define HDMI_VFREQ_TOLERANCE	5

static int mst3367_read_vfreq(struct usb3hdcap *hdcap)
{
	int hi, lo, period;

	mst_bank(hdcap, 0x00);
	hi = u3hc_i2c_read(hdcap, ADDR_MST3367, 0x59);
	lo = u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5a);
	if (hi < 0 || lo < 0)
		return 0;

	period = (hi & 0x3f) << 8 | lo;
	/* units of 0.1 Hz, ref: RxHdmiModeDetect */
	return period ? 1250000 / period : 0;
}

static const struct v4l2_dv_timings *match_hdmi_timing(int hactive, int vtotal,
						       int vfreq)
{
	const struct v4l2_dv_timings *best = NULL;
	int best_err = INT_MAX;
	int k;

	for (k = 0; v4l2_dv_timings_presets[k].bt.width; k++) {
		const struct v4l2_dv_timings *t = &v4l2_dv_timings_presets[k];
		const struct v4l2_bt_timings *bt = &t->bt;
		u32 frame_width = V4L2_DV_BT_FRAME_WIDTH(bt);
		u32 frame_height = V4L2_DV_BT_FRAME_HEIGHT(bt);
		int fields = bt->interlaced ? 2 : 1;
		int vtotal_err, vfreq_err, err;

		if (bt->width != hactive)
			continue;
		if (!v4l2_valid_dv_timings(t, &usb3hdcap_hdmi_timings_cap,
					   NULL, NULL))
			continue;

		vtotal_err = abs(vtotal * fields - (int)frame_height);
		if (vtotal_err > HDMI_VTOTAL_TOLERANCE)
			continue;

		vfreq_err = abs(vfreq -
				(int)DIV_ROUND_CLOSEST_ULL(bt->pixelclock * 10 * fields,
							   frame_width * frame_height));
		if (vfreq_err > HDMI_VFREQ_TOLERANCE)
			continue;

		err = vtotal_err * 2 * HDMI_VFREQ_TOLERANCE + vfreq_err;
		if (err < best_err) {
			best_err = err;
			best = t;
		}
	}
	return best;
}

static void mst3367_enable_auto_position(struct usb3hdcap *hdcap)
{
	mst_bank(hdcap, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xe2, 0x80);
	/* report the digital DE window */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xe3, 0x08);
	/* position threshold */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0xe4, 0x00);
}

static int hdmi_poll_signal(struct usb3hdcap *hdcap)
{
	int k, status;
	int prev_htotal = -1, prev_vtotal = -1, prev_hactive = -1;
	int stable_count = 0;

	mst3367_enable_auto_position(hdcap);
	msleep(100);

	for (k = 0; k < 100; k++) {
		int htotal, vtotal, hactive, vfreq, tmds_ratio;
		const struct v4l2_dv_timings *std;

		msleep(100);

		mst_bank(hdcap, 0x00);
		status = u3hc_i2c_read(hdcap, ADDR_MST3367, 0x55);
		if (status < 0)
			continue;

		if (!(status & 0x3c)) {
			/* Not locked yet */
			mst3367_enable_auto_position(hdcap);
			if (k % 10 == 0)
				dev_info(hdcap->dev,
					 "HDMI signal poll[%d]: lock=0x%02x (no signal)\n",
					 k, status);
			stable_count = 0;
			continue;
		}

		htotal = (u3hc_i2c_read(hdcap, ADDR_MST3367, 0x6a) << 8 |
			  u3hc_i2c_read(hdcap, ADDR_MST3367, 0x6b)) & 0xfff;
		vtotal = (u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5b) << 8 |
			  u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5c)) & 0x7ff;

		mst_bank(hdcap, 0x02);
		hactive = (u3hc_i2c_read(hdcap, ADDR_MST3367, 0x29) << 8 |
			   u3hc_i2c_read(hdcap, ADDR_MST3367, 0x28)) & 0x1fff;

		if (k % 5 == 0)
			dev_info(hdcap->dev,
				 "HDMI poll[%d]: lock=0x%02x ht=%d vt=%d ha=%d stable=%d\n",
				 k, status, htotal, vtotal, hactive, stable_count);

		/*
		 * Require non-zero timings and two consecutive identical
		 * readings before accepting
		 */
		if (htotal == 0 || vtotal == 0 || hactive == 0 ||
		    htotal != prev_htotal || vtotal != prev_vtotal ||
		    hactive != prev_hactive) {
			prev_htotal = htotal;
			prev_vtotal = vtotal;
			prev_hactive = hactive;
			stable_count = 0;
			continue;
		}

		if (++stable_count < 2)
			continue;

		vfreq = mst3367_read_vfreq(hdcap);

		dev_info(hdcap->dev,
			 "HDMI locked: htotal=%d vtotal=%d hactive=%d vfreq=%d.%d\n",
			 htotal, vtotal, hactive, vfreq / 10, vfreq % 10);

		std = match_hdmi_timing(hactive, vtotal, vfreq);
		if (!std) {
			dev_err(hdcap->dev,
				"unsupported HDMI timing: htotal=%d vtotal=%d hactive=%d vfreq=%d.%d\n",
				htotal, vtotal, hactive, vfreq / 10, vfreq % 10);
			return -ERANGE;
		}

		/* 100 = 8 bit, 125 = 10 bit, 150 = 12 bit deep color */
		tmds_ratio = htotal * 100 / V4L2_DV_BT_FRAME_WIDTH(&std->bt);
		dev_info(hdcap->dev,
			 "HDMI mode: %ux%u%s, TMDS clock = %d.%02dx pixel clock\n",
			 std->bt.width, std->bt.height,
			 std->bt.interlaced ? "i" : "p",
			 tmds_ratio / 100, tmds_ratio % 100);

		hdcap->detected_timings = *std;
		hdcap->detected_timings_present = 1;
		hdcap->std = 0; /* no SD standard */
		hdcap->width = std->bt.width;
		hdcap->interlaced = std->bt.interlaced;
		hdcap->height = std->bt.interlaced
			? std->bt.height / 2 : std->bt.height;
		hdcap->bpl = hdcap->width * 2;

		/* DISABLE AUTO POSITION */
		mst_bank(hdcap, 0x00);
		u3hc_i2c_write(hdcap, ADDR_MST3367, 0xe2, 0x00);

		return 0;
	}

	dev_err(hdcap->dev, "No HDMI signal lock after 10s\n");
	return -ETIMEDOUT;
}

/* ------------------------------------------------------------------ */
/* ADC front-end config (component/VGA only)                          */
/* ------------------------------------------------------------------ */

static void mst3367_adc_config(struct usb3hdcap *hdcap)
{
	/* RxAdcInit */
	mst_bank(hdcap, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x00, 0x80);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x24, 0xc0);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x00, 0x00);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x21, ~0x07, 0x01);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x04, 0x00); /* ADC phase */
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x10, 0x0f, 0xd0);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x11, 0x2d);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x20, 0xc0);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x21, 0x04);
	/* bits 5:4 = sync source: 0x30 = SOG for component */
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x0e, 0xcf, 0x30);
}

#define COMPONENT_VTOTAL_TOLERANCE	25
#define COMPONENT_HFREQ_TOLERANCE	8

/* Picks the mode closest to the measured line count and line rate */
static const struct component_mode *match_component_mode(int vtotal, int hfreq,
							 bool interlaced)
{
	const struct component_mode *best = NULL;
	int best_err = INT_MAX;
	int k;

	for (k = 0; k < ARRAY_SIZE(component_modes); k++) {
		const struct component_mode *m = &component_modes[k];
		const struct v4l2_bt_timings *bt = &m->timings.bt;
		int std_vtotal = V4L2_DV_BT_FRAME_HEIGHT(bt) /
				 (bt->interlaced ? 2 : 1);
		int std_hfreq = (u32)bt->pixelclock /
				(V4L2_DV_BT_FRAME_WIDTH(bt) * 100);
		int vtotal_err = abs(vtotal - std_vtotal);
		int hfreq_err = abs(hfreq - std_hfreq);
		int err;

		if (vtotal_err > COMPONENT_VTOTAL_TOLERANCE ||
		    hfreq_err > COMPONENT_HFREQ_TOLERANCE)
			continue;

		err = vtotal_err + hfreq_err;
		if (!bt->interlaced != !interlaced)
			err += COMPONENT_VTOTAL_TOLERANCE +
			       COMPONENT_HFREQ_TOLERANCE + 1;
		if (err < best_err) {
			best_err = err;
			best = m;
		}
	}
	return best;
}

/* ------------------------------------------------------------------ */
/* Component scaler register write                                    */
/* ------------------------------------------------------------------ */

static void component_write_scaler(struct usb3hdcap *hdcap,
				   const struct component_mode *m)
{
	const struct v4l2_bt_timings *bt = &m->timings.bt;
	int width = bt->width;
	int height = bt->interlaced ? bt->height / 2 : bt->height;
	int ht = m->scaler_htotal - 1;
	int is_720_low_rr = width == 1280 && height == 720 &&
			(m->refresh_rate == 24 ||
				m->refresh_rate == 25 ||
				m->refresh_rate == 30);

	mst_bank(hdcap, 0x00);

	/*
	 * edge case for low frame rate 720p:
	 * if (((*(int *)(uVar30 + 0x30) == 0x500) && (*(int *)(uVar30 + 0x34) == 0x2d0)) &&
	 *     ((*(int *)(uVar30 + 0x38) == 0x1e ||
	 *     ((*(int *)(uVar30 + 0x38) == 0x19 || (*(int *)(uVar30 + 0x38) == 0x18)))))) {
	 *   uVar37 = 0;
	 * } else {
	 *   uVar37 = 4;
	 * }
	 * send_mst(param_1,0,0x12,uVar37);
	 */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x12, is_720_low_rr ? 0x00 : 0x04);

	/* SetADParameters */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x03, m->pllgain);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x05, m->clpdly);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x06, m->clpdur);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x07, m->hsopw);

	/* ADC gain: Y, Cb, Cr */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x08, 0xa0);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x09, 0xc0);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x0a, 0xa0);

	/* grade scale (clamp level): Y, Cb, Cr */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x0b, 0x80);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x0c, 0x60);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x0d, 0x80);

	/* clamp offset: Y, Cb, Cr */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x18, 0x10);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x19, 0x10);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1a, 0x10);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1b, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1c, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1d, 0x00);

	/* ADCSetAutoDetectFormat: output htotal */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x01, ht >> 4);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x02, (ht & 0x0f) << 4);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1e, m->adc_bw0);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x1f, m->adc_bw1);

	/* output data enable start pos after sync */
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x80, (m->hde_off >> 8) & 0x0f);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x81, m->hde_off & 0xff);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x82, (width >> 8) & 0xff);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x83, width & 0xff);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x84, m->vde_off);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x85,
		       ((height >> 8) & 0x0f) | (bt->interlaced ? 0x20 : 0x00));
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x86, height & 0xff);

	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x2d, 0x11);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x2e, 0x11);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x39, (u8)(m->clpdly + m->clpdur - 0x78));
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x2c, 0x9d);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x3a, 0x0c);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x3b, 0x08);

	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x10, 0xfa, 0x05);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x0f, 0xff, 0x20);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x17, 0xff, 0x02);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x2f, 0xff, 0x02);
	u3hc_i2c_rmw(hdcap, ADDR_MST3367, 0x60, 0xfb, 0x00);
}

/* ------------------------------------------------------------------ */
/* Component ADC signal polling                                       */
/* ------------------------------------------------------------------ */

static int component_poll_signal(struct usb3hdcap *hdcap,
				 const struct component_mode **detected)
{
	const struct component_mode *mode;
	int k, status, vtotal, hperiod, hfreq, interlaced;
	int signal_count = 0;

	/*
	 * RxAdcModeDetect()
	 * Signal detection per decompiled Windows driver:
	 *   0x14 & 0x90 == 0x90: H+V locked (status=1)
	 *   0x14 & 0x90 == 0x80: H lock only (status=2)
	 *   0x14 == 0x00 && 0x15 & 0x40: status=3
	 */
	for (k = 0; k < 100; k++) {
		int signal_type;

		mst_bank(hdcap, 0x00);

		/* trigger timing measurement? */
		u3hc_i2c_write(hdcap, ADDR_MST3367, 0x0e, 0x40);

		status = u3hc_i2c_read(hdcap, ADDR_MST3367, 0x14);
		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x15);

		/* Check signal presence from 0x14 bits 7,4 */
		signal_type = status & 0x90;
		if (signal_type == 0x90 || signal_type == 0x80 ||
		    (signal_type == 0x00 && (status & 0x02)))
			signal_count++;
		else
			signal_count = 0;

		hperiod = ((u3hc_i2c_read(hdcap, ADDR_MST3367, 0x57) & 0x3f) << 8) |
			   u3hc_i2c_read(hdcap, ADDR_MST3367, 0x58);

		/* scale ADC sample rate to H period */
		if (hperiod > 0)
			u3hc_i2c_write(hdcap, ADDR_MST3367, 0x11,
				       (hperiod < 0x401 ? 0x400 : hperiod) >> 7);

		/* V period (timer counts) */
		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x59);
		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5a);

		/* V total (lines) */
		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5b);
		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5c);

		/* H total (pixels), interlace flag */
		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5d);
		u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5e);
		interlaced = u3hc_i2c_read(hdcap, ADDR_MST3367, 0x5f);
		interlaced = interlaced < 0 ? 0 : !!(interlaced & 0x02);

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

		/* units are 0.1 kHz, ref: RxAdcModeDetect */
		hfreq = hperiod > 0 ? 1600000 / hperiod : 0;

		dev_info(hdcap->dev,
			 "component locked: vtotal=%d hfreq=%d.%d kHz %s 0x14=0x%02x\n",
			 vtotal, hfreq / 10, hfreq % 10,
			 interlaced ? "interlaced" : "progressive", status);

		mode = match_component_mode(vtotal, hfreq, interlaced);
		if (!mode) {
			dev_err(hdcap->dev,
				"unsupported component timing: vtotal=%d hfreq=%d.%d kHz\n",
				vtotal, hfreq / 10, hfreq % 10);
			return -ERANGE;
		}
		hdcap->width = mode->timings.bt.width;
		hdcap->interlaced = mode->timings.bt.interlaced;
		hdcap->height = hdcap->interlaced ? mode->timings.bt.height / 2 :
						    mode->timings.bt.height;
		hdcap->bpl = hdcap->width * 2;
		hdcap->std = 0; /* no SD standard */
		hdcap->detected_timings_present = 1;
		hdcap->detected_timings = mode->timings;
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

	/* TW9900 power-down */
	u3hc_i2c_write(hdcap, ADDR_TW9900, 0x06, 0x0e);
	u3hc_i2c_write(hdcap, ADDR_TW9900, 0x1a, 0x40);

	/* CPLD init with HDMI input mux */
	cpld_init(hdcap, 0x02);
	mst3367_config(hdcap);

	ret = hdmi_poll_signal(hdcap);
	if (ret < 0)
		return ret;

	mst3367_write_csc(hdcap);

	v4l2_ctrl_handler_setup(&hdcap->ctrl);

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

	/* TW9900 power-down */
	u3hc_i2c_write(hdcap, ADDR_TW9900, 0x06, 0x0e);
	u3hc_i2c_write(hdcap, ADDR_TW9900, 0x1a, 0x40);

	/* CPLD init with component input mux */
	cpld_init(hdcap, 0x80);

	mst3367_config(hdcap);

	/* RxSwitchSource: 0x21 = component ADC (YPbPr) */
	mst_bank(hdcap, 0x00);
	u3hc_i2c_write(hdcap, ADDR_MST3367, 0x51, 0x21);

	/* Component CPLD routing, bit 4 = component input? */
	u3hc_i2c_read(hdcap, ADDR_CPLD, 0x20);
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x20, 0x15);

	mst3367_adc_config(hdcap);

	/*
	 * Wait for ADC to stabilize, windows driver does this but might be able
	 * to decrease wait
	 */
	msleep(1000);

	/* Final CPLD verify */
	u3hc_i2c_read(hdcap, ADDR_CPLD, 0x20);
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x20, 0x15);

	ret = component_poll_signal(hdcap, &mode);
	if (ret < 0)
		return ret;

	u3hc_i2c_rmw(hdcap, ADDR_CPLD, 0x00, 0xff, 0x02);

	component_write_scaler(hdcap, mode);
	mst3367_write_csc(hdcap);

	v4l2_ctrl_handler_setup(&hdcap->ctrl);

	use_height = hdcap->interlaced ? hdcap->height * 2 : hdcap->height;
	dev_info(hdcap->dev, "component_init: complete (%dx%d%s)\n",
		 hdcap->width, use_height,
		 hdcap->interlaced ? "i" : "p");
	return 0;
}
