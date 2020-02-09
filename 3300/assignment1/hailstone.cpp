// CSCI 3300
// Assignment: 1
// Author:     Jack Edwards
// File:       hailstone.cpp
// Tab stops:  4

//This program asks the user to enter a number then prints the hailstone
//sequence of that number, the length of said hailstone sequence,
//the largest number in said hailstone sequence and the starting number
//and lenght of the longest hailstone sequence from that number to 1.

#include <cstdio>
using namespace std;

//next(n) calculates the next number in the hailstone sequence after n.
//Requires: n > 1
//next(4) = 2
//next(7) = 22

int next(int n)
{
	//true if n is even
	if((n % 2) == 0)
	{
		return n / 2;
	}
	else
	{
		return (3 * n) + 1;
	}
	
}

//printHailstoneSequence(n) prints the hailstone sequence starting
//at n to the standard output.

void printHailstoneSequence(int n)
{
	int nextNum = n;
	
	printf("%i ", nextNum);
	while(nextNum != 1)
	{
		nextNum = next(nextNum);
		printf("%i ", nextNum);
	}
	printf("\n");
	
}

//hailstoneLength(n) returns the length of the hailstone sequence 
//starting at n.

int hailstoneLength(int n)
{
	int nextNum = n;
	int length = 1;
	
	while(nextNum != 1)
	{
		nextNum = next(nextNum);
		length++;
	}
	return length;
	
}

//largestNumber(n) returns the latgest number in the 
//hailstone sequence starting at n.

int largestNumber(int n)
{
	int nextNum = n;
	int largestNum = n;
	
	while(nextNum != 1)
	{
		nextNum = next(nextNum);
		
		if(nextNum > largestNum)
		{
			largestNum = nextNum;
		}
	}
	return largestNum;
}

//longestSequence(n) returns the length of the longest
//hailstone sequence from n to 1.

int longestSequence(int n)
{
	int nextNum = n;
	int nextLength;
	int largestLength = 0;
	
	while(nextNum >= 1)
	{
		nextLength = hailstoneLength(nextNum);
		if(nextLength > largestLength)
		{
			largestLength = nextLength;
		}
		
		nextNum--;
	}
	return largestLength;
}

//startingNumber(n) returns the starting number of the longest
//hailstone sequence from n to 1.

int startingNumber(int n)
{
	int k = 0;
	int nextNum = n;
	int nextLength;
	int largestLength = 0;
	
	while(nextNum >= 1)
	{
		nextLength = hailstoneLength(nextNum);
		if(nextLength > largestLength)
		{
			largestLength = nextLength;
			k = nextNum;
		}
		
		nextNum--;
	}
	return k;
	
}

int main(int argc, char** argv)
{
	int initalNum;
	
	printf("What number shall I start with? ");
	scanf("%i", &initalNum);
	
	printf("The hailstone sequence starting at %i is: \n", initalNum);
	printHailstoneSequence(initalNum);
	
	printf("The length of the sequence is %i.\n",
		hailstoneLength(initalNum));
	
	printf("The largest number in the sequence is %i.\n", 
		largestNumber(initalNum));
	
	printf("The longest hailstone sequence starting with a number up to "
		"%i has length %i\n", initalNum, longestSequence(initalNum));
	
	printf("The longest hailstone sequence starting with a number up to "
		"%i begins with %i\n", initalNum, startingNumber(initalNum));
	
	return 0;
}