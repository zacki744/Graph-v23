# CMakeList.txt : CMake project for Graph v23, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Graph v23")

# Add source to this project's executable.
add_executable (main  "Graph.h" "Graph.cpp" "DisjointSets.h" "DisjointSets.cpp" "main.cpp")
add_executable (test  "Graph.h" "Graph.cpp" "DisjointSets.h" "DisjointSets.cpp" "catch_amalgamated.cpp" "catch_amalgamated.hpp" "Testgraph.cpp")


# TODO: Add tests and install targets if needed.
