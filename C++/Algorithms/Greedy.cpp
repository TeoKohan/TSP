#include <assert.h>
#include"Algorithms.h"

namespace Algorithm {

    #define BOT -1
    #define INF -1

    namespace {

        std::function<int(int, const std::set<int>&, const Graph&)> min
        = [](int i, const std::set<int>& V, const Graph& G) {
            int v = BOT;
            int min = INF;
            for (int j = 0; j < G.vertices(); ++j)
                if (!V.count(j))
                    if ((min == INF && G[i][j] != INF) || G[i][j] < min) {
                        min = G[i][j];
                        v = j;
                    }
                    
            if (v == BOT)
                throw std::domain_error("Graph is not connected.");
            return v;
        };

        Solution greedy(int R, const Graph& G, std::function<int(int, const std::set<int>&, const Graph&)> f) {
            Solution S = {0, {R}};
            std::set<int> V = {R};

            while (S.path.size() < G.vertices()) {
                int u = *S.path.rbegin();
                int v = f(u, V, G);
                V.insert(v);
                S.path.push_back(v);
                S.weight += G[u][v];
            }
            S.weight += G[*S.path.begin()][*S.path.rbegin()];
            assert(S.weight == S.evaluate(S.path, G));
            return S;   
        }
    }

    Solution greedy(int R, const Graph& G) {
            return greedy(R, G, min);   
    }

    Solution greedy_all(int R, const Graph& G) {
        Solution S(INF, Path());
        for (int i = 0; i < G.vertices(); ++i)
            S = S.weight == INF ? greedy(i, G, min) : std::min(S, greedy(i, G, min));
        S.center();
        return S;
    }
}
