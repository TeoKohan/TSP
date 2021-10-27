#include<assert.h>
#include<algorithm>
#include<map>
#include"Algorithms.h"
#include"../Structures/Graph.h"

#define INF -1

namespace Algorithm {

    Solution tabu_search(int R, const Graph& G, std::function<Solution(int, const Graph&)> f) {

        int n = G.vertices();
        matrix<int> aspiration (n, std::vector<int>(n)); // on edges
        std::queue<Solution> Q;
        std::vector<int> apparitions(n);

        std::function<int(const Path&)> fitness =
        [&] (const Path& P) {
            
            int fitness;

            for (int i = 0; i < n; ++i) {
                int j = (i+1) % n;
                fitness += G[P[i]][P[j]] + aspiration[P[i]][P[j]] - apparitions[P[i]];
                //std::cout << "(" << i << ", " << j << ")" << std::endl;
                //Solution S = {0, P};
                //std::cout << S << std::endl;
            }

            return fitness;
        };

        std::function<bool(const Solution&, const Solution&)> least_fit =
        [&fitness] (const Solution& S, const Solution& R) {
            return fitness(S.path) < fitness(R.path);
        };

        std::function<Solution(const std::vector<int>&)> least_traveled =
        [&G] (const std::vector<int>& apparitions) -> Solution {
            
            std::function<bool(int, int)> least_apparitions =
            [&apparitions] (int a, int b) {
                return apparitions[a] > apparitions[b]; // > just because
            };
            
            std::vector<int> sorted(apparitions.size());
            for (int i = 0; i < apparitions.size(); ++i)
                sorted[i] = i;
            
            Solution R = {Solution::evaluate(sorted, G), sorted};

            std::sort(sorted.begin(), sorted.end(), least_apparitions);
            R = {Solution::evaluate(sorted, G), sorted};
            return {Solution::evaluate(sorted, G), sorted};
        };

        std::function<void(Solution)> register_solution =
        [&] (Solution S) {

            const int MAX_Q_SIZE = 30;

            //TODO aspiration

            Path P = S.path;
            Q.push(S);
            for (int i = 0; i < n; ++i) {
                ++apparitions[P[i]];
                aspiration[P[i]][P[(i+1)%n]] += S.weight;
                aspiration[Q.front().path[i]][Q.front().path[(i+1)%n]] -=
                    Q.size() > MAX_Q_SIZE * Q.front().weight;
            }

            if (Q.size() > MAX_Q_SIZE)
                Q.pop();

            return;
        };

        Solution best = f(R, G);   //initial solution
        Solution actual = best;

        std::vector<Solution> SS;
        int iterations = 50000;
        while (iterations--) {
            SS = {Algorithm::two_opt(actual, G), least_traveled(apparitions)};
            actual = *std::max_element(SS.begin(), SS.end(), least_fit);
            //std::cout << actual.weight << "   " << best.weight << std::endl;
            if (actual.weight <= best.weight)
                best = actual;
            register_solution(actual);
        }

        // %N -%N+random %LV -> vector[vector[Swaps]]
        
        return best;
    }
}