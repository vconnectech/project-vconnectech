IDIR =.
BUILD = ../../../build
CC=aarch64-linux-gnu-gcc
AR=aarch64-linux-gnu-ar
CFLAGS=-I$(IDIR)

ODIR=.
LDIR =./lib

INC_DIR = ../../common/ -I ../../PS/iic/
CFLAGS = -I $(INC_DIR)

SRC = dp159.c          \
     audiogen_drv.c     \
     si5324drv.c        \
     aes256.c           \
     idt_8t49n24x.c     \
     platform.c         \
     sha256.c           \
     xhdcp.c            \
     xhdmi_hdcp_keys.c  \
     xhdmi_edid.c       \
     xvidframe_crc.c


OBJ = $(SRC:.c=.o)

HDMI_API.a: 
	$(CC) -o $(SRC) $< $(CFLAGS) -L$(BUILD)
	$(AR) rcs $@ $(OBJ)
	cp -f $@ $(BUILD)/.

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~  *.gch *.a
