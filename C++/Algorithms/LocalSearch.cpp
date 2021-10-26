#include<assert.h>
#include<algorithm>
#include"Algorithms.h"

#define MAX_ALL 300

namespace Algorithm {

    Solution local_search(int R, const Graph& G) {
        Solution S = G.vertices() > MAX_ALL ? greedy(R, G) : greedy_all(G);

        std::function<int(int a, int b, int c, int d)> swap_weight =
        [&S, &G](int a, int b, int c, int d) {
            return (G[a][c] + G[b][d]) - (G[a][b] + G[c][d]);
        };

        int timer = 5000;
        auto a = S.path.begin(), c = S.path.begin();
        while (timer) {
            auto b = a+1 == S.path.end() ? S.path.begin() : a+1;
            auto d = c+1 == S.path.end() ? S.path.begin() : c+1;
            if (a != c && swap_weight(*a, *b, *c, *d) < 0) {
                S.weight += swap_weight(*a, *b, *c, *d);

                if (b < c)
                    std::reverse(b, c+1);
                else
                    std::reverse(d, a+1);

                timer = 5000;
            }
            --timer;
            //std::cout << "t: " << timer << std::endl;
            ++c;
            if (c == S.path.end()) {
                a = b;
                c = S.path.begin();
            }
        }
        S.center(0);
        std::cout << S.weight << "   " << S.reevaluate(G) << std::endl;
        assert(S.weight == S.reevaluate(G));
        assert(!S.repeats());
        return S;       
    }
}