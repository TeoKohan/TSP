#include"IO.h"

IO::IO(std::string path) : path(path) {}

std::vector<Graph> IO::read(const std::string& filename) {
    std::ifstream input(path + filename);
    int n, v, e, u, w;

    input >> n; // amount of graphs in file
    std::vector<Graph> test_cases;

    while (n--) {
        input >> v >> e;
        Graph G(v);
        while (e--) {
            input >> u >> v >> w;
            G[u][v] = G[v][u] = w;
        }

        test_cases.push_back(G);
    }

    return test_cases;
}
