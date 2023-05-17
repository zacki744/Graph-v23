#include "catch_amalgamated.hpp"
#include "Graph.cpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>


template<typename T>
inline bool sameContent(std::vector<T> vectOne, std::vector<T> vectTwo)
{
	bool ok = vectOne.size() == vectTwo.size();
	size_t nrOfNodes = vectOne.size();
	std::vector<bool> sameNodes(nrOfNodes, false);
	for (auto elem : vectOne)
	{
		for (size_t i = 0; i < nrOfNodes; i++)
			if (elem == vectTwo[i])
				sameNodes[i] = true;
	}

	for (size_t i = 0; i < nrOfNodes; i++)
		if (!sameNodes[i])
			ok = false;
	return ok;
}

bool readFromFile(std::string filename, std::string& typeOfGraph, std::vector<std::string>& nodes, std::vector<std::tuple<std::string, std::string, int>>& edges)
{
	bool ok = false;
	std::ifstream in("../../../" + filename);
	if (in.is_open())
	{
		std::string dummy;
		in >> typeOfGraph;

		std::string nodename;
		in >> dummy;
		in >> nodename;

		bool nodesDone = false;
		while (!nodesDone)
		{
			nodes.push_back(nodename);
	
			in >> nodename;
			if (nodename == "-")
				nodesDone = true;
		}

		std::string from;
		std::string to;
		int weight;
		bool edgesDone = false;
		std::string line;
		size_t indexFirst = -1;
		size_t indexLast = -1;

		in >> line;
		while (!edgesDone)
		{
			indexFirst = line.find_first_of("#");
			indexLast = line.find_last_of("#");
			from = line.substr(0, indexFirst);
			to = line.substr(indexFirst + 1, (indexLast - indexFirst - 1));
			weight = atoi((line.substr(indexLast + 1, std::string::npos)).c_str());
			edges.push_back(std::make_tuple(from, to, weight));
			if (typeOfGraph == "U")
				edges.push_back(std::make_tuple(to, from, weight));
		
			in >> line;
			if (line == "-")
				edgesDone = true;
		}
		ok = true;
	}
	else
	{
		std::cout << "Was not able to open file " << filename << std::endl;
	}
	in.close();
	return ok;

}



TEST_CASE("Test: creating directed Graph<int> object with only 1 node")
{
	std::vector<int> nodes({ 0 });
	std::vector<std::tuple<int, int, int>> edges;

	Graph<int> graph(Graph<int>::GRAPH_TYPE::DIRECTED, nodes, edges);
	REQUIRE(graph.nrOfNodes() == 1);
	REQUIRE(graph.nrOfEdges() == 0);
	REQUIRE(graph.getWeight(0, 4) == -1);
}

TEST_CASE("Test: creating directed Graph<std::string> object with only 1 node")
{
	std::vector<std::string> nodes({ "0"});
	std::vector<std::tuple<std::string, std::string, int>> edges;

	Graph<std::string> graph(Graph<std::string>::GRAPH_TYPE::DIRECTED, nodes, edges);

	REQUIRE(graph.nrOfNodes() == 1);
	REQUIRE(graph.nrOfEdges() == 0);
	REQUIRE(graph.getWeight("0", "4") == -1);
}

TEST_CASE("Test: creating undirected Graph<int> object with 3 nodes, and 2 edges ")
{
	std::vector<int> nodes({ 0, 1, 2 });
	std::vector<std::tuple<int, int, int>> edges;
	edges.push_back(std::make_tuple(0, 1, 10));
	edges.push_back(std::make_tuple(1, 0, 10));
	edges.push_back(std::make_tuple(0, 2, 7));
	edges.push_back(std::make_tuple(2, 0, 7));

	Graph<int> graph(Graph<int>::GRAPH_TYPE::UNDIRECTED, nodes, edges);

	REQUIRE(graph.nrOfNodes() == 3);
	REQUIRE(graph.nrOfEdges() == 2);
	REQUIRE(graph.getWeight(0, 1) == 10);
	REQUIRE(graph.getWeight(1, 0) == 10);
	REQUIRE(graph.getWeight(0, 2) == 7);
	REQUIRE(graph.getWeight(2, 0) == 7);
	REQUIRE(graph.getWeight(2, 1) == -1);
	REQUIRE(graph.getWeight(1, 2) == -1);
}

TEST_CASE("Test: creating directed Graph<std::string> object with 3 nodes, and 2 edges ")
{
	std::vector<std::string> nodes({ "0", "1", "2" });
	std::vector<std::tuple<std::string, std::string, int>> edges;
	edges.push_back(std::make_tuple("0", "1", 10));
	edges.push_back(std::make_tuple("2", "0", 7));

	Graph<std::string> graph(Graph<std::string>::GRAPH_TYPE::DIRECTED, nodes, edges);

	REQUIRE(graph.nrOfNodes() == 3);
	REQUIRE(graph.nrOfEdges() == 2);
	
	std::vector<std::string> nodesFromGraph;
	graph.allNodes(nodesFromGraph);
	
	REQUIRE(graph.getWeight("0", "1") == 10);
	REQUIRE(graph.getWeight("1", "0") == -1);
	REQUIRE(graph.getWeight("0", "2") == -1);
	REQUIRE(graph.getWeight("2", "0") == 7);
	REQUIRE(graph.getWeight("2", "1") == -1);
	REQUIRE(graph.getWeight("1", "2") == -1);

	REQUIRE(sameContent(nodes, nodesFromGraph));
}

