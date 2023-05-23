#ifndef DISJOINT_SETS_H
#define DISJOINT_SETS_H
#include <vector>

class DisjointSets
{
private:
	/*
	* members for you to decide
	*/
	std::vector<int> parent; // keeps track of the parent of each element
	std::vector<int> rank;   // keeps track of the rank of each set
	int numSets;             // the total number of sets
	int currentNumSets;      // the current number of disjoint sets
public:
	DisjointSets(int nrOfSets);
	DisjointSets(const DisjointSets& other);
	DisjointSets& operator=(const DisjointSets& other);

	int findSet(int set);
	void unionSets(int setOne, int setTwo);
	int getNrOfSets() const;
	int getcurrentNrOfDisjointSets() const;
};

#endif
