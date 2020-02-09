CFLAGS = -g -Wall -Wshadow -Wuninitialized -O
CC     = g++
LINK   = g++
OFILES = equiv.o testequiv.o

test: testequiv
	./testequiv

debug: testequiv
	gdb ./testequiv

testequiv: $(OFILES)
	$(LINK) -o testequiv $(OFILES) 

equiv.o: equiv.cpp equiv.h
	$(CC) $(CFLAGS) -c equiv.cpp

testequiv.o: testequiv.cpp equiv.h
	$(CC) $(CFLAGS) -c testequiv.cpp

clean: 
	rm $(OFILES) testequiv

