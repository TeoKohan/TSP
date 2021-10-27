cmake_minimum_required(VERSION 3.8)
# set the project name and version
project(TSP VERSION 1.0 LANGUAGES CXX)

message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

IF(CMAKE_BUILD_TYPE MATCHES Debug)
  message("Debug build.")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
  message("Release build.")
ENDIF()


# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


#add library
add_library(TSPlib STATIC 
	C++/Structures/Graph.cpp
	C++/Structures/Tree.cpp
	C++/IO/IO.cpp
	C++/IO/Time.cpp
	C++/Algorithms/Auxiliary/BFS.cpp
	C++/Algorithms/Auxiliary/DFS.cpp
	C++/Algorithms/Auxiliary/Prim.cpp
	C++/Algorithms/Greedy.cpp
	C++/Algorithms/MST.cpp
	C++/Algorithms/LocalSearch.cpp
	C++/Algorithms/Tabu.cpp
	)
target_include_directories(TSPlib PUBLIC
	C++/IO
	C++/Structures
	C++/Algorithms 
	C++/Algorithms/Auxiliary
	)

# add the executable
add_executable(TSP C++/main.cpp)
target_link_libraries(TSP PUBLIC TSPlib)

