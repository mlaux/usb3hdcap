// SPDX-License-Identifier: GPL-2.0
/*
 * USB3HDCAP composite video init - CPLD + TW9900 setup, signal lock
 */

#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/usb.h>
#include <media/v4l2-ctrls.h>

#include "usb3hdcap.h"

/* TW9900 registers */
#define TW9900_SDT        0x1c
#define TW9900_SDTR       0x31
#define TW9900_NINTL      0x08
#define TW9900_STDNOW_SHIFT 4
#define TW9900_STDNOW_MASK  0x70
#define TW9900_STD_NTSC_M   0
#define TW9900_STD_PAL_BDGHI 1
#define TW9900_STD_SECAM 2
#define TW9900_STD_NTSC_4_43 3
#define TW9900_STD_PAL_M 4
#define TW9900_STD_PAL_CN 5
#define TW9900_STD_PAL_60 6

/* Detect PAL vs NTSC from TW9900 auto-detection result */
static void usb3hdcap_detect_std(struct usb3hdcap *hdcap)
{
	int k, sdt, detected;

	/* 0x80 = start detection */
	/* 0x03 = enable recognition of PAL and NTSC only */
	i2c_write(hdcap, ADDR_TW9900, 0x1d, 0x83);

	for (k = 0; k < 10; k++) {
		sdt = i2c_read(hdcap, ADDR_TW9900, TW9900_SDT);
		if (!(sdt & 0x80)) {
			break;
		}
		msleep(100);
	}

	if (sdt & 0x80) {
		dev_warn(hdcap->dev, "Detection not done after 1s, using NTSC\n");
		hdcap->std = V4L2_STD_525_60;
		return;
	}

	detected = (sdt & TW9900_STDNOW_MASK) >> TW9900_STDNOW_SHIFT;
	switch (detected) {
	case TW9900_STD_NTSC_M:
		hdcap->std = V4L2_STD_525_60;
		dev_info(hdcap->dev, "NTSC detected (SDT=0x%02x)\n", sdt);
		break;
	case TW9900_STD_PAL_BDGHI:
		hdcap->std = V4L2_STD_PAL;
		dev_info(hdcap->dev, "PAL detected (SDT=0x%02x)\n", sdt);
		break;
	default: /* not sure if this will be hit, because others are disabled */
		hdcap->std = V4L2_STD_525_60;
		dev_info(hdcap->dev, "Non-PAL/NTSC detected (SDT=0x%02x)\n", sdt);
		break;
	}
}

/* Detect 240p/288p (non-interlaced) vs 480i/576i */
static void usb3hdcap_detect_size(struct usb3hdcap *hdcap)
{
	int status;
	int full_h = (hdcap->std & V4L2_STD_625_50) ? PAL_HEIGHT : NTSC_HEIGHT;
	int half_h = full_h / 2;
	hdcap->width = NTSC_WIDTH;
	hdcap->height = half_h;

	status = i2c_read(hdcap, ADDR_TW9900, TW9900_SDTR);
	if (status >= 0 && (status & TW9900_NINTL)) {
		hdcap->interlaced = 0;
		dev_info(hdcap->dev, "NINTL=1: %dp detected (SDTR=0x%02x)\n",
			half_h, status);
	} else {
		hdcap->interlaced = 1;
		dev_info(hdcap->dev, "NINTL=0: %di detected (SDTR=0x%02x)\n",
			full_h, status);
	}
}

