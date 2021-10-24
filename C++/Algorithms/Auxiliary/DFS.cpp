#include <iostream>
#include "../../Structures/Graph.h"
#include "../../Structures/Tree.h"

#define BOT -1

/** Depth-First-Search on a connected graph.
 * @param  R Root of the Tree.
 * @param  G Graph to construct the Tree on.
 * @return DFS Tree of the given graph.
 */
Tree Tree::DFS(int R, const Graph& G) {
    Tree T(R, G.vertices());

    std::function<void(int)> traverse;
    traverse = [&](int i) {
        for (int j = 0; j < G.vertices(); ++j) {
            if (G[i][j] != BOT && T.P[j] == BOT && j != R) {
                T.P[j] = i;
                T.C[i].push_back(j);
                traverse(j);
            }
        }
    };

    traverse(R);
    return T;
}