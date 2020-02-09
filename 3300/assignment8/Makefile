CFLAGS = -g -Wall -Wshadow -Wuninitialized -O
CC     = g++
LINK   = g++
OFILES = pqueue.o huffman.o trace.o binary2.o

test: huffman
	./huffman

debug: huffman
	gdb ./huffman

huffman : $(OFILES)
	$(LINK) -o huffman $(OFILES) 

pqueue.o: pqueue.cpp pqueue.h
	$(CC) $(CFLAGS) -c pqueue.cpp

binary2.o: binary2.cpp binary.h
	$(CC) $(CFLAGS) -c binary2.cpp

trace.o: trace.cpp trace.h
	$(CC) $(CFLAGS) -c trace.cpp

huffman.o: huffman.cpp pqueue.h trace.h binary.h
	$(CC) $(CFLAGS) -c huffman.cpp

clean: 
	rm $(OFILES) huffman
