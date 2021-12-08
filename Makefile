TARGETS:= tcalc

CC=/usr/bin/afl-gcc
#CC=gcc
#CC=clang

CFLAGS = -std=c11 -Wall -pedantic -g -fno-omit-frame-pointer

CFLAGS += -Wextra -Wfloat-equal -Wshadow                         \
-Wpointer-arith -Wbad-function-cast -Wcast-align -Wwrite-strings \
-Wconversion -Wunreachable-code 

LDLIBS = -lm 



#CFLAGS += -fsanitize=address
#LDLIBS += -fsanitize=address

all:: $(TARGETS)
OBJS:= tcalc.o tokens.o calculation.o data_structure.o

tcalc: $(OBJS)

calculation.o: calculation.c tcalc.h data_structure.h
data_structure.o: data_structure.c data_structure.h tcalc.h
tcalc.o: tcalc.c tcalc.h
tokens.o: tokens.c tcalc.h


.PHONY : clean style

style:
	astyle -n -o -A8 -xt0 *.[ch]


clean:
	rm -f $(OBJS) 

bin: all clean
	cp $(TARGETS) ~/bin/


