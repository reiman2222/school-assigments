CFLAGS = -g -Wall -Wshadow -Wuninitialized -O
CC     = g++
LINK   = g++
OFILES = unhuffman.o trace.o binary2.o

test: unhuffman
	./unhuffman

debug: unhuffman
	gdb ./unhuffman

unhuffman : $(OFILES)
	$(LINK) -o unhuffman $(OFILES) 

binary2.o: binary2.cpp binary.h
	$(CC) $(CFLAGS) -c binary2.cpp

trace.o: trace.cpp trace.h
	$(CC) $(CFLAGS) -c trace.cpp

unhuffman.o: unhuffman.cpp trace.h binary.h
	$(CC) $(CFLAGS) -c unhuffman.cpp

clean: 
	rm $(OFILES) unhuffman
