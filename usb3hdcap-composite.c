// SPDX-License-Identifier: GPL-2.0
/*
 * USB3HDCAP composite video init - CPLD + TW9900 setup, signal lock
 */

#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/usb.h>
#include <media/i2c/mst3367.h>
#include <media/i2c/tw9900.h>
#include <media/v4l2-ctrls.h>

#include "usb3hdcap.h"

/* Main TW9900 configuration */
static const struct tw9900_regval tw9900_init_regs[] = {
	{ TW9900_ACNTL_I, 0x00 },
	{ TW9900_OPFORM, 0xa7 },
	{ TW9900_OPCNTL_I, 0x01 },
	{ TW9900_VDELAY_LO, 0x14 },
	{ TW9900_VACTIVE_LO, 0xf2 },
	{ TW9900_HDELAY_LO, 0x0b },
	{ TW9900_HACTIVE_LO, 0xd2 },
	{ TW9900_VBICNTL, 0x57 },
	{ TW9900_ACNTL_II, 0x0f },
	{ TW9900_OPCNTL_II, 0x00 },
	{ TW9900_SDT, 0x07 }, /* auto-detect */
	{ TW9900_VCNTL1, 0x0c },
	{ TW9900_VCNTL2, 0x03 },
	{ TW9900_MISC1, 0x07 },
	{ TW9900_MISC2, 0x06 },
	{ TW9900_ANAPLLCTL, 0x01 },
	{ TW9900_VVBI, 0x00 },
	{ TW9900_HSBEGIN, 0x26 },
	{ TW9900_HSEND, 0x36 },
	{ TW9900_OVSDLY, 0xf0 },
	{ TW9900_OVSEND, 0x28 },
	{ TW9900_ACNTL_I, 0x80 },
	/* "internal current reference 2" */
	{ TW9900_ACNTL_I, 0x40 },
};

/* Adjust for PAL vs NTSC */
static const struct tw9900_regval tw9900_pal_regs[] = {
	{ TW9900_CROP_HI, 0x12 },
	{ TW9900_VDELAY_LO, 0x19 },
	{ TW9900_VACTIVE_LO, 0x20 },
	{ TW9900_HDELAY_LO, 0x0a },
	{ TW9900_HACTIVE_LO, 0xd0 },
	{ TW9900_VVBI, 0x00 },
	{ TW9900_CNTRL2, 0x00 },
	{ TW9900_SDT_NOISE, 0x11 },
	{ TW9900_LUMA_CTL, 0x00 },
};

static const struct tw9900_regval tw9900_ntsc_regs[] = {
	{ TW9900_CROP_HI, 0x02 },
	{ TW9900_VDELAY_LO, 0x14 },
	{ TW9900_VACTIVE_LO, 0xf2 },
	{ TW9900_HDELAY_LO, 0x10 },
	{ TW9900_HACTIVE_LO, 0xd0 },
	{ TW9900_VVBI, 0x10 },
	{ TW9900_CNTRL2, 0x00 },
	{ TW9900_SDT_NOISE, 0x11 },
	{ TW9900_LUMA_CTL, 0x00 },
};

static struct tw9900_platform_data tw9900_pdata = {
	.init_regs = tw9900_init_regs,
	.n_init_regs = ARRAY_SIZE(tw9900_init_regs),
	.ntsc_regs = tw9900_ntsc_regs,
	.n_ntsc_regs = ARRAY_SIZE(tw9900_ntsc_regs),
	.pal_regs = tw9900_pal_regs,
	.n_pal_regs = ARRAY_SIZE(tw9900_pal_regs),
};

static struct i2c_board_info tw9900_info = {
	I2C_BOARD_INFO("tw9900", ADDR_TW9900 >> 1),
	.platform_data = &tw9900_pdata,
};

