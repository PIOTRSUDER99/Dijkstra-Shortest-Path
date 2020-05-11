#ifndef Graph_h
#define Graph_h

#include <vector>
#include <list>
#include <iostream>
#include <limits>

using namespace std;

struct Edge
{
	int from;
	int to;
	int weight;
	bool visited;
};

struct Vertex
{
	//int index;
	int previous;
	int distance;
	bool finalized;
};

class Graph
{
public:
	vector<vector<Edge*>> AdjacencyMatrix;

	void insertEdge(int node1, int node2, int weight);  //inserts new edge in graph
	bool isEdge(int from, int to);  //returns true if there is an edge between the vertices from and to
	int getWeight(int from, int to);  //returns the weight of the edge between the vertices from and to
	Graph generateMST();
	void printDijkstra(int source);
	void printGraph(); //prints graph in a format sorted by ascending vertex and edge list

private:
	void MergeSort(vector<Edge*> *Array);
	void MergeSortRecursive(vector<Edge*> *Array, int beginIndex, int endIndex);
	void Merge(vector<Edge*> *Array, int beginIndex1, int endIndex1, int beginIndex2, int endIndex2);
};

#endif /* Graph_h */

