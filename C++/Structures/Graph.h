#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>
#include<vector>
#include<set>

typedef std::vector<std::vector<int>> matrix;
#define matrix(n, m, v) matrix(n, std::vector<int>(m, v))

/**A data structure holding an Edge, that is a straight line between two points.
 */
struct Edge {
    //origin of edge
    int from;
    //length of edge
    int weight;
    //destination of edge
    int to;

    /**Edge starting at from, ending at to, with length of length.
    */
    Edge(int from, int weight, int to) : from(from), weight(weight), to(to) {}
};


/**A data structure holding a Graph
 * composed of vertices, edges and an adjacency list or neighbourhood.
 */
class Graph {
    public:
        Graph(int V);
        Graph(int V, std::vector<Edge> E);

        int vertices() const;
        std::vector<int>& operator[](int i);
        const std::vector<int>& operator[](int i) const;
        std::ostream& operator << (std::ostream& os);
    private:
        int V;
        matrix N;
};

#endif//GRAPH_H