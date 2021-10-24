#include "IO/IO.h"
#include "Structures/Graph.h"
#include "Structures/Tree.h"
#include <iostream>
#include <string>
#include<vector>
#include<set>

int main(int argc, char* argv[]) {
    Graph G;
    G = Graph(3, {{0, 1}, {0, 2}, {1, 2}});
    G = Graph(4, {{0, 1}, {0, 2}, {1, 2}, {2, 3}});
    Tree T = Tree::DFS(0, G);

    IO test("../Test/Python/");
    G = test.read("complete-graph-random-weight/WEIGHT-1-to-20-n-5.txt");
    std::cout << G;
}