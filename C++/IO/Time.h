#include <iostream>
#include <chrono>
#include <functional>
#include "../Structures/Graph.h"
#include "../Algorithms/Algorithms.h"

#ifndef C_TIME_H
#define C_TIME_H

namespace Time {
    struct ST {
        Solution result;
        double time;
    };

    ST run_function(int R, const Graph& G, TSP f);
}

#endif//C_TIME_H