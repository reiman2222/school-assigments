// CSCI 3300
// Assignment: 04
// Author:     Jack Edwards
// File:       mst.cpp
// Tab stops:  4

//This program takes a graph from the standard input and 
//outputs the minimal spanning tree of that graph to the standard output. 

#include <cstdio>
#include <cstdlib>
#include "equiv.h"

using namespace std;

typedef int (*QSORT_COMPARE_TYPE)(const void*, const void*);

const int MAX_EDGES = 100;

//An edge represents a connection between two verticies in a graph.

struct Edge 
{
	int v1; //first vertex
	int v2; // second verted
	int weight; //weight of the edge
	
	Edge()
	{
		v1 = 0;
		v2 = 0;
		weight = 0;
	}
};
	
//A graph is composed of vertices connected by edges.

struct Graph
{
	int numVertices; //number of vertices in the graph
	Edge edges[MAX_EDGES]; //array of edges connecting the vertices in the graph
	int numEdges; //number of edges currently in the graph
	
	Graph(int nv)
	{
		numVertices = nv;
		numEdges = 0;
	}
};


//insertEdge(u, v, w, g) adds an edge of weight w, 
//between vertices u and v to the graph g.
//
//If there is not enough room to add the edge then
//insertEdge does nothing.

void insertEdge(int u, int v, int w, Graph &g)
{
	if(g.numEdges < (MAX_EDGES)) 
	{
		Edge x;
		g.edges[g.numEdges].v1 = u;
		g.edges[g.numEdges].v2 = v;
		g.edges[g.numEdges].weight = w;
		g.numEdges++;
	}
	else
	{
		printf("not enough room\n");
	}
}

//readAGraph() reads a graph from the standard input and returns that graph.
//First readAGraph takes the number of verticies, then readAGraph
//takes a vertex, a vertex and a weight until a 0 is entered for the first
//vertex.

Graph readAGraph()
{
	int numVertices;
	int vertex1;
	int vertex2;
	int weight;

	scanf("%i", &numVertices);
	Graph x(numVertices);
	
	for(int i = 0; i < MAX_EDGES; i++)
	{
		scanf("%i", &vertex1);
		
		if(vertex1 == 0)
		{
			break;
		}
		
		scanf("%i", &vertex2);
		scanf("%i", &weight);
		
		insertEdge(vertex1, vertex2, weight, x);
		
	}
	
	return x;
}

//writeGraph(g) prints graph g to the standard output.

void writeGraph(Graph &g)
{
	printf("There are %i vertices and %i edges\n\n",
		   g.numVertices, g.numEdges);
	printf("\tvertices\tweight\n");
	
	for(int i = 0; i < g.numEdges; i++)
	{
		printf("\t%i  %i\t\t%i\n", 
			   g.edges[i].v1, g.edges[i].v2, g.edges[i].weight);
	}
}

//compareEdges(A, B) decides if A should come before B when being sorted 
//with qsort.

int compareEdges(const Edge* A, const Edge* B)
{
	return A->weight - B->weight;
}

//sortEdge(g) sorts and array of edges from smallest to largest in graph g.

void sortEdge(Graph &g)
{
	qsort((void*)g.edges, g.numEdges, sizeof(Edge), (QSORT_COMPARE_TYPE)compareEdges);
}

//minimalSpanningTree(g) returns the graph that
//is the minimal spanning tree of g.

Graph minimalSpanningTree(Graph g)
{
	int vertex1;
	int vertex2;
	
	Graph K(g.numVertices); //this graph holds the minimal spanning tree
	sortEdge(g);
	ER connections = newER(g.numVertices);
	
	for(int i = 0; i < g.numEdges; i++)
	{
		vertex1 = g.edges[i].v1;
		vertex2 = g.edges[i].v2;
		
		//if vertex1 and vertex2 are not already connected then add 
		//the edge to graph K.
		
		if(!together(connections, vertex1, vertex2))
		{
			combine(connections, vertex1, vertex2);
			insertEdge(vertex1, vertex2, g.edges[i].weight, K);
		}
	}
	
	destroyER(connections);
	return K;
}

//totalWeight(g) returns the total weight of all the edges in graph g.

int totalWeight(Graph g)
{
	int sum = 0;
	for(int i = 0; i < g.numEdges; i++)
	{
		sum += g.edges[i].weight;
	}
	return sum;
}

int main(int argc, char** argv)
{
	printf("Input graph:\n\n");
	Graph inputGraph = readAGraph();
	
	writeGraph(inputGraph);
	
	Graph minSpanningTree = minimalSpanningTree(inputGraph);
	
	printf("\nMinimal spanning tree:\n\n");
	writeGraph(minSpanningTree);
	
	printf("\nThe total weight of the spanning tree is %i.\n",
		   totalWeight(minSpanningTree));

	return 0;
}
