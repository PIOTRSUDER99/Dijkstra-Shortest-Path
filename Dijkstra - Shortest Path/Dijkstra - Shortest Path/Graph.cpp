#include "Graph.h"
#include "Disjoint_Sets.h"

void Graph::MergeSort(vector<Edge*> *Array)
{
	MergeSortRecursive(Array, 0, Array->size() - 1);
}

void Graph::MergeSortRecursive(vector<Edge*> *Array, int beginIndex, int endIndex)
{
	if (beginIndex < endIndex)
	{
		int middleIndex = (beginIndex + endIndex) / 2;
		MergeSortRecursive(Array, beginIndex, middleIndex);
		MergeSortRecursive(Array, middleIndex + 1, endIndex);
		Merge(Array, beginIndex, middleIndex, middleIndex + 1, endIndex);
	}
}

void Graph::Merge(vector<Edge*> *Array, int beginIndex1, int endIndex1, int beginIndex2, int endIndex2)
{
	vector<Edge*> OutsideArray;
	unsigned int i = beginIndex1;
	unsigned int j = beginIndex2;

	while (i <= endIndex1 && j <= endIndex2)
	{
		if (Array->at(i)->weight <= Array->at(j)->weight)
		{
			OutsideArray.push_back(Array->at(i));
			i++;
		}
		else
		{
			OutsideArray.push_back(Array->at(j));
			j++;
		}
	}
	while (i <= endIndex1)
	{
		OutsideArray.push_back(Array->at(i));
		i++;
	}

	while (j <= endIndex2)
	{
		OutsideArray.push_back(Array->at(j));
		j++;
	}

	//copy the entries back to Array
	for (unsigned int k = 0; k < OutsideArray.size(); k++)
	{
		Array->at(beginIndex1 + k) = OutsideArray.at(k);
	}
}

/* Postconditions: Inserts a bi-directional between node1 and node2 with the given weight
*/
void Graph::insertEdge(int node1, int node2, int weight) {

	while (AdjacencyMatrix.size() <= node1 || AdjacencyMatrix.size() <= node2)
	{
		vector<Edge*> newRow;
		for (unsigned int i = 0; i < AdjacencyMatrix.size(); i++)
		{
			newRow.push_back(nullptr);
		}
		AdjacencyMatrix.push_back(newRow);
		for (unsigned int i = 0; i < AdjacencyMatrix.size(); i++)
		{
			AdjacencyMatrix.at(i).push_back(nullptr);
		}
	}

	Edge* newEdge1 = new Edge;
	newEdge1->from = node1;
	newEdge1->to = node2;
	newEdge1->weight = weight;
	newEdge1->visited = false;

	Edge* newEdge2 = new Edge;
	newEdge2->from = node2;
	newEdge2->to = node1;
	newEdge2->weight = weight;
	newEdge2->visited = false;

	AdjacencyMatrix.at(node1).at(node2) = newEdge1;
	AdjacencyMatrix.at(node2).at(node1) = newEdge2;	
}

