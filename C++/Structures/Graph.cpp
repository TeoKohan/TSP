#include "Graph.h"

#define INF -1

/** @return An empty Graph.*/
Graph::Graph() : V(0), N(matrix<int>(0, std::vector<int>(0, INF))) { }

/** @param V amount of vertices in graph.
 * @return An edgeless Graph of V vertices.
 */
Graph::Graph(int V) : V(V), N(matrix<int>(V, std::vector<int>(V, INF))) {
    for (int i = 0; i < V; ++i)
        N[i][i] = 0;
 }

/** @param V amount of vertices in graph.
 * @param E the edges in the graph.
 * @return The Graph defined by G(V, E).
 */
Graph::Graph(int V, std::vector<Edge> E) : V(V), N(matrix<int>(V, std::vector<int>(V, INF))) {
    for (int i = 0; i < V; ++i)
        N[i][i] = 0;
    for (const Edge& e : E) {
        N[e.from][e.to] = e.weight;
        N[e.to][e.from] = e.weight;
    }
}

/** @return The Graph's vertex count.*/
int Graph::vertices() const {
    return V;
}

/** @param i a vertex from the graph.
 * @return A read-write neighbourhood of vertex i.
 */
std::vector<int>& Graph::operator[](int i) {
    return N[i];
}

/** @param i a vertex from the graph.
 * @return A read only neighbourhood of vertex i.
 */
const std::vector<int>& Graph::operator[](int i) const {
    return N[i];
}

std::ostream& operator<< (std::ostream& os, const Graph& G) {
    std::cout << G.N.size() << 'x' << (G.N.size() > 0 ? G.N[0].size() : 0) << std::endl;
    for(int i = 0; i < G.V; ++i) {
        for(int j = 0; j < G.V; ++j)
            os << (j % G.V != 0 ? ", " : "") << (G[i][j] == INF ? "∞" : std::to_string(G[i][j]));
        os << std::endl;
    }
    return os;
}