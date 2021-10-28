#include"IO.h"

#define INF -1

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

void test_output(const std::string& output_filename, const std::vector<Graph>& GS, const std::vector<IO::TSPName>& fs) {
    std::ofstream results;
    
    results.open(output_filename + ".csv");
    results << "algorithm,size,weight,time" << std::endl;

    for (const auto& G : GS) {
        int min = INF;
        std::string min_n = fs[0].name;

        for (const auto& f : fs) {
            auto ST = Time::run_function(0, G, f.algorithm);
            if (min == INF || ST.result.weight < min) {
                min = ST.result.weight;
                min_n = f.name;
            }            
            results << f.name << "," << G.vertices() << "," << ST.result.weight << "," << ST.time << std::endl;

        }
    }

    results.close();
}

