import tsplib95 as tl
import os

# TODO 
# 1. WATCH OUT FOR GRAPHS STARTING IN 1
# 2. GREEDY WORST CASE 
#       BORDES EN 1 EXCEPTO ADYACENTE A NODO 0 SETTEADO EN 9999
#       DIAGONALES EN 2
#           DIAGONALES: ARISTAS NO ADYACENTES
#           ADYACENTES: NODOS CONSECUTIVOS
# 
# 3. MST WORST CASE
#       LITERALMENTE IGUAL A GREEDY
#       GENERAMOS EL ARBOL CON EL BORDE (ARISTAS DE PESO 1)
#       CUANDO VA A FORMAR EL CICLO LUEGO DE DFS, SOLO PUEDE CONECTAR
#       LA ARISTA DE PESO 999

curpath = os.path.abspath(os.curdir)

def convert_graph(filename):
    new_path = curpath + "/Test/Elib/"
    if not os.path.exists(new_path):
        os.mkdir(new_path)

    prob = tl.load("TSP/" + filename)

    if (os.path.exists(new_path + filename + ".formatted.txt")):
        return

    salida = open(new_path + filename + ".formatted.txt", 'w')

    graph = prob.get_graph()
    print(1, file=salida)
    print(graph.number_of_nodes(),graph.number_of_edges(), file=salida)
    for u,v in graph.edges:
        if u<v:
            print(u,v,graph.get_edge_data(u,v)['weight'], file=salida)
            
    return graph

def generate_all():
    graphs = os.listdir(curpath+"/TSP")
    for g in graphs:
        convert_graph(g)

generate_all()

