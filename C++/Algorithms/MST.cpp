#include"Algorithms.h"

namespace Algorithm {

    #define INF -1

    Solution MST(int R, const Graph& G) {
        Tree T = Tree::Prim(R, G);
        Solution S = {0, {R}};

        std::function<void(int)> traverse;
        traverse = [&](int u) {
            for (int v : T.children(u)) {
                S.weight += G[*S.path.rbegin()][v];
                //std::cout << "(" << *S.path.rbegin() << ", " << G[*S.path.rbegin()][v] << ", " << v << ")" << std::endl;
                S.path.push_back(v);
                traverse(v);
            }
        };

        traverse(R);
        S.weight += G[*S.path.rbegin()][R];
        //std::cout << "(" << *S.path.rbegin()<< ", " << G[*S.path.rbegin()][R] << ", " << R << ")" << std::endl;

        return S;
    }

    Solution MST_all(const Graph& G) {
        Solution S(INF, Path());
        for (int i = 0; i < G.vertices(); ++i)
            S = S.weight == INF ? MST(i, G) : std::min(S, MST(i, G)); 
        return S;
    }
}