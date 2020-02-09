compile worker.c with: gcc worker.c -o worker.o

compile coordinator.c with: gcc coordinator.c -o coordinator.o

Coordinator takes a series of integers from the command line and uses
multiple process to compute the sum of said integers

If coordinator.o is in your current directory use 
this command to run: ./coordinator.o 1 2 3 4 5

coordinator.o will report that the sum is 15.


