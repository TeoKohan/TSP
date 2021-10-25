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
    
    Solution center() {
        int i = 0;
        while (path[i] != 0)
            i++;
        Path P;
        P.reserve(path.size());
        P.insert(P.end(), path.cbegin()+i, path.cend());     // 0 to end
        P.insert(P.end(), path.cbegin(), path.cbegin()+i);   // begin to 0
        return {weight, P};
    }
}; 

namespace Algorithm {
    Solution greedy(const Graph& G);
    Solution greedy_all(const Graph& G);

    Solution MST(int R, const Graph& G);
    Solution MST_all(const Graph& G);
}

#endif//ALGO_H