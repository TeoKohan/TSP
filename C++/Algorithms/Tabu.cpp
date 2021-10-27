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

        std::function<Solution(const matrix<int>&)> least_traveled =
        [&G] (const matrix<int>& apparitions) -> Solution {
            
            std::function<bool(Edge, Edge)> least_apparitions =
            [&apparitions] (Edge a, Edge b) {
                return apparitions[a.from][a.to] > apparitions[b.from][b.to]; // > just because
            };
            
            std::vector<Edge> sorted|;
            for (int i = 0; i < apparitions.size(); ++i)
                for (int j = 0; j < i; ++j)
                    sorted[i * apparitions.size() + j] = {i, j};

            std::sort(sorted.begin(), sorted.end(), least_apparitions);
            Solution R = {Solution::evaluate(sorted, G), sorted};

            R = {Solution::evaluate(sorted, G), sorted};
            return {Solution::evaluate(sorted, G), sorted};
        };

        std::function<void(Solution)> register_solution =
        [&] (Solution S) {

            const int MAX_Q_SIZE = 1024;

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

        Solution best = Algorithm::greedy(R, G);   //initial solution
        Solution actual = best;

        std::vector<Solution> SS;
        int iterations = 100;
        while (iterations--) {
            auto N = Algorithm::two_opt_conj(actual, G, 30);
            //std::cout << Solution::evaluate(N.top().path, G) << "  -  " << Algorithm::two_opt(actual, G).weight << std::endl;
            while (N->size()) {
                SS.push_back(N->top());
                N->pop();
            }
            delete(N);
            
            SS.push_back(least_traveled(apparitions));
            
            best   = *std::min_element(SS.begin(), SS.end());
            actual = *std::max_element(SS.begin(), SS.end(), least_fit);

            //register_solution(actual);
        }

        // %N -%N+random %LV -> vector[vector[Swaps]]
        
        return best;
    }
}