// CSCI 3300
// Assignment: 03
// Author:     Jack Edwards
// File:       equiv.h
// Tab stops:  4

// These #ifndef and #define lines make it so that, if this file is
// read more than once by the compiler, its body is skipped on all
// but the first time it is read.

#ifndef EQUIV_H
#define EQUIV_H

// An equivalence relation is an array of structures.  So ER abbreviates equivRelation*.  
struct equivRelation
{
	int boss;
	int numConstituents;
	
	equivRelation()
	{
		boss = 0;
		numConstituents = 0;
	}
};

typedef equivRelation* ER;

ER   newER    (int n);
void destroyER(ER e);
bool together (ER e, int x, int y);
void combine  (ER e, int x, int y);

// The following is advertised here solely for debugging.  These must
// only be used for debugging.

void showER(ER e, int n);
int  leader(ER e, int x);

#endif