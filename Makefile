TARGETS:= tcalc

CC=gcc

CFLAGS = -std=c11 -Wall -pedantic -g

CFLAGS += -Wextra -Wfloat-equal -Wshadow                         \
-Wpointer-arith -Wbad-function-cast -Wcast-align -Wwrite-strings \
-Wconversion -Wunreachable-code

LDLIBS = -lm

all:: $(TARGETS)
OBJS:= tcalc.o tokens.o calculation.o data_structure.o

tcalc: $(OBJS)

calculation.o: calculation.c tcalc.h data_structure.h
data_structure.o: data_structure.c data_structure.h tcalc.h
tcalc.o: tcalc.c tcalc.h
tokens.o: tokens.c tcalc.h


.PHONY : clean style

style:
	astyle -n -oO -A1 -xt0 *.[ch]

clean:
	rm -f $(OBJS) $(TARGETS)


