// CSCI 3300
// Assignment: 2
// Author:     Jack Edwards
// File:       hailstone.cpp
// Tab stops:  4

//This program asks the user to enter a number then prints the hailstone
//sequence of that number, the length of said hailstone sequence,
//the largest number in said hailstone sequence and the starting number
//and lenght of the longest hailstone sequence from that number to 1.

#include <cstdio>
#include <algorithm>

using namespace std;

//next(n) calculates the next number in the hailstone sequence after n 
//for any integer greater than 1.
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
	
	if(n == 1)
	{
		printf("%i\n", n);
		return;
	}
	else
	{	
		printf("%i ", n);
		return printHailstoneSequence(next(n));
	}
	
}

//hailstoneLength(n, L) returns the length of the hailstone sequence 
//starting at n.
//Ex: hailstoneLength(7) = 17

int hailstoneLength(int n)
{
	if(n == 1)
	{
		return 1;
	}
	else
	{
		return  1 + hailstoneLength(next(n));
	}
}

//largestNumber(n) returns the latgest number in the 
//hailstone sequence starting at n.

int largestNumber(int n)
{
	
	if(n == 1)
	{
		return n;
	}
	else
	{
		int nextNum = next(n);
		return max(max(n, nextNum), largestNumber(nextNum));
	}
}

//longestSequence(n) returns the length of the longest
//hailstone sequence from n to 1.

int longestSequence(int n)
{
	if(n == 1)
	{
		return n;
	}
	else
	{
		return max(max(hailstoneLength(n), hailstoneLength(n - 1)), longestSequence(n-1));
	}
}

//startingNumber(n, longest) returns the starting number of the longest
//hailstone sequence from n to 1
//Rerquires: longest = n
//Ex: startingNumber(8, 8) = 7

int startingNumber(int n, int longest) 
{
	if(n == 1)
	{
		return longest;
	}
	else
	{
		if(hailstoneLength(longest) > hailstoneLength(n - 1))
		{
			longest = longest;
		}
		else
		{
			longest = n - 1;
		}
		return startingNumber(n - 1, longest);
	}
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
		"%i begins with %i\n", initalNum, startingNumber(initalNum, initalNum));
	
	return 0;
}