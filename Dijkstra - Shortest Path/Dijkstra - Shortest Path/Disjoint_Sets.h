#ifndef Disjoint_Sets_h
#define Disjoint_Sets_h

#include <vector>
#include <iostream>

using namespace std;

class Disjoint_Sets
{
public:
	Disjoint_Sets(int size);
	~Disjoint_Sets() = default;

	void union_set(int x, int y);
	int find(int x);

private:
	vector<int> VertexArray;

};

#endif /* Disjoint_Sets_h */
