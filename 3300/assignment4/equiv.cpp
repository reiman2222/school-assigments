// CSCI 3300
// Assignment: 03
// Author:     Jack Edwards
// File:       equiv.cpp
// Tab stops:  4

//This program provides functions for creating and working with equivalence relations.

#include "equiv.h"
#include <cstdio>

using namespace std;

//newER(n) returns a new equivalence relation of length n starting at 1.
//The equivalence relation is initalized so that each value is its own boss.

ER newER(int n)
{
	int length = n + 1;
	ER A = new equivRelation[length];
	
	for(int i = 1; i < length; i++)
	{
		A[i].boss = i;
		A[i].numConstituents = 1;
	}
	
	return A;
}

//leader(R, x) returns the number that is the leader of x in R.

int leader(ER R, int x)
{
	if(R[x].boss == x)
	{
		return x;
	}
	else
	{
		return R[x].boss = leader(R, R[x].boss);
		//return leader(R, R[x].boss);
	}
}

//together(R, x, y) returns true if x and y are in the same equivalence class.
//Ex: 	given a relation R = {1,2,4} {5,3} {6} 
//		together(R, 4, 2) = true
//		together(R, 1, 5) = false

bool together(ER R, int x, int y)
{
	return leader(R, x) == leader(R, y);
}

//combine(R, x, y) combines the equivalence class of x and
//the equivalence class of y.
//Ex: 	given a relation R = {1,2,4} {5,3} {6} 
//		combine(R, 5, 3) = {1,2,4} {5,3,6}

void combine(ER R, int x, int y)
{
	if(!together(R, x, y))
	{
		int leaderX = leader(R, x);
		int leaderY = leader(R, y);
		
		//makes the leader with the fewest constituents the leader of
		//the combined equivalence class
		
		if(R[leaderX].numConstituents < R[leaderY].numConstituents)
		{
			R[leaderX].boss = leaderY;
			R[leaderY].numConstituents += R[leaderX].numConstituents;
			R[leaderX].numConstituents = 0;
		}
		else
		{
			R[leaderY].boss = leaderX;
			R[leaderX].numConstituents += R[leaderY].numConstituents;
			R[leaderY].numConstituents = 0;
		}
	}
}

//destroyER(R) deallocates R.

void destroyER(ER R)
{
	delete [] R;
}

//showER(R, n) prints R of length n to the standard output 

void showER(ER R, int n)
{	
	printf("k\tboss of k\n");
	
	for(int i = 1; i <= n; i++)
	{
		printf("%i\t%i\n", i, R[i].boss);
	}
}
