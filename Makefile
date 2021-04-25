TARGETS:= 
all:: $(TARGETS)

OBJS:= tokens.o

tokens.o: tokens.c tokens.h

.PHONY : clean
clean:
	rm -f $(OBJS) 
