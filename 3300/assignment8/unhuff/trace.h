// CSCI 3300
// Assignment: 08
// Author:     Jack Edwards
// File:       trace.h
// Tab stops:  4

#ifndef EVENT_H
#define EVENT_H

struct Node;

void enableTracing(int numArgs, char** args);
void displayChar(char c);
void showFreqArray(int* freqArray, int size);
void printTree(Node* t);
void printCodeArray(char** codeArray, int size);

extern int tracelevel;
#endif