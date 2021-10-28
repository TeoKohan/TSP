#include<assert.h>
#include<algorithm>
#include<map>
#include"Algorithms.h"
#include"../Structures/Graph.h"

#define INF -1

namespace Algorithm {

    Solution tabu_search(int R, const Graph& G) {

        int n = G.vertices();
        matrix<int> aspiration (n, std::vector<int>(n));
        std::queue<Solution> Q;
        matrix<int> apparitions (n, std::vector<int>(n));

        std::function<int(const Path&)> fitness =
        [&] (const Path& P) {
            
            int fitness;

            for (int i = 0; i < n; ++i) {
                int j = (i+1) % n;
                fitness += aspiration[P[i]][P[j]] * 100 - apparitions[P[i]][P[j]] * 100 - G[P[i]][P[j]] * 10;
            }

            return fitness;
        };

        std::function<bool(const Solution&, const Solution&)> least_fit =
        [&fitness] (const Solution& S, const Solution& R) {
            return fitness(S.path) < fitness(R.path);
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

        std::function<void(Solution)> register_solution =
        [&] (Solution S) {

            const int MAX_Q_SIZE = 16;

            Path P = S.path;
            S.weight = fitness(P);
            Q.push(S);
            for (int i = 0; i < n; ++i) {
                ++apparitions[P[i]][P[(i+1)%n]];
                apparitions[Q.front().path[i]][Q.front().path[(i+1)%n]] -= 
                                                    Q.size() > MAX_Q_SIZE;

                aspiration[P[i]][P[(i+1)%n]] += S.weight;
                aspiration[Q.front().path[i]][Q.front().path[(i+1)%n]] -=
                                                    Q.size() > MAX_Q_SIZE * Q.front().weight;                                  
            }

            if (Q.size() > MAX_Q_SIZE)
                Q.pop();

            return;
        };

        if (G.vertices() == 1)
                return {0, {}};

        Solution best = Algorithm::greedy(R, G);   //initial solution
        Solution actual = best;

        std::vector<Solution> SS;
        int iterations = 100;
        while (iterations--) {
            auto N = Algorithm::two_opt_conj(actual, G, 256);
            //std::cout << Solution::evaluate(N.top().path, G) << "  -  " << Algorithm::two_opt(actual, G).weight << std::endl;
            while (N->size()) {
                SS.push_back(N->top());
                N->pop();
            }
            delete(N);
            
            SS.push_back(least_traveled(least_traveled_edges(apparitions)));
            
            best   = *std::min_element(SS.begin(), SS.end());
            actual = *std::max_element(SS.begin(), SS.end(), least_fit);

            //register_solution(actual);
        }

        // %N -%N+random %LV -> vector[vector[Swaps]]
        
        return best;
    }
}