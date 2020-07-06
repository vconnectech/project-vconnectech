csrc = $(wildcard $(PWD)/*.c) \
       $(wildcard $(PWD)/api/PL/dmapi/*.c) \
       $(wildcard $(PWD)/api/PS/iic/*.c)
obj = $(csrc:.c=.o) $(ccsrc:.cc=.o)

LDFLAGS = -lGL -lglut -lpng -lz -lm

.PHONY: install
install: DMA_API 
    mkdir -p $(DESTDIR)$(PREFIX)/binary
    cp $< $(DESTDIR)$(PREFIX)/binary/DMA_API

#/home/unique/TestGIT/api/PL/dmapi
