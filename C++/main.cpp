#include<assert.h>
#include<algorithm>

#include "Structures/Graph.h"
#include "Structures/Tree.h"

#include "IO/IO.h"
#include "IO/Time.h"

#include "Algorithms/Algorithms.h"

#include <functional>
#include <iostream>
#include <vector>
#include <set>
#include <map>

#define INF -1

std::string Python = "../Test/Python/";
std::string Elib = "../Test/Elib/";

std::string p_limited = "complete-graph-limited-values/";
std::string p_normal  = "complete-graph-normal-dist/";
std::string p_random  = "complete-graph-random-weight/";

int main(int argc, char* argv[]) {
    Solution S;
    Graph G;
    
    IO reader(Elib);

    std::vector<IO::TSPName> fs = 
    {{"greedy", Algorithm::greedy}, /*{"MST", Algorithm::MST},*/
     {"local search", Algorithm::local_search}, {"tabu", Algorithm::tabu_search}};
    std::map<std::string, int> winner_count;

    auto GS = reader.read("a280.tsp.formatted");
    std::cout << "=====|=====|=====" << std::endl;
    for (const auto& G : GS) {
        
        int min = INF;
        std::string min_n = fs[0].name;
        std::cout << "vertices: " << G.vertices() << std::endl;
        //std::cout << "MST: " << Tree::Prim(0, G).total_weight(G) << std::endl;
        for (const auto& f : fs) {
            auto ST = Time::run_function(0, G, f.algorithm);
            if (min == INF || ST.result.weight < min) {
                min = ST.result.weight;
                min_n = f.name;
            }
            std::cout << f.name << " - " << ST.result.weight << " - " << ST.time << std::endl;
        }
        std::cout << "=====|=====|=====" << std::endl;
        ++winner_count[min_n];
    }

    for (auto o : winner_count)
    std::cout << o.first << ": " << o.second << "  ";
    std::cout << std::endl;

    std::function<bool(std::pair<const std::string, int>&, std::pair<const std::string, int>&)> key_comp =
    [] (std::pair<const std::string, int>& a, std::pair<const std::string, int>& b) {
        return a.second > b.second;
    };
    
    auto W = (*std::min_element(winner_count.begin(), winner_count.end(), key_comp));
    std::cout << "winner: " << W.first << " with " << W.second << " wins." << std::endl;

    return 1;
}