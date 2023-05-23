#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <string>
#include <vector>
#include <tuple> 
#include <climits>
#include <unordered_map>
#include <queue>
#include <set>
#include <algorithm>

const int INFINITY_COST = INT_MAX;

template <typename T>
class Graph
{
public:
	enum class GRAPH_TYPE { DIRECTED, UNDIRECTED };
private:
	std::unordered_map<T, int> nodeIndices;
	std::map<T, std::vector<std::pair<T, int>>> adjList;
	GRAPH_TYPE graphType;
	int findIndex(const T& node) const;
	const T& GetNode(int index) const;
public:
	Graph(Graph::GRAPH_TYPE graphType, std::vector<T> nodes, std::vector<std::tuple<T, T, int>> edges);
	Graph(const Graph& origin) = delete;
	Graph& operator=(const Graph& origin) = delete;
	~Graph();
	unsigned int nrOfNodes() const;
	unsigned int nrOfEdges() const;

	void allNodes(std::vector<T>& nodes) const;
	void nodesAdjacentTo(const T& node, std::vector<T>& adjacentNodes) const;
	int getWeight(const T& from, const T& to) const;
	void shortestPathFrom(T from, T to, std::vector<std::pair<T, int>>& shortestPath) const;
	void MST(std::vector<std::tuple<T, T, int>>& mst);
};

#endif