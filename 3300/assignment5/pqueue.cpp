// CSCI 3300
// Assignment: 05
// Author:     Jack Edwards
// File:       pqueue.cpp
// Tab stops:  4

//This program provides functions for working with
//priority queues.

#include <cstdio>
#include "pqueue.h"

using namespace std;

//PQCell represents a cell in a priority queue

struct PQCell
{
	PQCell* next; //pointer to next cell in the queue
	PQItemType item; //item in the cell
	PQPriorityType priority; //priority of the cell
	
	PQCell(PQCell* nextCell, PQItemType i, PQPriorityType p)
	{
		next = nextCell;
		item = i;
		priority = p;
	}
		   
};

//isEmpty(q) returns true if PriorityQueue q is empty.

bool isEmpty(const PriorityQueue& q)
{
	return q.priorityQ == NULL;
}

//insertCell(item, pri, p) inserts a new item into p with
//item item and priority pri

void insertCell(const PQItemType &item, PQPriorityType pri, PQCell* &p)
{
	if(p == NULL)
	{
		p = new PQCell(NULL, item, pri);
	}
	else if(pri < p->priority)
	{
		p = new PQCell(p, item, pri);
	}
	else
	{
		insertCell(item, pri, p->next);
	}
}

//insert(item, pri, q) inserts an item of priority pri into priority queue q.

void insert(PQItemType item, PQPriorityType pri, PriorityQueue &q)
{
	insertCell(item, pri, q.priorityQ);
}

//remove(item, pri, q) remove the item with the lowest priority in q.
//removes stores the priority of that item into pri and its item into item.

void remove(PQItemType &item, PQPriorityType &pri, PriorityQueue &q)
{
	if(!isEmpty(q))
	{
		pri = q.priorityQ->priority;
		item = q.priorityQ->item;
		PQCell* cellToDelete = q.priorityQ;
		q.priorityQ = q.priorityQ->next;
		delete 	cellToDelete;
	}
}

//printPriorityQueue(q, pi, pp) prints q to the standard output using the
//functions pi and pp.

void printPriorityQueue(const PriorityQueue& q, ItemPrinter pi, PriorityPrinter pp)
{
	if(isEmpty(q))
	{
		printf("The Prority Queue is empty.\n");
	}
	else
	{
		printf("The items in the Priority Queue are as follow:\n\n");
	
		for(PQCell* p = q.priorityQ; p != NULL; p = p->next)
		{
			printf("\tItem: ");
			pi(p->item);
			printf("\n");
			printf("\tPriority: ");
			pp(p->priority);
			printf("\n\n");
		}
	
	}
}	
	

