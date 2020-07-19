IDIR =.
BUILD = ../../build
CC=aarch64-linux-gnu-gcc
AR=aarch64-linux-gnu-ar
LD=aarch64-linux-gnu-ld
CFLAGS = -I$(IDIR)
ODIR=.
LDIR =./lib

_DEPS = *.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

INC_DIR = ../../api/common -I ../../api/PS/hdmips
CFLAGS = -I $(INC_DIR)


SRC =   xhdmi_example.c \
        xhdmi_menu.c


OBJ = $(SRC:.c=.o)

HDMI_APP: 
	$(CC) -o $@ $(SRC) $< $(CFLAGS) -L$(BUILD) -lCMN_API -lHDMI_API
#	$(LD) -o $@ $(OBJ) -L$(BUILD) -lCMN_API -lIIC_API  #-lzlib --verbose
	cp -f $@ $(BUILD)/.

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~  *.gch HDMI_APP
