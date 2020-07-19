SUBDIRS := dmapi 
#SUBDIRS :=  emaclite_v4_3  gpio_v4_4  iic_v3_5  spi_v4_2  uartns550_v3_5  usb_v5_2

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)
