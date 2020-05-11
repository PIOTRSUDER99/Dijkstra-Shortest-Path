#include "Disjoint_Sets.h"

/* Preconditions: size is the number of sets to initialize for the class instance
   Postconditions: creates a new disjoint sets object that can handle size elements
   (with indicies 0 - size-1)
*/
Disjoint_Sets::Disjoint_Sets(int size) {

	for (int i = 0; i < size; i++)
	{
		VertexArray.push_back(-1);
	}
}

/* Preconditions: x and y are integer values between [0, size-1]
   Postconditions: attaches the root of one tree to the root of the other tree
*/
void Disjoint_Sets::union_set(int x, int y) {
	int root1 = find(x);
	int root2 = find(y);
	VertexArray.at(root1) = root2;
}

/* Preconditions: x is an integer values between [0, size-1]
   Postconditions: returns the root of the tree to which x belongs
*/
int Disjoint_Sets::find(int x) {
	if (VertexArray.at(x) == -1)
	{
		return x;
	}
	else
	{
		return find(VertexArray.at(x));
	}
}