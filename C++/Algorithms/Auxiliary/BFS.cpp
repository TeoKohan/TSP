#include <iostream>
#include "../../Structures/Graph.h"
#include "../../Structures/Tree.h"

#define BOT -1

/** Breadth-First-Search on a connected graph. 
 * Computes a tree which has the shortest 
 * path from the root to any other vertex.
 * @param  R Root of the Tree.
 * @param  G Graph to construct the Tree on.
 * @return BFS Tree of the given graph.
 */
Tree Tree::BFS(int R, const Graph &G) {
    Tree T(R, G.vertices());
    
    std::queue<int> Q;
    Q.push(R);
    
    while (!Q.empty()) {
        int i = Q.front();
        
        Q.pop();
        for (int j = 0; j < G.vertices(); ++j) {
            if (G[i][j] != BOT && T.P[j] == BOT && j != T.R) {
                T.P[j] = i;
                T.C[i].push_back(j);
                Q.push(j);
            }
        }
    }
    return T;
}