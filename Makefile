TARGETS:= tcalc
PWD = ${shell pwd}

CC=gcc

CFLAGS = -std=c11 -Wall -pedantic -g -fno-omit-frame-pointer  -Ofast


CFLAGS += -Wextra -Wfloat-equal -Wshadow                         \
-Wpointer-arith -Wbad-function-cast -Wcast-align -Wwrite-strings \
-Wconversion -Wunreachable-code 


LDLIBS = -lm -lreadline 
test: LDLIBS  += -lcheck


#coverage
coverage: CFLAGS += -fprofile-arcs -ftest-coverage
coverage: LDLIBS += -lgcov --coverage

test: CFLAGS += -fsanitize=address
test: LDLIBS += -fsanitize=address


all:: $(TARGETS)
OBJS:= tcalc.o tokens.o calculation.o data_structure.o time.o input.o

tcalc: $(OBJS)

calculation.o: calculation.c tcalc.h data_structure.h
data_structure.o: data_structure.h tcalc.h
input.o: input.c tcalc.h
tcalc.o: tcalc.h 
time.o: time.h
tokens.o: tokens.c tcalc.h

coverage: test
	gcov *.c
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out
	firefox out/index.html


test: tests 
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${PWD} ./tests < test_input

tests: tokens.o calculation.o data_structure.o time.o input.o


tests.o: tests.c tcalc.h data_structure.h 


.PHONY : clean style test

style:
	astyle -n -o -A8 -xt0 *.[ch]


clean:
	rm -f $(OBJS) *.o
	rm -f tests
	rm -f $(TARGETS)
	rm -f *.gcda *.gcda *.gcno *.gcov coverage.info
	rm -rf out/

bin: clean all
	cp $(TARGETS) ~/bin/

