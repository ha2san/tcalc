TARGETS:= src/tcalc
BINARY:= bin/tcalc
PWD = ${shell pwd}

CC=gcc

CFLAGS = -std=c11 -Ofast
LDLIBS = -lm -ledit

OBJS:= src/tcalc.o src/tokens.o src/calculation.o src/data_structure.o src/time.o \
 src/input.o src/hashmap.o

cflags_d = -pedantic -Wall -Wextra -Wfloat-equal -Wshadow   \
-Wpointer-arith -Wbad-function-cast -Wcast-align -Wwrite-strings \
-Wconversion -Wunreachable-code -g -fno-omit-frame-pointer

all:: $(TARGETS)
	mkdir -p bin/
	mv $(TARGETS) $(BINARY) 

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


test: test/tests src/tcalc
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${PWD} ./test/tests < test/test_input
test: CFLAGS += -fsanitize=address $(cflags_d)
test: LDLIBS += -fsanitize=address -lcheck
test/tests: src/tokens.o src/calculation.o src/data_structure.o src/time.o src/input.o src/hashmap.o


debug: all 
debug: CFLAGS += -g
debug: CFLAGS += $(cflags_d)

coverage: CFLAGS += -fprofile-arcs -ftest-coverage -g
coverage: LDLIBS += -lgcov --coverage
coverage: test 
	gcov src/*.c
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out
	firefox out/index.html

profile: CFLAGS += -g
profile: all 
	valgrind --tool=callgrind $(BINARY) < test/profile_input
	callgrind_annotate  callgrind.out.*
	kcachegrind
	rm callgrind.out*
	make clean

valgrind: CFLAGS += -g
valgrind: all 
	valgrind   $(BINARY) < test/profile_input

.PHONY : clean style test

style:
	astyle -n -o -A8 -xt0 src/*.[ch]


CLEAN_OBJS = $(OBJS) test/*.o test/tests $(TARGETS) $(BINARY) *.gc*  \
			 coverage.info src/*.gc*  out/ test/*.gc*
clean:
	rm -rfv $(CLEAN_OBJS)
#	rm -f $(OBJS) test/*.o
#	rm -f test/tests
#	rm -f $(TARGETS)
#	rm -f $(BINARY) 
#	rm -f *.gc*  coverage.info
#	rm -f src/*.gc* src/coverage.info
#	rm -rf out/
#	rm -rf test/*.gc*

bin: clean all
	cp $(BINARY) ~/bin/

