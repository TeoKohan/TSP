import tsplib95 as tl

def generar_instancia(archivo_entrada, archivo_salida):
    prob = tl.load(archivo_entrada)
    salida = open(archivo_salida,'w')

    grafo = prob.get_graph()

    print(grafo.number_of_nodes(),grafo.number_of_edges(), file=salida)
    for u,v in grafo.edges:
        if u<v:
            print(u,v,grafo.get_edge_data(u,v)['weight'], file=salida)
            
    return grafo

grafo = generar_instancia(archivo_entrada='./berlin52.tsp.txt' , archivo_salida='./berlin52.txt')