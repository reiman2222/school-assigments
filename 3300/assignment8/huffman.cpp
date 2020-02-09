// CSCI 3300
// Assignment: 08
// Author:     Jack Edwards
// File:       hufffman.cpp
// Tab stops:  4

//This program encodes a text file using huffman's algorithm.
//This program expects and input file and and output file 
//entered into the command line. The input file must come first.
//Ex: ./huffman inputfile outputfile
//to enaple tracing enter -t immediatly before the input file.


#include <cstdio>
#include <stdlib.h> 
#include "trace.h"
#include "tree.h"
#include "pqueue.h"
#include <string.h>
#include "binary.h"
using namespace std;

const int FREQUENCIE_ARRAY_SIZE = 256;
const int MAX_TREE_DEPTH = 256;
typedef Node* Tree;

//strCopy(s) copies s into a new string in the heap and returns that string.

char* strCopy(char* s)
{
	int length = strlen(s);
	char* result = new char[length + 1];
	int i = 0;
	
	while(s[i] != '\0')
	{
		result[i] = s[i];
		i++;
	}
	
	result[i] = '\0';	
	return result;
}

//initIntArray(array, size, val) initalizes all values in array to val.
//size is the size of the array.

void initIntArray(int* array, int size, int val)
{
	for(int i = 0; i < size; i++)
	{
		array[i] = val;
	}
}

//computeFrequincies(freqArray, inFileName) computes the frequincies of all
//characters in the file called inFileName. The character frequincies are
//stored in freqArray. computeFrequincies returns true if inFileName can be 
//opened. if infileName cannot be opened then computeFrequincies returns 
//false.

bool computeFrequincies(int* freqArray, char* inFileName)
{
	FILE* inFile = fopen(inFileName, "r");
	
	if(inFile == NULL)
	{
		return false;
	}
	
	initIntArray(freqArray, FREQUENCIE_ARRAY_SIZE, 0);
	
	int c = getc(inFile);
	while(c != EOF)
	{
		freqArray[c]++;
		
		c = getc(inFile);
	}
	
	fclose(inFile);
	
	return true;
}

//fillPQ(freqArray, treeQueue) inserts a node in to treeQueue
//for all character that have a frequency in freqArray greater than 0.

void fillPQ(int* freqArray, PriorityQueue& q)
{
	for(int i = 0; i < FREQUENCIE_ARRAY_SIZE; i++)
	{
		if(freqArray[i] > 0)
		{
			Node* newNode = new Node((char)i);
			insert(newNode, freqArray[i], q);
		}
	
	}
}

//buildHuffmanTree(freqArray) builds a huffman tree  in the heap 
//and returns that tree. if there is no tree to build buildHuffmanTree
//returns a NULL pointer. freqArray tells buildHuffmanTree which characters
//need to be in the tree.

Tree buildHuffmanTree(int* freqArray)
{
	PriorityQueue treeQueue;
	fillPQ(freqArray, treeQueue);
	
	int pri1;
	int pri2;
	Node* node1 = NULL;
	Node* node2;

	while(!isEmpty(treeQueue))
	{
		remove(node1, pri1, treeQueue);
		if(isEmpty(treeQueue))
		{	
			return node1;
		}
		
		remove(node2, pri2, treeQueue);
		
		Node* t = new Node(node1,node2);
		
		insert(t, pri1 + pri2, treeQueue);
	}
	
	return node1;
}

//buildCodes(t, codeArray, pref) builds the huffman code for each of the
//characters in t. codeArray is the array to store the codes in. 
//pref is the prefix of the code.

void buildCodes(Tree t, char** codeArray, char* pref)
{
	if(t->kind == leaf)
	{
		codeArray[(int)t->ch] = strCopy(pref);
	}
	else
	{
		char leftPath[MAX_TREE_DEPTH];
		char rightPath[MAX_TREE_DEPTH];
		
		strcpy(leftPath, pref);
		strcat(leftPath, "0");
		
		strcpy(rightPath, pref);
		strcat(rightPath, "1");
		
		buildCodes(t->left, codeArray, leftPath);
		buildCodes(t->right, codeArray, rightPath);
		
	}
}

