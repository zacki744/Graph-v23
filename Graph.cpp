#include "DisjointSets.h"
#include "Graph.h"



template <typename T>
Graph<T>::Graph(GRAPH_TYPE graphType, std::vector<T> nodes, std::vector<std::tuple<T, T, int>> edges)
{
    this->graphType = graphType;
    for (const auto& node : nodes)
    {
        adjList[node] = {};
    }

    for (const auto& edge : edges)
    {
        T from = std::get<0>(edge);
        T to = std::get<1>(edge);
        int weight = std::get<2>(edge);

        adjList[from].push_back({ to, weight });

        if (graphType == GRAPH_TYPE::UNDIRECTED)
        {
            adjList[to].push_back({ from, weight });
        }
    }
    int index = 0;
    for (const auto& u : adjList) {
        const T& node = u.first;
        nodeIndices[node] = index++;
    }
}

template <typename T>
Graph<T>::~Graph()
{
    adjList.clear();
}

template <typename T>
unsigned int Graph<T>::nrOfNodes() const
{
    return adjList.size();
}

template <typename T>
unsigned int Graph<T>::nrOfEdges() const
{
    unsigned int numEdges = 0;
    for (const auto& node : adjList)
    {
        numEdges += node.second.size();
    }
    if (graphType == GRAPH_TYPE::DIRECTED)
    {
        return numEdges;
    }
    return numEdges / 4;
}

template <typename T>
void Graph<T>::allNodes(std::vector<T>& nodes) const
{
    nodes.clear();
    for (const auto& node : adjList)
    {
        nodes.push_back(node.first);
    }
}

template <typename T>
void Graph<T>::nodesAdjacentTo(const T& node, std::vector<T>& adjacentNodes) const
{
    adjacentNodes.clear();
    for (const auto& neighbor : adjList.at(node))
    {
        adjacentNodes.push_back(neighbor.first);
    }
}

template <typename T>
int Graph<T>::getWeight(const T& from, const T& to) const
{
    for (const auto& neighbor : adjList.at(from))
    {
        if (neighbor.first == to)
        {
            return neighbor.second;
        }
    }
    return -1;
}

template <typename T>
void Graph<T>::shortestPathFrom(T from, T to, std::vector<std::pair<T, int>>& shortestPath) const {
    // Skapa en prioritetskö för ohanterade noder och en hashmap för att spåra tidigare noder
    std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, std::greater<>> unvisitedNodes;
    std::unordered_map<T, T> previousNodes;
    std::unordered_map<T, int> distances;

    // Sätt alla avstånd till oändligt förutom från-noden, som är 0
    for (const auto& node : adjList) {
        if (node.first == from) {
            distances[node.first] = 0;
        }
        else {
            distances[node.first] = INFINITY_COST;
        }
        unvisitedNodes.emplace(distances[node.first], node.first);
    }

    while (!unvisitedNodes.empty()) {
        // Välj noden med lägst avstånd som nästa nod att hantera
        auto current = unvisitedNodes.top().second;
        unvisitedNodes.pop();

        // Om vi har nått till-noden, så är kortaste vägen hittad och vi kan avsluta
        if (current == to) {
            break;
        }

        // Gå igenom alla grannar till noden och uppdatera avstånden om de är kortare än tidigare beräknade avstånd
        for (const auto& neighbor : adjList.at(current)) {
            auto newDistance = distances[current] + neighbor.second;
            if (newDistance < distances[neighbor.first]) {
                unvisitedNodes.emplace(newDistance, neighbor.first);
                distances[neighbor.first] = newDistance;
                previousNodes[neighbor.first] = current;
            }
        }
    }

    // Om det inte finns någon väg till to-noden, så returnera en tom vektor
    if (previousNodes.find(to) == previousNodes.end()) {
        shortestPath.clear();
        return;
    }

    // Bygg upp kortaste vägen genom att gå tillbaka från till-noden och spara alla noder och deras avstånd längs vägen
    shortestPath.clear();
    T current = to;
    while (current != from) {
        shortestPath.emplace_back(current, distances[current]);
        current = previousNodes[current];
    }
    shortestPath.emplace_back(from, 0);

    // Vänd på vektorn så att från-noden kommer först
    std::reverse(shortestPath.begin(), shortestPath.end());
}

template <typename T>
int Graph<T>::findIndex(const T& node) const
{
    auto it = nodeIndices.find(node);
    if (it != nodeIndices.end()) {
        return it->second;
    }
    return -1; // node not found
}

template<typename T>
const T& Graph<T>::GetNode(int index) const
{
    auto iter = adjList.begin();
    std::advance(iter, index);
    return iter->first;
}



template <typename T>
void Graph<T>::MST(std::vector<std::tuple<T, T, int>>& mst)
{
    mst.clear();
    DisjointSets ds(adjList.size());
    std::vector<std::tuple<int, int, int>> edges;

    // Create a vector of all edges sorted by weight
    for (const auto& u : adjList) {
        const T& fromNode = u.first;
        const std::vector<std::pair<T, int>>& neighbors = u.second;
        for (const auto& v : neighbors) {
            const T& toNode = v.first;
            const int weight = v.second;
            edges.emplace_back(weight, findIndex(fromNode), findIndex(toNode));
        }
    }
    std::sort(edges.begin(), edges.end());

    // Process edges in increasing order of weight
    for (const auto& edge : edges) {
        int fromIndex = std::get<1>(edge);
        int toIndex = std::get<2>(edge);
        int fromSet = ds.findSet(fromIndex);
        int toSet = ds.findSet(toIndex);
        if (fromSet != toSet) {
            ds.unionSets(fromSet, toSet);
            mst.emplace_back(GetNode(fromIndex), GetNode(toIndex), std::get<0>(edge));
        }
    }
}

