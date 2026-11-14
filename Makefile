obj-m += usb3hdcap.o mst3367.o tw9900.o
usb3hdcap-y := usb3hdcap-core.o usb3hdcap-video.o usb3hdcap-composite.o \
               usb3hdcap-hdmi.o usb3hdcap-audio.o
ccflags-y += -I$(src)/include
# tw9900.c is the media/next version
ccflags-y += $(shell grep -qs v4l2_subdev_client_info \
	$(srctree)/include/media/v4l2-subdev.h && echo -DHAVE_SUBDEV_CLIENT_INFO)
KCFLAGS=-W
KDIR ?= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
