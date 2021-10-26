#include<assert.h>
#include<algorithm>
#include"Algorithms.h"

#define INF -1
#define MAX_ALL 300

namespace Algorithm {

    Solution two_opt (Solution& S, int a, int b, int c, int d, const Graph& G) {

        Solution R = S;
        assert(a < R.path.size() && b < R.path.size() && c < R.path.size() && d < R.path.size());
        R.weight += (G[a][c] + G[b][d]) - (G[a][b] + G[c][d]);

        if (b < c)
            std::reverse(R.path.begin()+b, R.path.begin()+(c+1));
        else
            std::reverse(R.path.begin()+d, R.path.begin()+(a+1));

        assert(R.weight == R.reevaluate(G));
        return R;
    }

    Solution& two_opt (Solution& S, const Graph& G) {

        std::function<int(int a, int b, int c, int d)> swap_weight =
        [&S, &G](int a, int b, int c, int d) {
            return (G[a][c] + G[b][d]) - (G[a][b] + G[c][d]); //swapped - former
        };

        auto a = S.path.begin(), c = S.path.begin();
        while (a != S.path.end() && c != S.path.end()) {
            auto b = a+1 == S.path.end() ? S.path.begin() : a+1;
            auto d = c+1 == S.path.end() ? S.path.begin() : c+1;
            if (a != c && swap_weight(*a, *b, *c, *d) < 0) {
                S.weight += swap_weight(*a, *b, *c, *d);

                if (b < c)
                    std::reverse(b, c+1);
                else
                    std::reverse(d, a+1);
                
                return S;
            }

            if (++c == S.path.end())
                if (++a != S.path.end())
                    c = S.path.begin();
        }

        assert(S.weight == S.reevaluate(G));
        return S;
    }

    Solution local_search(int R, const Graph& G) {
        Solution S = G.vertices() > MAX_ALL ? greedy(R, G) : greedy_all(G);

        int weight = S.weight;
        while (weight != two_opt(S, G).weight)
            weight = S.weight;
        
        S.center(0);
        return S;
    }
}