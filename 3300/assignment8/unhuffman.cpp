// CSCI 3300
// Assignment: 08
// Author:     Jack Edwards
// File:       unhuffman.cpp
// Tab stops:  4

//This program decodes a file encoded with huffman's algorithm.
//This program expects and input file and and output file 
//entered into the command line. The input file must come first.
//Ex: ./unhuffman inputfile outputfile
//to enaple tracing enter -t immediatly before the input file.

#include <cstdio>
#include <stdlib.h> 
#include "trace.h"
#include "binary.h"
#include "tree.h"
using namespace std;

typedef Node* Tree;

//readTree(f) reads a hufman tree from f.

Tree readTree(BFILE* f)
{
	int b = readBit(f);
	if(b == 1)
	{
		int ch = readByte(f);
		return new Node((char)ch);
	}
	else
	{
		Tree A = readTree(f);
		Tree B = readTree(f);
		return new Node(A, B);
	}
}

//decodeChar(t, encodedFile) reads encodedFile until a complete a code for
//a character is found. decodeChar then returns that character.

int decodeChar(Tree t, BFILE* encodedFile)
{
	if(t->kind == leaf)
	{
		return t->ch;
	}
	else
	{
		int b = readBit(encodedFile);
		
		if(b == 0)
		{
			return decodeChar(t->left, encodedFile);
		}
		else if(b == 1)
		{
			return decodeChar(t->right, encodedFile);
		}
		else
		{
			return EOF;
		}
		
	}
	
	
}

//decodeTreeOfHeight1(t, encodedFile, decodedFile) decodes encodedFile using huffmans
//algoritm writing the decoded version to outFile.
//Requires: tree t must have height 1.

void decodeTreeOfHeight1(Tree t, BFILE* encodedFile, FILE* decodedFile)
{
	int nextBit = readBit(encodedFile);
	
	while(nextBit != EOF)
	{
		putc(t->ch, decodedFile);
		
		nextBit = readBit(encodedFile);
	}
}

//decodeFile(t, encodedFile, outFile) writes a decoded version of 
//encodedFile to a file named outFile. decodeFile uses huffman tree 
//t to decode encodedFile. 

void decodeFile(Tree t, BFILE* encodedFile, const char* outFile)
{
	FILE* decodedFile = fopen(outFile, "w");
	
	if(decodedFile == NULL)
	{
		printf("ERROR: the file \"%s\" could not be read\n", outFile);
		exit(0);
	}
	
	if(t->kind == leaf)
	{
		decodeTreeOfHeight1(t, encodedFile, decodedFile);
	}
	else
	{
		int ch = decodeChar(t, encodedFile);
	
		while(ch != EOF)
		{
			putc((char)ch, decodedFile);

			ch = decodeChar(t, encodedFile);
		}
	}
	fclose(decodedFile);
}

int main(int argc, char** argv)
{
	enableTracing(argc, argv);
	
	BFILE* encodedFile = openBinaryFileRead(argv[argc - 2]);
	
	if(encodedFile == NULL)
	{
		printf("ERROR: the file \"%s\" could not be opened\n", argv[argc - 2]);
		exit(0);
	}

	Tree huffmanTree = readTree(encodedFile);

	if(tracelevel == 1)
	{
		printf("Decoding from file %s with Tree: ", argv[argc - 2]);
		printTree(huffmanTree);
		printf("\n");
	}
	
	decodeFile(huffmanTree, encodedFile, argv[argc - 1]);

	closeBinaryFileRead(encodedFile);
	
	return 0;
}
