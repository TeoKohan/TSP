#include "Structures/Graph.h"
#include "Structures/Tree.h"

#include "IO/IO.h"
#include <iostream>

#include "Algorithms/Algorithms.h"

#include <chrono>
#include <thread>

#include<string>
#include<vector>
#include<set>

int main(int argc, char* argv[]) {
    Solution S;
    Graph G;
    std::string limited = "../Test/Python/complete-graph-limited-values/";
    std::string normal = "../Test/Python/complete-graph-normal-dist/";
    std::string random = "../Test/Python/complete-graph-random-weight/";
    
    IO reader(random);

    int winner[] = {0, 0, 0, 0};

    for (int i = 1; i <= 200; ++i) {
    std::string path = "WEIGHT-1-to-1000-n-";
    path += std::to_string(i);
    path += ".txt";
    G = reader.read(path);
    
    std::cout << "n: " << i << "   MST: " << Tree::Prim(0, G).total_weight(G) << std::endl;
    
    S = Algorithm::greedy(0, G);
    std::cout << "greedy - ROOTED " << S.weight << std::endl;
    
    int w = 0;
    int min = S.weight;

    S = Algorithm::greedy_all(G);
    std::cout << "greedy - ALL " << S.weight << std::endl;
    if (S.weight < min) {w = 1; min = S.weight;}

    S = Algorithm::MST(0, G);
    std::cout << "MST - ROOTED " << S.weight << std::endl;
    if (S.weight < min) {w = 2; min = S.weight;}

    S = Algorithm::local_search(0, G);
    std::cout << "Lsearch - ROOTED " << S << std::endl;
    if (S.weight < min) {w = 3; min = S.weight;}

    std::cout << "-----------------" << std::endl;
    
    winner[w]++;

    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << std::endl << "Greed: " << winner[0] << 
                              "  Greed All: " << winner[1] << 
                              "  MST: " << winner[2] <<
                              "  LS: " << winner[3] << std::endl; 
    std::cout << "-----------------" << std::endl;

    return 1;
}