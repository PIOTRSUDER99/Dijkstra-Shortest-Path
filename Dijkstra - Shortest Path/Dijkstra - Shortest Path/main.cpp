#include <iostream>
#include "Disjoint_Sets.h"
#include "Graph.h"

using namespace std;

int main()
{
   //Example of running the algorithm on a particular graph

	Graph* G1 = new Graph;
	G1->insertEdge(0, 1, 2);
	G1->insertEdge(0, 2, 1);
	G1->insertEdge(0, 4, 5);
	G1->insertEdge(1, 2, 1);
	G1->insertEdge(1, 3, 4);
	G1->insertEdge(2, 3, 3);
	G1->insertEdge(2, 4, 2);

	Graph G2 = G1->generateMST();

	G2.printGraph();
	
	Graph *G3 = new Graph;
	G3->insertEdge(0, 1, 1);
	G3->insertEdge(0, 3, 3);
	G3->insertEdge(0, 5, 2);
	G3->insertEdge(1, 3, 1);
	G3->insertEdge(1, 2, 2);
	G3->insertEdge(1, 4, 7);
	G3->insertEdge(2, 3, 6);
	G3->insertEdge(2, 4, 10);
	G3->insertEdge(3, 5, 4);
	G3->insertEdge(3, 6, 4);
	G3->insertEdge(5, 6, 10);

	cout << endl;
	cout << "Dijkstra" << endl;
	cout << endl;
	
	cout << "Vertices, their distances and previous vertices on path from vertex 0:" << endl;
	G3->printDijkstra(0);


	int noth;
	cin >> noth;
	return 0;
}