#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char** argv){
	int n1;
	int n2;
	int answer;

	sscanf(argv[1], "%d", &n1);
	sscanf(argv[2], "%d", &n2);
		
	answer = n1 + n2;
	printf("pid: %d operand: %d, %d sum: %d\n", getpid(), n1, n2, answer);
	
	exit(answer);
}
