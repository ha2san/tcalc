TARGETS:= tcalc

all:: $(TARGETS)
OBJS:= tcalc.o tokens.o

tcalc.o: tcalc.c tokens.h
tokens.o: tokens.c tokens.h

.PHONY : clean
clean:
	rm -f $(OBJS) $(TARGETS)
