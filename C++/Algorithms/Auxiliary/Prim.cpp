#include <iostream>
#include "../../Structures/Graph.h"
#include "../../Structures/Tree.h"

#define BOT Edge(0, 0, 0)
#define INF -1

/** Prim on a connected graph. 
 * Computes a Tree whith the minimum total weight.
 * @param  R Root of the Tree.
 * @param  G Graph to construct the Tree on.
 * @return MST of the given graph.
 */
Tree Tree::Prim(int R, const Graph& G) {
    Tree T(R, G.vertices());
    std::set<int> V = {R};

    //Returns the minimum weight edge that connects V and V(G) / V
    std::function<Edge(const std::set<int>&)> min_bridge;
    min_bridge = [&G](const std::set<int>& V) {
        Edge min = BOT;

        for (int i : V)
            for (int j = 0; j < G.vertices(); ++j)
                if (!V.count(j))
                    if (G[i][j] != INF && (min == BOT || G[i][j] < min.weight))
                        min = {i, G[i][j], j};
        return min;
    };
    
    for (size_t i = 1; i < G.vertices(); ++i) {
        Edge e = min_bridge(V);
        if (e == BOT) 
            throw std::domain_error("Graph is not connected.");
        V.insert(e.to);
        T.P[e.to] = e.from;
        T.C[e.from].push_back(e.to);
    }
    
    return T;
}