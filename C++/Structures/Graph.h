#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<set>

template<class T>
using matrix = std::vector<std::vector<T>>;

/**A data structure holding an Edge, that is a straight line between two points.*/
struct Edge {
    int from;   //origin of edge
    int weight; //length of edge
    int to;     //destination of edge

    /**Edge starting at from, ending at to, with weight of 1.*/
    Edge(int from, int to) : from(from), weight(1), to(to) {}

    /**Edge starting at from, ending at to, with weight of weight.*/
    Edge(int from, int weight, int to) : from(from), weight(weight), to(to) {}

    void swap () {
        std::swap(from, to);
    }

    bool operator == (const Edge& rhs) const {
        return  from == rhs.from &&
                weight == rhs.weight &&
                to == rhs.to;
    }

    bool operator != (const Edge& rhs) const {
        return  !(*this == rhs);
    }

    bool operator < (const Edge& rhs) const {
        return  from < rhs.from ||
            (from == rhs.from && to < rhs.to);
    }
};


/**A data structure holding a Graph described by an adjacency matrix.*/
class Graph {
    friend std::ostream& operator << (std::ostream& os, const Graph& G);

    public:
        Graph();
        Graph(int V);
        Graph(int V, std::vector<Edge> E);

        int vertices() const;
        std::vector<int>& operator[](int i);
        const std::vector<int>& operator[](int i) const;
        
    private:
        int V;
        matrix<int> N;
};

#endif//GRAPH_H