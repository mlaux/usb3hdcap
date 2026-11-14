// SPDX-License-Identifier: GPL-2.0
/*
 * USB3HDCAP MST3367 support: HDMI and component
 */

#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/usb.h>
#include <media/i2c/mst3367.h>
#include <media/v4l2-dv-timings.h>

#include "usb3hdcap.h"

static struct i2c_board_info mst3367_info = {
	I2C_BOARD_INFO("mst3367", ADDR_MST3367 >> 1),
};

int usb3hdcap_hdmi_register(struct usb3hdcap *hdcap)
{
	hdcap->sd_mst3367 = v4l2_i2c_new_subdev_board(&hdcap->v4l2_dev,
						      &hdcap->i2c_adap,
						      &mst3367_info, NULL);
	if (!hdcap->sd_mst3367) {
		dev_warn(hdcap->dev, "Could not register MST3367\n");
		return -ENODEV;
	}

	return 0;
}

/* XCAPTURE-1: the hot plug detect signal also has to be sent to the CPLD */
void usb3hdcap_hdmi_hotplug(struct usb3hdcap *hdcap, bool hotplug)
{
	if (!hdcap->has_mcu)
		return;

	if (hotplug)
		u3hc_i2c_rmw(hdcap, ADDR_CPLD, 0x01, 0xfd, 0x01);
	else
		u3hc_i2c_rmw(hdcap, ADDR_CPLD, 0x01, 0xff, 0x03);
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x11, 0xfc);
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

/* Program the MST3367 for the timings it detected and pick up the format */
static int usb3hdcap_set_detected_timings(struct usb3hdcap *hdcap,
					  struct v4l2_dv_timings *timings)
{
	struct v4l2_subdev_format fmt = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.pad = MST3367_PAD_SOURCE,
	};
	int ret;

	ret = v4l2_subdev_call(hdcap->sd_mst3367, pad, s_dv_timings, 0, timings);
	if (ret < 0)
		return ret;

	ret = v4l2_subdev_call(hdcap->sd_mst3367, pad, get_fmt, NULL, &fmt);
	if (ret < 0)
		return ret;

	hdcap->mst_bt601 = fmt.format.colorspace == V4L2_COLORSPACE_SMPTE170M;

	hdcap->detected_timings = *timings;
	hdcap->detected_timings_present = 1;
	hdcap->std = 0; /* no SD standard */
	hdcap->width = timings->bt.width;
	hdcap->interlaced = timings->bt.interlaced;
	hdcap->height = timings->bt.interlaced
		? timings->bt.height / 2 : timings->bt.height;
	hdcap->bpl = hdcap->width * 2;

	return 0;
}

/* ------------------------------------------------------------------ */
/* Main HDMI init entry point                                         */
/* ------------------------------------------------------------------ */

int usb3hdcap_hdmi_init(struct usb3hdcap *hdcap)
{
	struct v4l2_dv_timings timings;
	int ret;

	/* CPLD init with HDMI input mux */
	cpld_init(hdcap, 0x02);

	ret = v4l2_subdev_call(hdcap->sd_mst3367, video, s_routing,
			       MST3367_INPUT_HDMI, 0, 0);
	if (ret < 0)
		return ret;

	ret = v4l2_subdev_call(hdcap->sd_mst3367, pad, query_dv_timings, 0,
			       &timings);
	if (ret < 0)
		return ret;

	ret = usb3hdcap_set_detected_timings(hdcap, &timings);
	if (ret < 0)
		return ret;

	dev_info(hdcap->dev, "hdmi_init: complete (%dx%d)\n",
		 hdcap->width, hdcap->height);
	return 0;
}

/* ------------------------------------------------------------------ */
/* Main component init entry point                                    */
/* ------------------------------------------------------------------ */

int usb3hdcap_component_init(struct usb3hdcap *hdcap)
{
	struct v4l2_dv_timings timings;
	int ret, use_height;

	/* CPLD init with component input mux */
	cpld_init(hdcap, 0x80);

	ret = v4l2_subdev_call(hdcap->sd_mst3367, video, s_routing,
			       MST3367_INPUT_COMPONENT, 0, 0);
	if (ret < 0)
		return ret;

	/* Component CPLD routing, bit 4 = component input? */
	u3hc_i2c_read(hdcap, ADDR_CPLD, 0x20);
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x20, 0x15);

	/*
	 * Wait for ADC to stabilize, windows driver does this but might be able
	 * to decrease wait
	 */
	msleep(1000);

	/* Final CPLD verify */
	u3hc_i2c_read(hdcap, ADDR_CPLD, 0x20);
	u3hc_i2c_write(hdcap, ADDR_CPLD, 0x20, 0x15);

	ret = v4l2_subdev_call(hdcap->sd_mst3367, pad, query_dv_timings, 0,
			       &timings);
	if (ret < 0)
		return ret;

	u3hc_i2c_rmw(hdcap, ADDR_CPLD, 0x00, 0xff, 0x02);

	ret = usb3hdcap_set_detected_timings(hdcap, &timings);
	if (ret < 0)
		return ret;

	use_height = hdcap->interlaced ? hdcap->height * 2 : hdcap->height;
	dev_info(hdcap->dev, "component_init: complete (%dx%d%s)\n",
		 hdcap->width, use_height,
		 hdcap->interlaced ? "i" : "p");
	return 0;
}
