#include "Time.h"
namespace Time {
    ST run_function(int R, const Graph& G, TSP f) {
        Solution S;
        auto start = std::chrono::steady_clock::now();
        S = f(R, G);
        auto end = std::chrono::steady_clock::now();
        double total_time = std::chrono::duration<double, std::milli>(end - start).count();
        return {S, total_time};
    }
}