TEST_CASE("Test: creating undirected Graph<std::string> reading from file ")
{
	std::vector<std::string> nodes;
	std::vector<std::tuple<std::string, std::string, int>> edges;
	std::string typeOfGraph; 
	readFromFile(std::string("graph01_U.txt"), typeOfGraph, nodes, edges);
	Graph<std::string>::GRAPH_TYPE type;
	if (typeOfGraph == "U")
		type = Graph<std::string>::GRAPH_TYPE::UNDIRECTED;
	else
		type = Graph<std::string>::GRAPH_TYPE::DIRECTED;

	Graph<std::string> graph(type, nodes, edges);

	REQUIRE(graph.nrOfNodes() == 5);
	REQUIRE(graph.nrOfEdges() == 7);

	std::vector<std::string> nodesFromGraph;
	graph.allNodes(nodesFromGraph);

	REQUIRE(sameContent(nodes, nodesFromGraph));
}

TEST_CASE("Test: creating directed Graph<std::string> reading from file ")
{
	std::vector<std::string> nodes;
	std::vector<std::tuple<std::string, std::string, int>> edges;
	std::string typeOfGraph;
	readFromFile(std::string("graph02_D.txt"), typeOfGraph, nodes, edges);
	Graph<std::string>::GRAPH_TYPE type;
	if (typeOfGraph == "U")
		type = Graph<std::string>::GRAPH_TYPE::UNDIRECTED;
	else
		type = Graph<std::string>::GRAPH_TYPE::DIRECTED;

	Graph<std::string> graph(type, nodes, edges);
	REQUIRE(graph.nrOfNodes() == 5);
	REQUIRE(graph.nrOfEdges() == 6);

	std::vector<std::string> nodesFromGraph;
	graph.allNodes(nodesFromGraph);

	REQUIRE(sameContent(nodes, nodesFromGraph));
}

TEST_CASE("Test: shortets path on very small Graph")
{
	std::vector<std::string> nodes;
	std::vector<std::tuple<std::string, std::string, int>> edges;
	std::string typeOfGraph;
	readFromFile(std::string("graph02_D.txt"), typeOfGraph, nodes, edges);
	Graph<std::string>::GRAPH_TYPE type;
	if (typeOfGraph == "U")
		type = Graph<std::string>::GRAPH_TYPE::UNDIRECTED;
	else
		type = Graph<std::string>::GRAPH_TYPE::DIRECTED;

	Graph<std::string> graph(type, nodes, edges);
	std::vector<std::pair<std::string, int>> path;
	std::vector<std::pair<std::string, int>> correctPath;
	correctPath.push_back(std::make_pair("a", 0));
	correctPath.push_back(std::make_pair("b", 10));
	graph.shortestPathFrom("a", "b", path);
	REQUIRE(path == correctPath);

	path.clear();
	correctPath.clear();
	correctPath.push_back(std::make_pair("a", 0));
	correctPath.push_back(std::make_pair("b", 10));
	correctPath.push_back(std::make_pair("c", 14));
	graph.shortestPathFrom("a", "c", path);
	REQUIRE(path == correctPath);

	path.clear();
	correctPath.clear();
	correctPath.push_back(std::make_pair("d", 0));
	correctPath.push_back(std::make_pair("e", 1));
	correctPath.push_back(std::make_pair("c", 3));
	graph.shortestPathFrom("d", "c", path);
	REQUIRE(path == correctPath);
}

TEST_CASE("Test: shortets path on small Graph")
{
	std::vector<std::string> nodes;
	std::vector<std::tuple<std::string, std::string, int>> edges;
	std::string typeOfGraph;
	readFromFile(std::string("graph03_D.txt"), typeOfGraph, nodes, edges);
	Graph<std::string>::GRAPH_TYPE type;
	if (typeOfGraph == "U")
		type = Graph<std::string>::GRAPH_TYPE::UNDIRECTED;
	else
		type = Graph<std::string>::GRAPH_TYPE::DIRECTED;

	Graph<std::string> graph(type, nodes, edges);
	std::vector<std::pair<std::string, int>> path;
	std::vector<std::pair<std::string, int>> correctPath;
	correctPath.push_back(std::make_pair("d", 0));
	correctPath.push_back(std::make_pair("g", 2));
	correctPath.push_back(std::make_pair("h", 8));
	graph.shortestPathFrom("d", "h", path);
	REQUIRE(path == correctPath);

	path.clear();
	correctPath.clear();
	correctPath.push_back(std::make_pair("d", 0));
	correctPath.push_back(std::make_pair("g", 2));
	correctPath.push_back(std::make_pair("i", 6));
	graph.shortestPathFrom("d", "i", path);
	REQUIRE(path == correctPath);

}

