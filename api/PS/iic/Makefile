IDIR =.
CC=aarch64-linux-gnu-gcc
CFLAGS=-I$(IDIR)

ODIR=.
LDIR =./lib

_DEPS = *.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

#_OBJ = xaxidma_hw.o xaxidma.o  xaxidma_example_simple_poll.o  xaxidma_g.o  xaxidma_sinit.o
#OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


#$(ODIR)/%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

#DMA_App: $(OBJ)
#	$(CC) -o $@  xaxidma_hw.c xaxidma.c  xaxidma_example_simple_poll.c  xaxidma_g.c  xaxidma_sinit.c
#	$(CC) -o $@  xiicps_hw.h  xiicps_g.c xiicps.c	xiicps_options.c xiicps_selftest.c

IIC_App: $(OBJ)
	$(CC) -o $@   xiicps_g.c  xiicps.c   xiicps_hw.c  xiicps_selftest_example.c  xil_assert.h xiicps_sinit.c xiicps_selftest.c xiicps_options.c xil_assert.c  xplatform_info.c xiicps_hw.c xil_io.c 

	#$(CC) -o $@   xiicps_g.c  xiicps.c  xiicps_options.c  xiicps_master.c  xiicps_slave.c xiicps_hw.c xiicps_selftest.c xiicps_selftest_example.c 
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ IIC_App 
