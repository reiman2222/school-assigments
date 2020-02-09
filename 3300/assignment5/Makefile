CFLAGS = -g -Wall -Wshadow -Wuninitialized -O
CC     = g++
LINK   = g++
OFILES = pqueue.o testpq.o

test: testpq
	./testpq

debug: testpq
	gdb ./testpq

testpq : $(OFILES)
	$(LINK) -o testpq $(OFILES) 

pqueue.o: pqueue.cpp pqueue.h
	$(CC) $(CFLAGS) -c pqueue.cpp

testpq.o: testpq.cpp pqueue.h
	$(CC) $(CFLAGS) -c testpq.cpp

clean: 
	rm $(OFILES) testpq

