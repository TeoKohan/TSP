#ifndef TREE_H
#define TREE_H

#include"Graph.h"
#include<iostream>
#include<functional>
#include<queue>
#include<stack>
#include<vector>

/**A data structure holding a Tree
 * you can expect every vertex to have exactly one parent (excluding the root).
 */
class Tree {
    friend std::ostream& operator << (std::ostream& os, const Tree& T);

    public:
        static Tree BFS  (int R, const Graph& G);
        static Tree DFS  (int R, const Graph& G);
        static Tree Prim (int R, const Graph& G);

        int root() const;
        int vertices() const;
        int parent(int v) const;
        int total_weight(const Graph& G) const;
        std::vector<int> children(int v) const;

    private:
        Tree(int R, int V);
        int R;                              //Root
        int V;                              //Vertices
        std::vector<int> P;                 //Parent
        std::vector<std::vector<int>> C;    //Children
};

#endif //TREE_H