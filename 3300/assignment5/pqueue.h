// CSCI 3300
// Assignment: 05
// Author:     Jack Edwards
// File:       pqueue.h
// Tab stops:  4

#ifndef PQUEUE_H
#define PQUEUE_H

typedef const char* PQItemType;
typedef double PQPriorityType;
typedef void (ItemPrinter)(PQItemType);
typedef void (PriorityPrinter)(PQPriorityType);

struct PQCell;

//PriorityQueue represents a queue where each item in the queue contains
//a priority and an item.

struct PriorityQueue
{
	PQCell* priorityQ; //pointer to the first cell in the priority queue
	
	PriorityQueue()
	{
		priorityQ = NULL;
	}
};

bool isEmpty(const PriorityQueue &q);
void insert(PQItemType item, PQPriorityType pri, PriorityQueue &q);
void remove(PQItemType &item, PQPriorityType &pri, PriorityQueue &q);
void printPriorityQueue(const PriorityQueue &q, ItemPrinter pi, PriorityPrinter pp);

#endif
