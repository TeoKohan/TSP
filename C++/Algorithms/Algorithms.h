#ifndef ALGO_H
#define ALGO_H

#include <functional>
#include <iostream>
#include <vector>
#include "../Structures/Graph.h"
#include "../Structures/Tree.h"

typedef std::vector<int> Path;

struct Solution {

    friend std::ostream& operator << (std::ostream& os, const Solution& S) {
        os << S.weight << " - ";
        for (int i = 0; i < S.path.size(); ++i)
            os << (i == 0 ? "" : " ") << S.path[i];
        return os;
    }
    
    int weight;
    Path path;

    Solution() : weight(0), path(Path()) {}
    Solution(int weight, Path path) : weight(weight), path(path) {}

    Solution& operator = (const Solution& rhs) {
        weight = rhs.weight;
        path = rhs.path;
        return *this;
    }

    bool operator < (const Solution& rhs) const {
        return weight < rhs.weight ||
               (weight == rhs.weight && path.size() <= rhs.path.size());
    }

    bool operator == (const Solution& rhs) const {
        return weight == rhs.weight && path == rhs.path;
    }
    
    static int evaluate (const Path& P, const Graph& G) {
        int sum = 0;
        for (int i = 0; i < P.size(); ++i)
            sum += G[P[i]][P[(i+1) % P.size()]];
        return sum;
    }

    void center(int k = 0) {
        int i = 0;
        while (path[i] != k)
            i++;
        Path P;
        P.reserve(path.size());
        P.insert(P.end(), path.cbegin()+i, path.cend());     //k     -> end
        P.insert(P.end(), path.cbegin(), path.cbegin()+i);   //begin -> k
        path = P;
    }
};

struct Swap {
    Edge before;
    Edge after;

    bool operator == (const Swap& rhs) const {
        return (before == rhs.before && after == rhs.after) ||
               (before == rhs.after  && after == rhs.before);
    }

    bool operator < (const Swap& rhs) const {
        return before < rhs.before || 
            (before == rhs.before && after < rhs.after);
    }
};

struct SwapSolution {
    Swap swap;
    Solution solution;

    bool operator < (const SwapSolution& rhs) const {
        return solution < rhs.solution;
    }
};

typedef std::function<Solution(int, const Graph&)> TSP;

namespace Algorithm {
    Solution greedy(int R, const Graph& G);
    Solution greedy_all(int R, const Graph& G);

    Solution MST(int R, const Graph& G);
    Solution MST_all(int R, const Graph& G);

    Solution& two_opt(Solution& S, const Graph& G);

    Solution local_search(int R, const Graph& G);
    Solution tabu_search(int R, const Graph& G);
}

#endif//ALGO_H