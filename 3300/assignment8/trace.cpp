// CSCI 3300
// Assignment: Assignment 08
// Author:     Jack Edwards
// File:       trace.cpp
// Tab stops:  4

//This program provides functions for tracing

#include <cstdio>
#include "trace.h"
#include <string.h>
#include <cctype>
#include "tree.h"
using namespace std;

int tracelevel = 0;

//contains(A, size, key) returns true if key is found in array A.
//size is the size of array A

bool contains(char** A, const int size, const char* key)
{
	bool found = false;
	int i = 0;
	while(!found && i < size)
	{
		if(strcmp(A[i], key) == 0)
		{
			found = true;
		}
		i++;
	}
	
	return found;
}

//enableTracing(numArgs, args) enables tracing if the command -t is entered
//anywhere in the command line.

void enableTracing(int numArgs, char** args)
{
	const char* trace = "-t";
	
	if(contains(args, numArgs, trace))
	{
		tracelevel = 1;
	}
}

//displayChar(c) prints a char to the standard output. If the character is not
//printable displayChar prints the characters code or another appropriate 
//representation.

void displayChar(char c)
{
	if(c == ' ')
	{
		printf("space");
	}
	else if(c == '\n')
	{
		printf("\\n");
	}
	else if(c == '\t')
	{
		printf("\\t");
	}
	else if(isprint((int)c))
	{
		printf("%c", c);
	}
	else
	{
		printf("\\%i", (int)c);
	}
}

//showFreqArray(freqArray, size) prints freqArray to the standard output.
//size is the size of freqArray. showFreqArray only prints items that have a 
//frequency greater than 0.

void showFreqArray(int* freqArray, int size)
{
	for(int i = 0; i < size; i++)
	{
		if(freqArray[i] > 0)
		{
			displayChar((char)i);
			printf("\t%i\n", freqArray[i]);
		}
	}
}

//printTree(t) prints a huffman tree to the standard output.

void printTree(Node* t)
{
	if(t != NULL)
	{
		
		if(t->kind == leaf)
		{
			displayChar(t->ch);
		}
		else
		{
			printf("(");
			printTree(t->left);
			printf(",");
			printTree(t->right);
			printf(")");
		}
	}
}

//printCodeArray(codeArray, size) prints the code array to the standard
//output. size is the size of the code array

void printCodeArray(char** codeArray, int size)
{
	for(int i = 0; i < size; i++)
	{
		if(strcmp(codeArray[i], "\0") != 0)
		{
			displayChar((char)i);
			printf("\t%s\n", codeArray[i]);
		}
	}
}
