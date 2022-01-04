TARGETS:= tcalc
PWD = ${shell pwd}

CC=gcc

CFLAGS = -std=c11 -Ofast

all:: $(TARGETS)

test: CFLAGS += -pedantic -Wall -Wextra -Wfloat-equal -Wshadow                         \
-Wpointer-arith -Wbad-function-cast -Wcast-align -Wwrite-strings \
-Wconversion -Wunreachable-code -g -fno-omit-frame-pointer

debug: tcalc
debug: CFLAGS += -g
debug: CFLAGS += -pedantic -Wall -Wextra -Wfloat-equal -Wshadow                         \
-Wpointer-arith -Wbad-function-cast -Wcast-align -Wwrite-strings \
-Wconversion -Wunreachable-code -g -fno-omit-frame-pointer

#LDLIBS = -lm -lreadline 
LDLIBS = -lm -ledit
test: LDLIBS  += -lcheck


#coverage
coverage: CFLAGS += -fprofile-arcs -ftest-coverage -g
coverage: LDLIBS += -lgcov --coverage

test: CFLAGS += -fsanitize=address 
test: LDLIBS += -fsanitize=address 





OBJS:= tcalc.o tokens.o calculation.o data_structure.o time.o input.o hashmap.o

tcalc: $(OBJS)


calculation.o: calculation.c calculation.h hashmap.h tokens.h  \
 data_structure.h
data_structure.o: data_structure.c data_structure.h tokens.h hashmap.h
hashmap.o: hashmap.c hashmap.h
input.o: input.c input.h calculation.h hashmap.h tokens.h time.h
tcalc.o: tcalc.c input.h
tests.o: tests.c data_structure.h tokens.h hashmap.h calculation.h \
 input.h
time.o: time.c time.h
tokens.o: tokens.c tokens.h hashmap.h input.h


coverage: test
	gcov *.c
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out
	firefox out/index.html


test: tests tcalc
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${PWD} ./tests < test_input

tests: tokens.o calculation.o data_structure.o time.o input.o hashmap.o


tests.o: tests.c  data_structure.h 

profile: CFLAGS += -g
profile: tcalc
	valgrind --tool=callgrind ./tcalc < profile_input
	callgrind_annotate  callgrind.out.*
	kcachegrind
	rm callgrind.out*
	make clean

valgrind: CFLAGS += -g
valgrind: tcalc
	valgrind   tcalc < profile_input

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

