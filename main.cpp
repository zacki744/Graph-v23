#include "Graph.cpp"
#include <iostream>

int main() {
    // Create a directed graph with nodes {A, B, C, D} and edges {(A,B,5), (B,C,3), (C,D,1)}
    std::vector<char> nodes = { 'A', 'B', 'C', 'D' };
    std::vector<std::tuple<char, char, int>> edges = { {'A', 'B', 5}, {'B', 'C', 3}, {'C', 'D', 1} };
    Graph<char> g(Graph<char>::GRAPH_TYPE::DIRECTED, nodes, edges);

    // Test nrOfNodes() and nrOfEdges()
    std::cout << "Number of nodes: " << g.nrOfNodes() << std::endl;
    std::cout << "Number of edges: " << g.nrOfEdges() << std::endl;

    // Test allNodes()
    std::vector<char> allNodes;
    g.allNodes(allNodes);
    std::cout << "All nodes: ";
    for (const auto& node : allNodes) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    // Test nodesAdjacentTo()
    std::vector<char> adjNodes;
    g.nodesAdjacentTo('B', adjNodes);
    std::cout << "Nodes adjacent to B: ";
    for (const auto& node : adjNodes) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    // Test getWeight()
    std::cout << "Weight from A to B: " << g.getWeight('A', 'B') << std::endl;
    std::cout << "Weight from B to C: " << g.getWeight('B', 'C') << std::endl;
    std::cout << "Weight from C to D: " << g.getWeight('C', 'D') << std::endl;

    // Test shortestPathFrom()
    std::vector<std::pair<char, int>> shortestPath;
    g.shortestPathFrom('A', 'D', shortestPath);
    std::cout << "Shortest path from A to D: ";
    for (const auto& pair : shortestPath) {
        std::cout << "(" << pair.first << "," << pair.second << ") ";
    }
    std::cout << std::endl;

    // Test MST()
    std::vector<std::tuple<char, char, int>> mst;
    g.MST(mst);
    std::cout << "Minimum Spanning Tree: ";
    for (const auto& triple : mst) {
        std::cout << "(" << std::get<0>(triple) << "," << std::get<1>(triple) << "," << std::get<2>(triple) << ") ";
    }
    std::cout << std::endl;





    // Create a directed graph with nodes {A, B, C, D, E} and edges {(A,B,5), (B,C,3), (C,D,1), (D,E,7), (A,C,8), (B,E,6)}
    std::vector<char> nodes2 = { 'A', 'B', 'C', 'D', 'E' };
    std::vector<std::tuple<char, char, int>> edges2 = { {'A', 'B', 5}, {'B', 'C', 3}, {'C', 'D', 1}, {'D', 'E', 7}, {'A', 'C', 8}, {'B', 'E', 6} };
    Graph<char> g2(Graph<char>::GRAPH_TYPE::DIRECTED, nodes2, edges2);

    // Test shortestPathFrom()
    std::vector<std::pair<char, int>> shortestPath2;
    g2.shortestPathFrom('A', 'E', shortestPath2);
    std::cout << "Shortest path from A to E: ";
    for (const auto& pair : shortestPath2) {
        std::cout << "(" << pair.first << "," << pair.second << ") ";
    }
    std::cout << std::endl;

    // Test MST()
    std::vector<std::tuple<char, char, int>> mst2;
    g2.MST(mst2);
    std::cout << "Minimum Spanning Tree: ";
    for (const auto& triple : mst) {
        std::cout << "(" << std::get<0>(triple) << "," << std::get<1>(triple) << "," << std::get<2>(triple) << ") ";
    }
    std::cout << std::endl;





    // Create a directed graph with nodes {1, 2, 3, 4, 5} and edges {(1,2,5), (2,3,3), (3,4,1), (4,5,7), (1,3,8), (2,5,6), (1,5,9)}
    std::vector<int> nodes1 = { 1, 2, 3, 4, 5 };
    std::vector<std::tuple<int, int, int>> edges1 = { {1,2,5}, {2,3,3}, {3,4,1}, {4,5,7}, {1,3,8}, {2,5,6}, {1,5,9} };
    Graph<int> g1(Graph<int>::GRAPH_TYPE::DIRECTED, nodes1, edges1);

    // Test nrOfNodes() and nrOfEdges()
    std::cout << "Number of nodes in graph 1: " << g1.nrOfNodes() << std::endl;
    std::cout << "Number of edges in graph 1: " << g1.nrOfEdges() << std::endl;

    // Test allNodes()
    std::vector<int> allNodes1;
    g1.allNodes(allNodes1);
    std::cout << "All nodes in graph 1: ";
    for (const auto& node : allNodes1) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    // Test nodesAdjacentTo()
    std::vector<int> adjNodes1;
    g1.nodesAdjacentTo(2, adjNodes1);
    std::cout << "Nodes adjacent to 2 in graph 1: ";
    for (const auto& node : adjNodes1) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    // Test getWeight()
    std::cout << "Weight from 1 to 2 in graph 1: " << g1.getWeight(1, 2) << std::endl;
    std::cout << "Weight from 2 to 3 in graph 1: " << g1.getWeight(2, 3) << std::endl;
    std::cout << "Weight from 3 to 4 in graph 1: " << g1.getWeight(3, 4) << std::endl;

    // Test shortestPathFrom()
    std::vector<std::pair<int, int>> shortestPath1;
    g1.shortestPathFrom(1, 5, shortestPath1);
    std::cout << "Shortest path from 1 to 5 in graph 1: ";
    for (const auto& pair : shortestPath1) {
        std::cout << "(" << pair.first << "," << pair.second << ") ";
    }
    std::cout << std::endl;

    // Test MST()
    std::vector<std::tuple<int, int, int>> mst1;
    g1.MST(mst1);
    std::cout << "Minimum Spanning Tree of graph 1: ";
    for (const auto& triple : mst1)
        std::cout << "(" << std::get<0>(triple) << "," << std::get<1>(triple) << "," << std::get<2>(triple) << ") ";

    return 0;
}
