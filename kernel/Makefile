export ARCH=arm64
export CROSS_COMPILE=aarch64-linux-gnu-
SUBDIRS := linux-xlnx u-boot-xlnx dts 

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)
