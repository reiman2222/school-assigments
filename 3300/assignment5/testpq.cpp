#include <cstdio>
#include "pqueue.h"
using namespace std;

void printString(const char* s)
{
	printf("%s", s);
}

void printDouble(double x)
{
	printf("%lf", x);
}

int main(int argc, char** argv)
{
	

	PriorityQueue h = PriorityQueue();
	
	printPriorityQueue(h, printString, printDouble);
	//PQCell x;
	//h.priorityQ = &x;
	/*
	if(isEmpty(h))
	{
		printf("Queue is empty.\n");
	}
	else
	{
		printf("Queue is NOT empty.\n");
	}
	*/
	
	insert("cow", 5.0, h);
	insert("cat", 3.0, h);
	insert("lemming", 8.0, h);
	insert("fish", 10.0, h);
	insert("swan", 1.0, h);
	
	
	
	printPriorityQueue(h, printString, printDouble);
	PQItemType a;
	PQPriorityType b;
	
	printf("doing remove\n");
	remove(a, b, h);
	printf("items was: ");
	printString(a);
	printf("\n");
	
	printf("priority was: ");
	printDouble(b);
	printf("\n");
	
	
	printPriorityQueue(h, printString, printDouble);
	
	printf("doing remove\n");
	remove(a, b, h);
	printf("items was: ");
	printString(a);
	printf("\n");
	
	printf("priority was: ");
	printDouble(b);
	printf("\n");
	
	printPriorityQueue(h, printString, printDouble);
	
	insert("ferret", 45.0, h);
	
	printPriorityQueue(h, printString, printDouble);
	
	return 0;
}
