#include "DisjointSets.h"

DisjointSets::DisjointSets(int nrOfSets)
    : parent(nrOfSets), rank(nrOfSets), numSets(nrOfSets), currentNumSets(nrOfSets)
{
    for (int i = 0; i < nrOfSets; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

DisjointSets::DisjointSets(const DisjointSets& other)
    : parent(other.parent), rank(other.rank), numSets(other.numSets), currentNumSets(other.currentNumSets){}

DisjointSets& DisjointSets::operator=(const DisjointSets& other)
{
    if (this == &other) {
        return *this;
    }

    parent = other.parent;
    rank = other.rank;
    numSets = other.numSets;
    currentNumSets = other.currentNumSets;

    return *this;
}

int DisjointSets::findSet(int element)
{
    if (element == parent[element])
        return element;
    return parent[element] = findSet(parent[element]);
}

void DisjointSets::unionSets(int set1, int set2)
{
    int root1 = findSet(set1);
    int root2 = findSet(set2);
    if (root1 == root2) {
        return;
    }
    // Union by rank: attach the smaller set to the root of the larger set.
    if (rank[root1] > rank[root2]) {
        parent[root2] = root1;
    }
    else if (rank[root1] < rank[root2]) {
        parent[root1] = root2;
    }
    else {
        parent[root2] = root1;
        rank[root1]++;
    }
    numSets--;
    currentNumSets--;
}

int DisjointSets::getNrOfSets() const
{
    return numSets;
}

int DisjointSets::getcurrentNrOfDisjointSets() const
{
    return currentNumSets;
}
