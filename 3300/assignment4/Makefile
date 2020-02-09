CFLAGS = -g -Wall -Wshadow -Wuninitialized -O
CC     = g++
LINK   = g++
OFILES = mst.o equiv.o

test: mst
	./mst

debug: mst
	gdb ./mst

mst : $(OFILES)
	$(LINK) -o mst $(OFILES) 

equiv.o: equiv.cpp equiv.h
	$(CC) $(CFLAGS) -c equiv.cpp

mst.o: mst.cpp equiv.h
	$(CC) $(CFLAGS) -c mst.cpp

clean: 
	rm $(OFILES) mst

