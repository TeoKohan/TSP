#include"IO.h"

IO::IO(std::string path) : path(path) {}

Graph IO::read(const std::string& filename) {
    std::ifstream input(path + filename);
    int u, v, w;
    input >> u >> v;
    Graph G(u); 
    
    while (input >> u >> v >> w)
        G[u][v] = G[v][u] = w;

    return G;
}

std::string IO::get_path(){
    return path;
}

// #include <filesystem>
// filesystem::current_path()