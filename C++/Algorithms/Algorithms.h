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

    bool operator < (const Solution& rhs) const {
        return weight < rhs.weight ||
               (weight == rhs.weight && path.size() <= rhs.path.size());
    }
    
    int reevaluate (const Graph& G) {
        int sum = 0;
        for (int i = 0; i < path.size(); ++i)
            sum += G[path[i]][path[(i+1) % path.size()]];
        return sum;
    }

    bool repeats () {
        std::set<int> A(path.begin(), path.end());
        return A.size() != path.size();
    }

    void center(int k = 0) {
        int i = 0;
        while (path[i] != k)
            i++;
        Path P;
        P.reserve(path.size());
        P.insert(P.end(), path.cbegin()+i, path.cend());     //k to end
        P.insert(P.end(), path.cbegin(), path.cbegin()+i);   //begin to k
        path = P;
    }
}; 

namespace Algorithm {
    Solution greedy(int R, const Graph& G);
    Solution greedy_all(const Graph& G);

    Solution MST(int R, const Graph& G);
    Solution MST_all(const Graph& G);

    Solution local_search(int R, const Graph& G);
}

#endif//ALGO_H