int usb3hdcap_composite_register(struct usb3hdcap *hdcap)
{
	hdcap->sd_tw9900 = v4l2_i2c_new_subdev_board(&hdcap->v4l2_dev,
						     &hdcap->i2c_adap,
						     &tw9900_info, NULL);
	if (!hdcap->sd_tw9900) {
		dev_warn(hdcap->dev, "Could not register TW9900\n");
		return -ENODEV;
	}

	hdcap->ctrl_brightness = v4l2_ctrl_find(&hdcap->ctrl,
						V4L2_CID_BRIGHTNESS);
	hdcap->ctrl_contrast = v4l2_ctrl_find(&hdcap->ctrl, V4L2_CID_CONTRAST);
	hdcap->ctrl_saturation = v4l2_ctrl_find(&hdcap->ctrl,
						V4L2_CID_SATURATION);
	hdcap->ctrl_hue = v4l2_ctrl_find(&hdcap->ctrl, V4L2_CID_HUE);
	hdcap->ctrl_sharpness = v4l2_ctrl_find(&hdcap->ctrl,
					       V4L2_CID_SHARPNESS);
	if (!hdcap->ctrl_brightness || !hdcap->ctrl_contrast ||
	    !hdcap->ctrl_saturation || !hdcap->ctrl_hue ||
	    !hdcap->ctrl_sharpness)
		return -ENODEV;

	v4l2_ctrl_s_ctrl(hdcap->ctrl_brightness, -9);
	v4l2_ctrl_s_ctrl(hdcap->ctrl_contrast, 0x79);
	v4l2_ctrl_s_ctrl(hdcap->ctrl_sharpness, 0x02);

	return 0;
}

/* Detect PAL vs NTSC from TW9900 auto-detection result */
static void usb3hdcap_detect_std(struct usb3hdcap *hdcap)
{
	v4l2_std_id detected = V4L2_STD_UNKNOWN;
	int ret;

	ret = v4l2_subdev_call(hdcap->sd_tw9900, video, querystd, &detected);
	if (ret == -ETIMEDOUT) {
		dev_warn(hdcap->dev, "Detection not done, using NTSC\n");
		hdcap->std = V4L2_STD_NTSC;
	} else if (detected & V4L2_STD_NTSC) {
		hdcap->std = V4L2_STD_NTSC;
		dev_info(hdcap->dev, "NTSC detected\n");
	} else if (detected & V4L2_STD_PAL) {
		hdcap->std = V4L2_STD_PAL;
		dev_info(hdcap->dev, "PAL detected\n");
	} else { /* not sure if this will be hit, because others are disabled */
		hdcap->std = V4L2_STD_NTSC;
		dev_info(hdcap->dev, "Non-PAL/NTSC detected\n");
	}

	v4l2_subdev_call(hdcap->sd_tw9900, video, s_std, hdcap->std);

	hdcap->detected_timings_present = 0;
}

/* Detect 240p/288p vs 480i/576i */
static void usb3hdcap_detect_size(struct usb3hdcap *hdcap)
{
	struct v4l2_subdev_format fmt = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	int ret;
	int full_h = (hdcap->std & V4L2_STD_PAL) ? PAL_HEIGHT : NTSC_HEIGHT;
	int half_h = full_h / 2;

	hdcap->width = SD_WIDTH;
	hdcap->height = half_h;
	hdcap->bpl = hdcap->width * 2;

	/* the TW9900 reports a half height frame if the source is progressive */
	ret = v4l2_subdev_call(hdcap->sd_tw9900, pad, get_fmt, NULL, &fmt);
	if (ret >= 0 && fmt.format.height == half_h) {
		hdcap->interlaced = 0;
		dev_info(hdcap->dev, "%dp detected\n", half_h);
	} else {
		hdcap->interlaced = 1;
		dev_info(hdcap->dev, "%di detected\n", full_h);
	}
}

int usb3hdcap_composite_init(struct usb3hdcap *hdcap)
{
	int k, ret;
	u32 status = 0;

	/* disable MST3367 */
	v4l2_subdev_call(hdcap->sd_mst3367, video, s_routing,
			 MST3367_INPUT_NONE, 0, 0);

	/* select TW9900 input of cpld? */
	/* from windows driver */
	if (u3hc_i2c_read(hdcap, ADDR_CPLD, 0x3b) != 0)
		u3hc_i2c_write(hdcap, ADDR_CPLD, 0x3b, 0x80);
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x20, 0x05);
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x00, 0x01);
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x10, hdcap->has_mcu ? 0xfc : 0xfe);
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x20, 0x75);

	ret = v4l2_subdev_call(hdcap->sd_tw9900, video, s_routing,
			       hdcap->input == INPUT_SVIDEO ?
			       TW9900_INPUT_SVIDEO : TW9900_INPUT_COMPOSITE,
			       0, 0);
	if (ret < 0)
		return ret;

	for (k = 0; k < 10; k++) {
		ret = v4l2_subdev_call(hdcap->sd_tw9900, video, g_input_status,
				       &status);
		if (ret >= 0 && !status) {
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

	return 0;
}
