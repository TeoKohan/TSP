#include <iostream>
#include <chrono>
#include <functional>
#include "../Structures/Graph.h"
#include "../Algorithms/Algorithms.h"

namespace Time {
    struct ST {
        Solution result;
        double time;
    };

    ST run_function(int R, const Graph& G, TSP f);
}