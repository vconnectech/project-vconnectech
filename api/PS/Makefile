SUBDIRS :=  iic
#SUBDIRS :=  iic dmaps_v2_4  emacps_v3_8  gpiops_v3_5   spips_v3_2  uartps_v3_5  usbps_v2_4

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)
