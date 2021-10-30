#include <algorithm>
#include <iostream>
#include <assert.h>
#include "../../Structures/Graph.h"
#include "../../Structures/Tree.h"

#define BOT -1
#define INF -1

/** Prim on a connected graph. 
 * Computes a Tree whith the minimum total weight.
 * @param  R Root of the Tree.
 * @param  G Graph to construct the Tree on.
 * @return MST of the given graph.
 */
Tree Tree::Prim(int R, const Graph& G) {
    Tree T(R, G.vertices());
    std::vector<bool> V(G.vertices(), false);
    std::vector<int> D = G[R];
    T.P = std::vector<int>(G.vertices(), R);
    T.P[R] = BOT;
    V[R] = true;
    
    for (size_t i = 1; i < G.vertices(); ++i) {
        int v = BOT;
        for (int j = 0; j < G.vertices(); ++j) {
            if (!V[j]) {
                v = (v == BOT ? j : std::min(v, j, [&D](int a, int b){return D[a] < D[b];}));
            }
        }
         
        V[v] = true;
        for (int j = 0; j < G.vertices(); ++j)
            if (!V[j] && G[v][j] < D[j]) {
                D[j] = G[v][j];
                T.P[j] = v;
            }
    }
    
    for (int i = 0; i < T.P.size(); ++i)
        if (T.P[i] != BOT)
            T.C[T.P[i]].push_back(i);
    //std::cout << T << std::endl;
    return T;
}