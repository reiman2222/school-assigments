// CSCI 3300
// Assignment: Assignment 08
// Author:     Jack Edwards
// File:       trace.cpp
// Tab stops:  4

#ifndef TREE_H
#define TREE_H

enum NodeKind {leaf, nonleaf};

//A Node represents a node in a tree

struct Node
{
	NodeKind kind; //type of node
	char ch; //character stored in node
	Node* left; //left subtree
	Node*  right; //right subtree

    Node(char c)
    {
    	kind = leaf;
    	ch   = c;
    }

    Node(Node* L, Node *R)
    {
    	kind  = nonleaf;
    	left  = L;
    	right = R;
	}      
};

#endif
