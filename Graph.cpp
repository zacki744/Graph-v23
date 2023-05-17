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
    // Skapa en mängd för ohanterade noder och en karta för att spåra tidigare noder
    std::set<std::pair<int, T>> unvisitedNodes;
    std::unordered_map<T, T> previousNodes;

    // Sätt alla avstånd till oändligt förutom från-noden, som är 0
    std::unordered_map<T, int> distances;
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
        auto current = unvisitedNodes.begin()->second;
        unvisitedNodes.erase(unvisitedNodes.begin());

        // Om vi har nått till-noden, så är kortaste vägen hittad och vi kan avsluta
        if (current == to) {
            break;
        }

        // Gå igenom alla grannar till noden och uppdatera avstånden om de är kortare än tidigare beräknade avstånd
        for (const auto& neighbor : adjList.at(current)) {
            auto newDistance = distances[current] + neighbor.second;
            if (newDistance < distances[neighbor.first]) {
                unvisitedNodes.erase({ distances[neighbor.first], neighbor.first });
                distances[neighbor.first] = newDistance;
                previousNodes[neighbor.first] = current;
                unvisitedNodes.emplace(distances[neighbor.first], neighbor.first);
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
    int i = 0;
    for (const auto& n : adjList) {
        if (n.first == node) {
            return i;
        }
        i++;
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

    // Create a vector of all edges sorted by weight
    std::vector<std::tuple<int, int, int>> edges;
    for (auto it = adjList.begin(); it != adjList.end(); ++it) {
        const T& fromNode = it->first;
        const std::vector<std::pair<T, int>>& neighbors = it->second;
        for (auto jt = neighbors.begin(); jt != neighbors.end(); ++jt) {
            const T& toNode = jt->first;
            const int weight = jt->second;
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