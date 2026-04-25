.PHONY: all clean

CFLAGS = -Wall
LIBS = -lm
SRC = $(wildcard *.c)
BINDIR = bin
OUT = $(patsubst %.c,$(BINDIR)/%,$(SRC))

all: $(BINDIR) $(OUT)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -rf $(BINDIR)
