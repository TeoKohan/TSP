#include<assert.h>
#include<algorithm>
#include<map>
#include"Algorithms.h"
#include"../Structures/Graph.h"

#define INF -1
#define EMPTY_SWAP {{0, 0}, {0, 0}}
#define print(x) std::cout<< x << std::endl

namespace Algorithm {

    Solution tabu_search(int R, const Graph& G) {

        int n = G.vertices();
        matrix<int> aspiration (n, std::vector<int>(n));
        std::queue<SwapSolution> Q;
        std::set<Swap> TSwaps;
        std::set<Solution> TSolutions;
        matrix<int> apparitions (n, std::vector<int>(n));

        std::function<int(const Path&)> fitness =
        [&] (const Path& P) {
            
            int fitness;

            for (int i = 0; i < n; ++i) {
                int j = (i+1) % n;
                //lower fitness is better
                fitness -= G[P[i]][P[j]] * 100 + aspiration[P[i]][P[j]] * 100 - apparitions[P[i]][P[j]] * 50;
            }

            return fitness;
        };

        std::function<bool(const SwapSolution&, const SwapSolution&)> least_fit =
        [&fitness] (const SwapSolution& S, const SwapSolution& R) {
            return fitness(S.solution.path) < fitness(R.solution.path);
        };

        std::function<std::vector<Edge> (const matrix<int>&)> least_traveled_edges =
        [&G] (const matrix<int>& apparitions) -> std::vector<Edge> {
            
            std::function<bool(Edge, Edge)> least_apparitions =
            [&apparitions] (Edge a, Edge b) {
                return apparitions[a.from][a.to] > apparitions[b.from][b.to]; // > just because
            };
            
            std::vector<Edge> sorted;
            for (int i = 0; i < apparitions.size(); ++i)
                for (int j = 0; j < i; ++j)
                    sorted.push_back({i, j});

            std::sort(sorted.begin(), sorted.end(), least_apparitions);

            return sorted;
        };

        std::function<Solution (const std::vector<Edge>&)> least_traveled =
        [&G] (const std::vector<Edge>& least_apparitions ) -> Solution {
            Path P;

            std::function<bool(Edge&, int)> connects =
            [] (Edge& E, int v) {
                if (E.from == v)
                    return true;
                E.swap();
                if (E.from == v)
                    return true;
                return false;
            };   
 
            if (least_apparitions.size() == 0)
                return {0, {}};

            P = {(*least_apparitions.begin()).from, (*least_apparitions.begin()).to};
            std::set<int> V = {(*least_apparitions.begin()).from, (*least_apparitions.begin()).to};
            
            for (auto it = least_apparitions.begin()+1; it != least_apparitions.end(); ++it) {
                Edge E = *it;
                int previous = *P.rbegin();
                if (connects(E, previous) && V.count(E.to) == 0) {
                    P.push_back(E.to);
                    V.insert(E.to);
                }
                
                else if (!(V.count(E.from) || V.count(E.to))) {
                    if (G[previous][E.to] < G[previous][E.from])
                        E.swap();
                    
                    P.push_back(E.from);
                    P.push_back(E.to);
                    V.insert(E.from);
                    V.insert(E.to);
                }        
                if (P.size() >= G.vertices())
                    break;
            }

            return {Solution::evaluate(P, G), P};
        };
        
        std::function<void(SwapSolution, const Solution&)> register_solution =
        [&] (SwapSolution SwSol, const Solution& best) {
            const int MAX_Q_SIZE = 32;

            Solution S = SwSol.solution;
            Swap W = SwSol.swap;
            Path P = S.path;
            
            S.weight = best.weight - S.weight;
            Q.push(SwSol);
            TSolutions.insert(S);
            TSwaps.insert(W);
            for (int i = 0; i < n; ++i) {
                ++apparitions[P[i]][P[(i+1)%n]];
                // apparitions[Q.front().path[i]][Q.front().path[(i+1)%n]] -= 
                //                                    Q.size() > MAX_Q_SIZE;
                Solution R = Q.front().solution;
                aspiration[P[i]][P[(i+1)%n]] += S.weight;
                aspiration[R.path[i]][R.path[(i+1)%n]] -=
                                                    Q.size() > MAX_Q_SIZE * R.weight;                                  
            }

            if (Q.size() > MAX_Q_SIZE) {
                TSolutions.erase(Q.front().solution);
                TSwaps.erase(Q.front().swap);
                Q.pop();
            }

            return;
        };

        std::function<std::set<SwapSolution>*(Solution, const Graph&, int)> two_opt = 
        [] (Solution S, const Graph& G, int k) -> std::set<SwapSolution>* {
            std::function<int(int a, int b, int c, int d)> swap_weight =
            [&G](int a, int b, int c, int d) {
                return (G[a][c] + G[b][d]) - (G[a][b] + G[c][d]); //swapped - former
            };

            std::set<SwapSolution>* SS = new std::set<SwapSolution>();

            auto a = S.path.begin(), c = a + 1;
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

                    Swap SW = {{*a, *c}, {*b, *d}};
                    SS->insert({SW, S});
                    S = T;
                    if (SS->size() > k)
                        SS->erase(std::prev(SS->end()));
                }

                if (++c == S.path.end())
                    if (++a != S.path.end())
                        c = a + 1;
            }

            return SS;
        };

        if (G.vertices() == 1)
                return {0, {}};

        SwapSolution best = {EMPTY_SWAP, Algorithm::greedy(R, G)};
        SwapSolution actual = best;

        int const MAX_ITER = 512;
        int iterations = MAX_ITER;

        while (iterations--) {
            auto N = two_opt(actual.solution, G, 8);

            // N->erase(std::remove_if(N->begin(),
            //                         N->end(),
            //                         [&](const Solution a) {return true;}),
            //         N->end());

            for (auto it = N->begin(); it != N->end();)
                if (TSolutions.count((*it).solution) || TSwaps.count((*it).swap))
                    N->erase(it++);
                else
                    ++it;

            if (!N->size()) {
                auto L = least_traveled(least_traveled_edges(apparitions));
                N->insert({EMPTY_SWAP, L});
            }

            best   = std::min(best, *std::min_element(N->begin(), N->end()));
            actual = *std::max_element(N->begin(), N->end(), least_fit);

            register_solution(actual, best.solution);

            delete(N);
        }

        // %N -%N+random %LV -> vector[vector[TSwaps]]
        
        return best.solution;
    }
}