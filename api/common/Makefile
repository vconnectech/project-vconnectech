IDIR =.
BUILD = ../../build
CC=aarch64-linux-gnu-gcc
AR=aarch64-linux-gnu-ar
CFLAGS=-I$(IDIR)

ODIR=.
LDIR =./lib

_DEPS = *.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

SRC = xil_io.c       \
      xil_assert.c    \
      xplatform_info.c 

OBJ = $(SRC:.c=.o)

CMN_API.a: 
	$(CC) -c $(SRC) 
	$(AR) rcs $@ $(OBJ)
	cp -f $@ $(BUILD)/.

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~  *.gch *.a
