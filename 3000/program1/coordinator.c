//Jack Edwards
//CSCI 3000
//1-30-18


#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <stdlib.h>

//argArrayToIntArray(argc, argv) converts the argument arrray to an 
//array of intergers, the array returned will always have an even size.
int* argArrayToIntArray(int argc, const char** argv){
	int newSize;
	int even = ((argc - 1) % 2 == 0);
	if(even){
		newSize = argc - 1;
		
	}else{
		newSize = argc;
	}
	
	int* numbers = (int *)malloc(sizeof(int)*newSize);
	
	int i = 1;
	while(i < argc){
		sscanf(argv[i], "%d", &numbers[i - 1]);
		i++;
	}
	
	if(even == 0){
		numbers[newSize - 1] = 0;
	}
	
	return numbers;
}

//makeArrayHalfSize(n, size) returns half of size if size/2 is even and
//half of size + 1 if size/2 is odd. size is the original size of the array n.
int makeArrayHalfSize(int* n, int size){
	int halfSize = size/2;

	int even = (halfSize % 2 == 0);
	if(halfSize == 1){
		return halfSize;

	}else if(even){
		return halfSize;

	}else{
		halfSize++;
		n[halfSize - 1] = 0;
		return halfSize;
	}
}

//sizeOfArgArray(argc) returns size of the evenly sized argument
//array. argc is the size of the argument array.
int sizeOfArgArray(int argc){
	int newSize;
	int even = ((argc - 1) % 2 == 0);
	if(even){
		newSize = argc - 1;
		
	}else{
		newSize = argc;
	}
	return newSize;
}

//makeWorker(n1, n2, p) creates a worker process to add n1 and n2 and
//return the result. p stores the process id of the worker. 
//n1 and n2 are the numbers to add.
int makeWorker(int n1, int n2, int* p){
	char num1[16];
	char num2[16];
	int answer;
	
	int pid = fork();
	
 
	if(pid == 0){
		sprintf(num1, "%d", n1);
		sprintf(num2, "%d", n2);
	
		execlp("./worker.o", "./worker.o", num1 , num2, NULL);
		
	}else{
		waitpid(pid, &answer, 0);
		answer = WEXITSTATUS(answer);
		*p = pid;
		return answer;
	}
	
	
}

int main(int argc, const char** argv){
	
	int* n = argArrayToIntArray(argc, argv);
	int size = sizeOfArgArray(argc);
	
	int pid;	
	
	int i;
	int j;
	while(size > 1){
		j = 0;
		for(i = 0; i < size; i += 2){
			n[j] = makeWorker(n[i], n[i + 1], &pid);
			printf("pid of worker: %d result: %d\n", pid, n[j]);

			j++;
		}
		
		size = makeArrayHalfSize(n, size);
		
	}

	printf("Total is: %d\n", n[0]);


	return 0;
}
