IDIR =.
BUILD = ../../../build
CC=aarch64-linux-gnu-gcc
AR=aarch64-linux-gnu-ar
CFLAGS=-I$(IDIR)

ODIR=.
LDIR =./lib

INC_DIR = ../../../common/
CFLAGS = -I $(INC_DIR)

#xiicps.c     \
      xiicps_g.c   \
      xiicps_hw.c  \
      xiicps_intr.c \
      xiicps_options.c \
      xiicps_sinit.c   \
      xiicps_master.c  \
      xiicps_slave.c

SRC = xiic_l.c     \
      xiic_g.c   \
      xiic_intr.c \
      xiic_options.c \
      xiic_sinit.c   \
      xiic_master.c  \
      xiic_slave.c   

OBJ = $(SRC:.c=.o)

IIC_API_PL.a: 
	$(CC) -c $(SRC) $< $(CFLAGS)
	$(AR) rcs $@ $(OBJ)
	cp -f $@ $(BUILD)/.

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~  *.gch *.a
