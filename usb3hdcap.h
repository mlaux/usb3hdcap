/* SPDX-License-Identifier: GPL-2.0 */
#ifndef USB3HDCAP_H
#define USB3HDCAP_H

#include <linux/usb.h>
#include <media/v4l2-device.h>
#include <media/v4l2-ctrls.h>
#include <media/videobuf2-v4l2.h>

struct snd_card;
struct snd_pcm_substream;
struct vb2_ops;

/* NTSC SD frame format */
#define NTSC_WIDTH     720
#define NTSC_HEIGHT    480
/* YUYV = 4 bytes/2 pixels */
#define DEFAULT_BPL    (NTSC_WIDTH * 2)
/* PAL SD frame format */
#define PAL_HEIGHT    576

enum usb3hdcap_input {
	INPUT_COMPOSITE = 0,
	INPUT_SVIDEO    = 1,
	INPUT_COMPONENT = 2,
	INPUT_HDMI      = 3,
};

/* I2C 8-bit addresses */
#define ADDR_MST3367 0x9c
#define ADDR_TW9900  0x88
#define ADDR_CS53L21 0x94
#define ADDR_CPLD    0x98
#define ADDR_MCU     0x64 /* Nuvoton NUC100 on XCAPTURE-1 */

/* Vendor request codes */
#define REQ_I2C    0xc0
#define REQ_GPIO   0xc1
#define REQ_INIT   0xc2
#define REQ_STREAM 0xc6
#define REQ_UNK_C7 0xc7

/* Isochronous transfer parameters */
#define EP_VIDEO       0x83
#define NUM_XFERS      8
#define NUM_ISO_PKTS   64

/* 
 * Stream framing: two element types in the byte stream, both
 * starting with ff 00:
 *   SAV (ff 00 00 XY): bpl-1 pixel bytes, -1 because the XY is actually
 *   in the first pixel's V position... weird but it's correct
 *   Marker (ff 00 ff NN):  audio - NN = number of stereo s16le
 *                          samples, audio data = NN * 4 bytes
 */
#define SAV_LEN        4
#define MARKER_LEN     4
#define PARSE_BUF_SIZE (2 * 1024 * 1024)

/* BT.656 SAV XY bits */
#define BT656_F_BIT    0x40
#define BT656_V_BIT    0x20

struct hdcap_buf {
	struct vb2_v4l2_buffer vb;
	struct list_head list;
};

struct usb3hdcap {
	struct device *dev;
	struct usb_device *usb_dev;
	struct v4l2_device v4l2_dev;
	struct video_device video_dev;
	struct vb2_queue vb2q;
	struct v4l2_ctrl_handler ctrl;
	struct v4l2_ctrl *ctrl_brightness;
	struct v4l2_ctrl *ctrl_contrast;
	struct v4l2_ctrl *ctrl_saturation;
	struct v4l2_ctrl *ctrl_hue;
	struct v4l2_ctrl *ctrl_sharpness;
	struct mutex v4l2_lock;
	struct mutex vb2q_lock;

	/* buffer list */
	spinlock_t buflock;
	struct list_head bufs;

	/* ISO URBs */
	int iso_size;
	struct urb *isoc_urbs[NUM_XFERS];

	/* frame tracking */
	unsigned int sequence;

	/* input selection + format */
	enum usb3hdcap_input input;
	v4l2_std_id std;
	int width;
	int height;
	int interlaced;
	int bpl; /* width * 2 */

	/* stream parser state */
	u8 *parse_buf;
	int parse_len;
	struct hdcap_buf *cur_buf;
	int frame_line;
	int synced;
	int was_blanking;
	int is_second_field;

	/* hardware init state */
	int hw_inited;
	int has_mcu; /* Nuvoton MCU present (XCAPTURE-1) */

	/* MST3367 state */
	int mst_current_bank;
	struct v4l2_dv_timings detected_timings;

	/* ALSA audio */
	struct snd_card *snd;
	struct snd_pcm_substream *snd_substream;
	atomic_t snd_stream;
	size_t snd_buffer_pos;
	size_t snd_period_pos;

	/* diagnostics */
	unsigned int iso_cb_count;
	unsigned long iso_bytes;
	unsigned int markers_found;
	unsigned int frames_delivered;
};

/* USB control helpers (usb3hdcap-core.c) */
int vendor_out(struct usb3hdcap *hdcap, u8 request, u16 value, u16 index,
	       u8 *data, u16 len);
int u3hc_i2c_write(struct usb3hdcap *hdcap, u8 addr, u8 reg, u8 val);
int u3hc_i2c_read(struct usb3hdcap *hdcap, u8 addr, u8 reg);
int u3hc_i2c_rmw(struct usb3hdcap *hdcap, u8 addr, u8 reg, u8 mask, u8 bits);
int u3hc_i2c_rmw_get_old(struct usb3hdcap *hdcap, u8 addr, u8 reg, u8 mask, u8 bits, u8 *old);
int usb3hdcap_hw_init(struct usb3hdcap *hdcap);

/* Composite (usb3hdcap-composite.c) */
int usb3hdcap_composite_init(struct usb3hdcap *hdcap);

/* HDMI + Component (usb3hdcap-hdmi.c) */
int usb3hdcap_hdmi_init(struct usb3hdcap *hdcap);
int usb3hdcap_component_init(struct usb3hdcap *hdcap);

/* Video/streaming (usb3hdcap-video.c) */
extern const struct vb2_ops usb3hdcap_vb2_ops;

/* Audio (usb3hdcap-audio.c) */
int usb3hdcap_cs53l21_init(struct usb3hdcap *hdcap);
int usb3hdcap_audio_init(struct usb3hdcap *hdcap);
void usb3hdcap_audio_free(struct usb3hdcap *hdcap);
void usb3hdcap_audio_data(struct usb3hdcap *hdcap, const u8 *data, int len);

#endif
