IDIR =.
BUILD = ../../../build
CC=aarch64-linux-gnu-gcc
AR=aarch64-linux-gnu-ar
CFLAGS=-I$(IDIR)

ODIR=.
LDIR =./lib

INC_DIR = ../../common/
CFLAGS = -I $(INC_DIR)

SRC = 



OBJ = $(SRC:.c=.o)

IIC_API.a: 
	$(CC) -c $(SRC) $< $(CFLAGS)
	$(AR) rcs $@ $(OBJ)
	cp -f $@ $(BUILD)/.

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~  *.gch *.a
