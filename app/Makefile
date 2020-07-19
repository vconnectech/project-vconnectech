SUBDIRS := iic_ps  

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS) 

.PHONY: clean

clean:
	rm -f $(PWD)/iic_ps/IIC_APP 

