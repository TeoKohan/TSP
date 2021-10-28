import os
import random
import numpy as np

os.chdir('..')
curpath = os.path.abspath(os.curdir)

def save_instance(function, g_range):
    new_path = curpath + f"/Test/Python/"
    if not os.path.exists(new_path):
        os.mkdir(new_path)
    with open(new_path + f"/{function.__name__}-{g_range[0]}-{g_range[-1]}.txt", "w") as f:
        print(len(g_range), file=f, end="\n") # amount of graphs in file
        for g in [function(i) for i in g_range]:
            for e in g:
                print(e, file=f, end="\n")

def com_graph_rand(k, floor = 0, ceil = 100):
        G = [f"{i} {j} {random.randint(floor, ceil)}" for i in range(k) for j in range(i + 1, k)]
        G.insert(0, f"{k} {k*(k-1)//2}")
        return G
  
def com_graph_normal_dist(k, mu, sigma):
    G = [f"{i} {j} {int(abs(np.random.normal(mu, sigma))+1)}" for i in range(k) for j in range(i + 1, k)]
    G.insert(0, f"{k} {k*(k-1)//2}")
    return G

def com_graph_limited_values(k, values):
    G = [f"{i} {j} {random.choice(values)}" for i in range(k) for j in range(i + 1, k)]
    G.insert(0, f"{k} {k*(k-1)//2}")
    return G

save_instance(com_graph_rand, range(100, 1001, 100))
#complete_graph_weight_1(11)

