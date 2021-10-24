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

std::ostream& operator<< (std::ostream& os, const Tree& T) {
    std::cout << "v: " << T.V << ", r: " << T.R << std::endl;
    for(int i = 0; i < T.vertices(); ++i) {
        std::cout << "v: " << i;
        std::cout << " p: " << (T.parent(i) == -1 ? "root" : std::to_string(T.parent(i))) << " c: ";
        for(int j : T.children(i))
            std::cout << j << ", ";
        std::cout << "end" << std::endl;
    }

    return os;
}