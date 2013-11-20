IDIR =../include
CC=/opt/gcc/il-4_4_4/bin/gcc
CFLAGS=-I$(IDIR)

ODIR=.
LDIR =../lib

LIBS=-lm

_DEPS = input.h stack.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = input.o stack.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

calc: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

obj/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ calc
