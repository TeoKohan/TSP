#include"Tree.h"
#include<vector>

#define BOT -1

/** @param R Tree root.
 * @param V Tree vertex count.
 * @return An edgeless Tree of V vertices.
 */
Tree::Tree(int R, int V) : 
R(R), V(V), P(std::vector<int>(V, BOT)), C(std::vector<std::vector<int>>(V)) { }

/** @return The root of the tree.
 */
int Tree::root() const {
    return R;
}

/** @return The amount of vertices in the tree.  
 */
int Tree::vertices() const {
    return V;
}

/** @param v a vertex in the Tree.
 * @return The parent of vertex v.
 */
int Tree::parent(int v) const {
    return P[v];
}

/** @param v a vertex in the Tree.
 * @return A vector containing the children of vertex v.
 */
std::vector<int> Tree::children(int v) const {
    return C[v];
}

/** @param G a subyacent Graph G of the Tree.
 * @return Returns the sum of the weights in G of all the edges in the tree.  
 */
int Tree::total_weight(const Graph& G) const {
    int weight = 0;
    std::queue<int> Q;
    Q.push(R);

    while (!Q.empty()) {
        for (int c : C[Q.front()]) {
            weight += G[Q.front()][c];
            Q.push(c);
        }
        Q.pop();
    }

    return weight;
}

#define ARROW " --> "
#define AND " & "

std::ostream& operator<< (std::ostream& os, const Tree& T) {
    std::cout << "v: " << T.V << ", r: " << T.R << std::endl;
    for(int i = 0; i < T.vertices(); ++i) {
        if (!T.children(i).size())
            continue;
        std::cout << i << ARROW;
        for(int j = 0; j < T.children(i).size(); ++j)
            std::cout << (j == 0 ? "" : AND) << T.children(i)[j];
        std::cout << std::endl;
    }

    return os;
}