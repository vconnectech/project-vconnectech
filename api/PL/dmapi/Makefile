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

DMA_App: $(OBJ)
	$(CC) -o $@  xaxidma_hw.c xaxidma.c  xaxidma_example_simple_poll.c  xaxidma_g.c  xaxidma_sinit.c

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ DMA_App 