int usb3hdcap_composite_init(struct usb3hdcap *hdcap)
{
	int k, status;

	/* disable MST3367 */
	i2c_write(hdcap, ADDR_MST3367, 0x00, 0x00); /* bank 0 */
	i2c_write(hdcap, ADDR_MST3367, 0x51, 0x80);

	/* disable TW9900 */
	i2c_write(hdcap, ADDR_TW9900, 0x06, 0x0e); /* ACNTL_I */
	i2c_write(hdcap, ADDR_TW9900, 0x1a, 0x40); /* ACNTL_II */

	/* select TW9900 input of cpld? */
	/* from windows driver */
	status = i2c_read(hdcap, ADDR_CPLD, 0x3b);
	if (status != 0) {
		i2c_write(hdcap, ADDR_CPLD, 0x3b, 0x80);
	}
	i2c_write(hdcap, ADDR_CPLD, 0x20, 0x05);
	i2c_write(hdcap, ADDR_CPLD, 0x00, 0x01);
	i2c_write(hdcap, ADDR_CPLD, 0x10, 0xfe);
	i2c_write(hdcap, ADDR_CPLD, 0x20, 0x75);

	/* Main TW9900 configuration */
	i2c_write(hdcap, ADDR_TW9900, 0x06, 0x00); /* ACNTL_I */
	i2c_write(hdcap, ADDR_TW9900, 0x03, 0xa2); /* OPFORM */
	i2c_write(hdcap, ADDR_TW9900, 0x05, 0x01); /* OPCNTL_I */
	i2c_write(hdcap, ADDR_TW9900, 0x08, 0x14); /* VDELAY_LO */
	i2c_write(hdcap, ADDR_TW9900, 0x09, 0xf2); /* VACTIVE_LO */
	i2c_write(hdcap, ADDR_TW9900, 0x0a, 0x0b); /* HDELAY_LO */
	i2c_write(hdcap, ADDR_TW9900, 0x0b, 0xd2); /* HACTIVE_LO */
	i2c_write(hdcap, ADDR_TW9900, 0x19, 0x57); /* VBICNTL */
	i2c_write(hdcap, ADDR_TW9900, 0x1a, 0x0f); /* ACNTL_II */
	i2c_write(hdcap, ADDR_TW9900, 0x1b, 0x00); /* OPCNTL_II */
	i2c_write(hdcap, ADDR_TW9900, 0x1c, 0x07); /* SDT: auto-detect */
	i2c_write(hdcap, ADDR_TW9900, 0x28, 0x0c); /* VCNTL1 */
	i2c_write(hdcap, ADDR_TW9900, 0x29, 0x03); /* VCNTL2 */
	i2c_write(hdcap, ADDR_TW9900, 0x2d, 0x07); /* MISC1 */
	i2c_write(hdcap, ADDR_TW9900, 0x2f, 0x06); /* MISC2 */
	i2c_write(hdcap, ADDR_TW9900, 0x4c, 0x01); /* ANAPLLCTL */
	i2c_write(hdcap, ADDR_TW9900, 0x55, 0x00); /* VVBI */
	i2c_write(hdcap, ADDR_TW9900, 0x6b, 0x26); /* HSBEGIN */
	i2c_write(hdcap, ADDR_TW9900, 0x6c, 0x36); /* HSEND */
	i2c_write(hdcap, ADDR_TW9900, 0x6d, 0xf0); /* OVSDLY */
	i2c_write(hdcap, ADDR_TW9900, 0x6e, 0x28); /* OVSEND */
	i2c_write(hdcap, ADDR_TW9900, 0x06, 0x80); /* ACNTL_I */
	if (hdcap->input == INPUT_SVIDEO) {
		/* "Input crystal clock frequency is 27MHz" */
		/* IFSEL 01 for S-Video, YSEL 01 for Y on Mux1 */
		i2c_write(hdcap, ADDR_TW9900, 0x02, 0x54);
		/* "internal current reference 2" + both luma and chroma ADCs on */
		i2c_write(hdcap, ADDR_TW9900, 0x06, 0x40);

	} else {
		/* IFSEL 00 for composite, YSEL 00 for Y on Mux0 */
		i2c_write(hdcap, ADDR_TW9900, 0x02, 0x40);
		/* "internal current reference 2" + chroma ADC off */
		i2c_write(hdcap, ADDR_TW9900, 0x06, 0x42);
	}
	v4l2_ctrl_handler_setup(&hdcap->ctrl);

	vendor_out(hdcap, REQ_STREAM, 0x0000, 0, NULL, 0);

	for (k = 0; k < 10; k++) {
		status = i2c_read(hdcap, ADDR_TW9900, 0x01);

		/* 0x40 = "Horizontal sync PLL is locked to the incoming video source"
		   0x08 = "Vertical logic is locked to the incoming video source" */
		if (status >= 0 && (status & 0x48) == 0x48) {
			dev_info(hdcap->dev, "Signal locked (%d ms)\n", k * 100);
			break;
		}
		msleep(100);
	}

	if (k == 10) {
		dev_err(hdcap->dev, "No signal lock after 1s (last status=0x%02x)\n",
			status);
		return -ETIMEDOUT;
	}

	usb3hdcap_detect_std(hdcap);
	usb3hdcap_detect_size(hdcap);

	/* Adjust for PAL vs NTSC */
	if (hdcap->std & V4L2_STD_625_50) {
		i2c_rmw(hdcap, ADDR_TW9900, 0x07, 0x0f, 0x10); /* CROP_HI: set bit 4 */
		i2c_write(hdcap, ADDR_TW9900, 0x08, 0x19); /* VDELAY_LO */
		i2c_write(hdcap, ADDR_TW9900, 0x09, 0x20); /* VACTIVE_LO */
		i2c_write(hdcap, ADDR_TW9900, 0x0a, 0x0a); /* HDELAY_LO */
		i2c_write(hdcap, ADDR_TW9900, 0x0b, 0xd0); /* HACTIVE_LO */
		i2c_rmw(hdcap, ADDR_TW9900, 0x55, 0xef, 0x00); /* VVBI: clear bit 4 */
	} else {
		i2c_rmw(hdcap, ADDR_TW9900, 0x07, 0x0f, 0x00); /* CROP_HI: clear bit 4 */
		i2c_write(hdcap, ADDR_TW9900, 0x08, 0x14); /* VDELAY_LO */
		i2c_write(hdcap, ADDR_TW9900, 0x09, 0xf2); /* VACTIVE_LO */
		i2c_write(hdcap, ADDR_TW9900, 0x0a, 0x10); /* HDELAY_LO */
		i2c_write(hdcap, ADDR_TW9900, 0x0b, 0xd0); /* HACTIVE_LO */
		i2c_rmw(hdcap, ADDR_TW9900, 0x55, 0xef, 0x10); /* VVBI: set bit 4 */
	}
	i2c_write(hdcap, ADDR_TW9900, 0x0d, 0x00); /* CNTRL2 */
	i2c_write(hdcap, ADDR_TW9900, 0x0e, 0x11); /* SDT_NOISE */
	i2c_write(hdcap, ADDR_TW9900, 0x0f, 0x00); /* LUMA_CTL */

	return 0;
}
