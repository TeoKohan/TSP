#include<assert.h>
#include<algorithm>
#include"Algorithms.h"

#define INF -1

//
//Aspiraciones

namespace Algorithm {

    namespace {
        bool parada() {
            return false;
        }
    }

    Solution tabu_search(int R, const Graph& G, std::function<Solution(int, const Graph&)> f) {

        int timer = 100;

        Solution S = f(R, G);
        std::set<Solution> Top10;
        int n = S.path.size();
        while (timer) {
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    if (i != j) {
                        Top10.insert(two_opt(S, i, (i+1) % n, j, (j+1) % n, G));
                        if (Top10.size() > 10) {
                            auto it = Top10.begin();
                            for (int i = 0; i < 10; ++i)
                                ++it;
                            Top10.erase(it);
                        }
                            
                    }
            
            S = *std::min_element(Top10.begin(), Top10.end());
            Top10.clear();
            --timer;
        }
        

        return *Top10.begin();
    }
}