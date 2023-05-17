#include <tuple>
#include <vector>
#include <string>
#include <iostream>
#include <utility> 
#include <map>

int main()
{
	std::pair<std::string, int> aPair = std::make_pair("String", 55);

	std::cout << aPair.first << "," << aPair.second << std::endl;

	std::vector<std::pair<std::string, int>> pairs;
	pairs.push_back(aPair);

	std::cout << pairs[0].first << "," << pairs[0].second << std::endl;

	std::cout << std::get<0>(aPair) << "," << std::get<1>(aPair) << std::endl;


	std::tuple<std::string, std::string, int> tup;
	tup = std::make_tuple("from", "to", 99);
	std::cout << std::get <0>(tup) << ", " << std::get <1>(tup) << ", " << std::get <2>(tup) << std::endl;
	
	std::vector<std::tuple<std::string, std::string, int>> tupleVect;
	tupleVect.push_back(tup);

	tup = tupleVect[0];
	std::cout << std::get <0>(tup) << ", " << std::get <1>(tup) << ", " << std::get <2>(tup) << std::endl;

	std::map<std::string, int > aMap;


	aMap["First"] = 1;
	aMap["Second"] = 2;

	std::cout << aMap["First"] << ", " << aMap["Second"] << std::endl;

	for (auto str : aMap)
		std::cout << str.first << ", " << str.second << std::endl;

	return 0;
}