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

INC_DIR = ../../api/common -I ../../api/PL/dmapl
CFLAGS = -I $(INC_DIR)


SRC =   xaxidma_example_simple_poll.c \
       xaxidma_selftest.c


OBJ = $(SRC:.c=.o)

DMA_APP: 
	$(CC) -o $@ $(SRC) $< $(CFLAGS) -L$(BUILD) -lCMN_API -lDMA_API
#	$(LD) -o $@ $(OBJ) -L$(BUILD) -lCMN_API -lIIC_API  #-lzlib --verbose
	cp -f $@ $(BUILD)/.

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~  *.gch DMA_APP
