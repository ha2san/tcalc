TARGETS:= src/tcalc
PWD = ${shell pwd}

CC=gcc

CFLAGS = -std=c11 -Ofast

all:: $(TARGETS)
	mv src/tcalc bin/tcalc

cflags_d = -pedantic -Wall -Wextra -Wfloat-equal -Wshadow   \
-Wpointer-arith -Wbad-function-cast -Wcast-align -Wwrite-strings \
-Wconversion -Wunreachable-code -g -fno-omit-frame-pointer

test: CFLAGS += $(cflags_d)

debug: all 
debug: CFLAGS += -g
debug: CFLAGS += $(cflags_d)

#LDLIBS = -lm -lreadline 
LDLIBS = -lm -ledit
test: LDLIBS  += -lcheck


#coverage
coverage: CFLAGS += -fprofile-arcs -ftest-coverage -g
coverage: LDLIBS += -lgcov --coverage

test: CFLAGS += -fsanitize=address 
test: LDLIBS += -fsanitize=address 

OBJS:= src/tcalc.o src/tokens.o src/calculation.o src/data_structure.o src/time.o \
 src/input.o src/hashmap.o

src/tcalc: $(OBJS)


src/calculation.o: src/calculation.c src/calculation.h src/hashmap.h \
 src/tokens.h src/data_structure.h
src/data_structure.o: src/data_structure.c src/data_structure.h src/tokens.h \
 src/hashmap.h
src/hashmap.o: src/hashmap.c src/hashmap.h
src/input.o: src/input.c src/input.h src/calculation.h src/hashmap.h \
 src/tokens.h src/time.h
src/tcalc.o: src/tcalc.c src/input.h
src/time.o: src/time.c src/time.h
src/tokens.o: src/tokens.c src/tokens.h src/hashmap.h src/input.h
test/tests.o: test/tests.c src/data_structure.h src/tokens.h \
 src/hashmap.h src/calculation.h src/input.h


coverage: test
	gcov src/*.c
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out
	firefox out/index.html


test: test/tests src/tcalc
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${PWD} ./test/tests < test/test_input

test/tests: src/tokens.o src/calculation.o src/data_structure.o src/time.o src/input.o src/hashmap.o



profile: CFLAGS += -g
profile: all 
	valgrind --tool=callgrind bin/tcalc < test/profile_input
	callgrind_annotate  callgrind.out.*
	kcachegrind
	rm callgrind.out*
	make clean

valgrind: CFLAGS += -g
valgrind: all 
	valgrind   bin/tcalc < test/profile_input

.PHONY : clean style test

style:
	astyle -n -o -A8 -xt0 *.[ch]


clean:
	rm -f $(OBJS) test/*.o
	rm -f test/tests
	rm -f $(TARGETS)
	rm -f bin/* 
	rm -f *.gcda *.gcda *.gcno *.gcov coverage.info
	rm -rf out/

bin: clean all
	cp bin/tcalc ~/bin/

