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

os.chdir('..')
curpath = os.path.abspath(os.curdir)

new_path = curpath + "/Test/Elib/"
if not os.path.exists(new_path):
    os.mkdir(new_path)

def convert_graph(filename):

    prob = tl.load(new_path + filename)

    if "formatted" in filename:
       return

    salida = open(new_path + filename + ".formatted", 'w')

    graph = prob.get_graph()
    print(1, file=salida)
    print(graph.number_of_nodes(),graph.number_of_edges(), file=salida)
    
    no_zero = not 0 in graph.nodes

    for u,v in graph.edges:
        if u<v:
            print(u-no_zero,v-no_zero,graph.get_edge_data(u,v)['weight'], file=salida)
            
    return graph

def generate_all():
    graphs = os.listdir(new_path)
    for g in graphs:
        convert_graph(g)

generate_all()