/* Preconditions: From and to are of vertices of the graph
   Postconditions: Returns true if there is an edge between from and to and false otherwise
*/
bool Graph::isEdge(int from, int to) 
{
	if (AdjacencyMatrix.at(from).at(to) != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* Preconditions: From and to are vertices of the graph between which there is an edge
   Postconditions: Returns the weight of the edge between from and to
*/
int Graph::getWeight(int from, int to) {
	if (AdjacencyMatrix.at(from).at(to) != nullptr)
	{
		return AdjacencyMatrix.at(from).at(to)->weight;
	}
	else
	{
		return -1;
	}
}

/* Preconditions: The graph is connected
   Postconditions: Returns a new graph object containing only the edges representing
   the minimum spanning tree of the graph
*/
Graph Graph::generateMST() {
	//create array of edges
	vector<Edge*> EdgeArray;
	//adding all the entries from on and below the principal diagonal
	for (unsigned int i = 0; i < AdjacencyMatrix.size(); i++)
	{
		for (unsigned int j = 0; j <= i; j++)
		{
			//if (AdjacencyMatrix.at(i).at(j))
			if (isEdge(i, j))
			{
				EdgeArray.push_back(AdjacencyMatrix.at(i).at(j));
			}
		}
	}

	//sort EdgeArray according to weights using MergeSort
	MergeSort(&EdgeArray);

	vector<Edge*> SelectedEdges;
	
	//create disjoint sets holding all vertices
	Disjoint_Sets disjoint_Sets(AdjacencyMatrix.size());

	int fromSet = -1;
	int toSet = -1;

	for (unsigned int i = 0; i < EdgeArray.size(); i++)
	{
		fromSet = disjoint_Sets.find(EdgeArray.at(i)->from);
		toSet = disjoint_Sets.find(EdgeArray.at(i)->to);

		if (fromSet != toSet)
		{
			SelectedEdges.push_back(EdgeArray.at(i));
			disjoint_Sets.union_set(fromSet, toSet);
		}
	}

	//create new graph
	Graph* newGraph = new Graph;
	for (unsigned int i = 0; i < SelectedEdges.size(); i++)
	{
		newGraph->insertEdge(SelectedEdges.at(i)->from, SelectedEdges.at(i)->to, SelectedEdges.at(i)->weight);
		newGraph->insertEdge(SelectedEdges.at(i)->to, SelectedEdges.at(i)->from, SelectedEdges.at(i)->weight);
	}

	return *newGraph;
}

/* Preconditions: The graph is connected
   Postconditions: Runs Dijkstra's Algorithm from source, printing to cout a line for
   each vertex (except the source). Each line should contain the vertex number, the shortest
   distance to that vertex, and the previous vertex on the shortest path to that vertex.
   Each value on the line should be separated by a single space. The vertices should be printed
   in order from lowest numbered vertex to highest numbered vertex.
*/
void Graph::printDijkstra(int source) {
	vector<Vertex*> VertexArray;
	for (int i = 0; i < AdjacencyMatrix.size(); i++)
	{
		Vertex *v = new Vertex;
		//v->index = i;
		v->previous = -1;
		if (i == source)
		{
			v->distance = 0;
			v->finalized = true;
		}
		else
		{
			v->distance = std::numeric_limits<int>::max(); //infinity
			//v->distance = 1000000; //infinity
			v->finalized = false;
		}
		VertexArray.push_back(v);
	}

	int lastFinalized = source;
	int newDistance;
	int numFinalized = 1;
	while (numFinalized < VertexArray.size())
	{
		for (int j = 0; j < AdjacencyMatrix.size(); j++)
		{
			if (isEdge(lastFinalized, j)) 
			{
				if (VertexArray.at(j)->finalized == false)
				{
					//Vertex *v = VertexArray.at(j);
					newDistance = VertexArray.at(lastFinalized)->distance + getWeight(lastFinalized, j);
					if (newDistance < VertexArray.at(j)->distance)
					{
						VertexArray.at(j)->distance = newDistance;
						VertexArray.at(j)->previous = lastFinalized;
					}
				}
			}
		}

		int minUpdatedDistance = std::numeric_limits<int>::max(); //infinity

		for (int j = 0; j < VertexArray.size(); j++)
		{
			if (VertexArray.at(j)->finalized == false)
			{
				if (VertexArray.at(j)->distance < minUpdatedDistance)
				{
					lastFinalized = j;
					minUpdatedDistance = VertexArray.at(j)->distance;
				}
			}
		}
		VertexArray.at(lastFinalized)->finalized = true;
		numFinalized++;
	}

	
	//print out contents of VertexArray
	for (int i = 0; i < VertexArray.size(); i++)
	{
		if (i != source)
		{
			cout << "Vertex: "<< i << ", Distance: " << VertexArray.at(i)->distance << ", Previous Vertex: " << VertexArray.at(i)->previous << endl;
		}
	}
}

/* Optional Function: You may use this function for debugging purposes if you wish
   Preconditions: None
   Postconditions: Prints the graph in any format you wish
*/
void Graph::printGraph() {
	for (unsigned int i = 0; i < AdjacencyMatrix.size(); i++)
	{
		for (unsigned int j = 0; j < AdjacencyMatrix.at(i).size(); j++)
		{
			if (AdjacencyMatrix.at(i).at(j) != nullptr)
			{
				cout << "Vertex " << i << "[" << AdjacencyMatrix.at(i).at(j)->to << ", weight: " << AdjacencyMatrix.at(i).at(j)->weight << "]" << endl;
			}
		}
	}
}