//buildCodeArray(t) builds codes for all characters in huffman tree t.
//If t has hight 1 then the code for its character will be 1. Otherwise 
//the standard convention for huffman codes is used. buildCodeArray returns a
//pointer to the code array.
//
//Tree: (a,(b,c)) yeilds these codes
//			a - 0
//			b - 10
//			c - 11

char** buildCodeArray(Tree t)
{
	char** codeArray = new char*[FREQUENCIE_ARRAY_SIZE];
	char prefix[MAX_TREE_DEPTH];
	prefix[0] = '\0';
	
	for(int i = 0; i < FREQUENCIE_ARRAY_SIZE; i++)
	{
		codeArray[i] = strCopy(prefix);
	}
	
	if(t->kind == leaf)
	{
		char* code = new char[MAX_TREE_DEPTH];
		code[0] = '1';
		code[1] = '\0';
		codeArray[(int)t->ch] = code;
	}
	else
	{
		buildCodes(t, codeArray, prefix);
	}
	
	return codeArray;
	
}

//writeTree(f, t) writes a binary huffman tree to f. t is the tree to write.

void writeTree(BFILE* f, Tree t)
{
	if(t->kind == leaf)
	{
		writeBit(f, 1);
		writeByte(f, (int)t->ch);
	}
	else
	{
		writeBit(f, 0);
		writeTree(f, t->left);
		writeTree(f, t->right);
	}
}

//writeEncodedChar(codeArray, charToEncode, outputFile) writes charToEncode
//into outputFile using the codes in codeArray.

void writeEncodedChar(char** codeArray, char charToEncode, BFILE* outputFile)
{
	char* code = codeArray[(int)charToEncode];
	for(int i = 0; code[i] != '\0'; i++)
	{
		if(code[i] == '1')
		{
			writeBit(outputFile, 1);
		}
		else
		{
			writeBit(outputFile, 0);
		}
	}
}

//writeEncodedFile(codeArray, outputFile, inputFile) uses the codes in codeArray
//to encode inputFile. The encoded text is stored in outputFile.

void writeEncodedFile(char** codeArray, BFILE* outputFile, const char* inputFile)
{
	FILE* inFile = fopen(inputFile, "r");
	
	if(inFile == NULL)
	{
		printf("ERROR: the file \"%s\" could not be read\n", inputFile);
		exit(0);
	}
	
	int c = getc(inFile);
	
	while(c != EOF)
	{
		writeEncodedChar(codeArray, c, outputFile);
		
		c = getc(inFile);
	}
	
	fclose(inFile);
}

int main(int argc, char** argv)
{
	enableTracing(argc, argv);
	
	int* frequencies = new int[FREQUENCIE_ARRAY_SIZE];
	Tree huffmanTree;
	
	if(!computeFrequincies(frequencies, argv[argc - 2]))
	{
		printf("ERROR: the file \"%s\" could not be read\n", argv[argc - 2]);
		exit(0);
	}
	
	if(tracelevel == 1)
	{
		printf("The character frequencies are:\n\n");
		showFreqArray(frequencies, FREQUENCIE_ARRAY_SIZE);
		printf("\n");
	}
	
	huffmanTree = buildHuffmanTree(frequencies);
	
	if(tracelevel == 1)
	{
		printf("The Huffman tree is as follows: ");
		printTree(huffmanTree);
		printf("\n\n");
	}
	
	char** codes = buildCodeArray(huffmanTree);
	
	if(tracelevel == 1)
	{
		printf("A Huffman code is as follows.\n\n");
		printCodeArray(codes, FREQUENCIE_ARRAY_SIZE);
	}
		
	BFILE* outFile = openBinaryFileWrite(argv[argc - 1]);
	
	if(outFile == NULL)
	{
		printf("ERROR: the file \"%s\" could not be opened\n", argv[argc - 1]);
		exit(0);
	}
	
	writeTree(outFile, huffmanTree);
	writeEncodedFile(codes, outFile, argv[argc - 2]);
	closeBinaryFileWrite(outFile);

 	return 0;
}
