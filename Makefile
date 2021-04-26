TARGETS:= style tcalc

CFLAGS = -std=c11 -Wall -pedantic -g

CFLAGS += -Wextra -Wfloat-equal -Wshadow                         \
-Wpointer-arith -Wbad-function-cast -Wcast-align -Wwrite-strings \
-Wconversion -Wunreachable-code

all:: $(TARGETS)
OBJS:= tcalc.o tokens.o

tcalc: $(OBJS)

tcalc.o: tcalc.c tcalc.h tokens.h error.h
tokens.o: tokens.c tokens.h

.PHONY : clean style

style:
	astyle -n -oO -A1 -xt0 *.[ch]

clean:
	rm -f $(OBJS) $(TARGETS)
