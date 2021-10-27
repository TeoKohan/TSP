#include<assert.h>
#include<algorithm>
#include"Algorithms.h"

#define INF -1
#define MAX_ALL 300

namespace Algorithm {

    //*
    std::priority_queue<Solution>* two_opt_conj (Solution S, const Graph& G, int k) {

        std::function<int(int a, int b, int c, int d)> swap_weight =
        [&G](int a, int b, int c, int d) {
            return (G[a][c] + G[b][d]) - (G[a][b] + G[c][d]); //swapped - former
        };

        std::priority_queue<Solution>* SS = new std::priority_queue<Solution>();
        SS->push(S);

        auto a = S.path.begin(), c = S.path.begin();
        while (a != S.path.end() && c != S.path.end()) {
            auto b = a+1 == S.path.end() ? S.path.begin() : a+1;
            auto d = c+1 == S.path.end() ? S.path.begin() : c+1;
            if (a != c && swap_weight(*a, *b, *c, *d) < 0) {
                Solution T = S;
                
                S.weight += swap_weight(*a, *b, *c, *d);
                if (b < c)
                    std::reverse(b, c+1);
                else
                    std::reverse(d, a+1);
                
                SS->push(S);
                S = T;
                if (SS->size() > k)
                    SS->pop();
            }

            if (++c == S.path.end())
                if (++a != S.path.end())
                    c = S.path.begin();
        }

        return SS;
    }

    Solution& two_opt (Solution& S, const Graph& G) {

        std::function<int(int a, int b, int c, int d)> swap_weight =
        [&G](int a, int b, int c, int d) {
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

        assert(S.weight == Solution::evaluate(S.path, G));
        return S;
    }

    Solution local_search(int R, const Graph& G) {
        Solution S = G.vertices() > MAX_ALL ? greedy(R, G) : greedy_all(R, G);
        int t = 100;
        int weight = S.weight;
        while (weight != two_opt(S, G).weight) {
            weight = S.weight;
        }
        
        S.center(0);
        return S;
    }
}