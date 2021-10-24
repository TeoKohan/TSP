/** Prim on a connected graph. 
 * Computes a Tree whith the minimum total weight.
 * @param  R Root of the Tree.
 * @param  G Graph to construct the Tree on.
 * @return MST of the given graph.
 */
Tree Tree::Prim(int R, const Graph& G) {
    Tree T(R, G.vertices());
    T.L[R] = 0;
    T.V = {R};

    //Returns the minimum weight edge that connects V and V(G) / V
    std::function<Edge*(const std::set<int>&)> min_bridge;
    min_bridge = [&G](const std::set<int>& V) {
        Edge* min = nullptr; 
        for (int v : V)
            for (const Edge& e : G.neighbour(v))
                if (!V.count(e.to))
                    if (min == nullptr)
                        min = new Edge(e);
                    else if (e.length < min->length)
                        *min = e;
        return min;
    };
    
    for (size_t i = 1; i < G.vertices().size(); ++i) {
        Edge* e = min_bridge(T.V);
        if (!e) 
            throw std::domain_error("Graph is not connected.");
        
        T.V.insert(e->to);
        T.E.insert(*e);
        T.P[e->to] = e->from;
        T.N[e->to].insert(*e);
        T.L[e->to] = T.L[e->from] + e->length;
        delete(e);
    }
    
    return T;
}