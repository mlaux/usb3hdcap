obj-m += usb3hdcap.o
usb3hdcap-y := usb3hdcap-core.o usb3hdcap-video.o usb3hdcap-composite.o \
               usb3hdcap-hdmi.o usb3hdcap-audio.o
KDIR ?= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
