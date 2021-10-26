import os
import random
import numpy as np

os.chdir('..')
curpath = os.path.abspath(os.curdir)

def save_instance(dataset, instance_name, edges, n):
    new_path = curpath + f"/Test/Python/{dataset}"
    if not os.path.exists(new_path):
        os.mkdir(new_path)
    with open(new_path + f"/{instance_name}.txt", "w") as f:
        print(n, len(edges), file=f)
        for e in edges:
            print(e, file=f, end="\n")


def complete_graph_weight_1(k):
    """ Generates k i-complete graphs (i from 2 to k) with all it's edge weights set to 1.

    Arguments: \n
    int k -- a number indicating the amount of vertices.
    """ 
    for size in range(2, k+1):
        edges = [f"{i} {j} 1" for i in range(size) for j in range(i + 1, size)]
        save_instance("complete-graph-weight-1", f"WEIGHT-1-n-{size}", edges, size)

def complete_graph_random_weight(k, floor, ceil):
    """ Generates k i-complete graphs (i from 2 to k) with random edge weights, between floor and ceil.

    Arguments: \n
    int k -- a number indicating the amount of vertices. \n
    int floor -- a number indicating the minimun possible weight and edge can have.\n
    int ceil -- a number indicating the maximum possible weight and edge can have. \n
    """ 

    for size in range(1, k+1):
        edges = [f"{i} {j} {random.randint(floor, ceil)}" for i in range(size) for j in range(i + 1, size)]
        save_instance("complete-graph-random-weight", f"WEIGHT-{floor}-to-{ceil}-n-{size}", edges, size)

def complete_graph_normal_dist(k, mu, sigma):
    """ Generates k i-complete graphs (i from 2 to k) with normally-distributed {N(mu, sigma)} edge weights.

    Arguments: \n
    int k -- a number indicating the amount of vertices. \n
    int mu -- a number indicating the mean of the normal distribution.\n
    int sigma -- a number indicating the variance of the normal distribution. \n
    """ 

    for size in range(2, k+1):
        edges = [f"{i} {j} {int(abs(np.random.normal(mu, sigma))+1)}" for i in range(size) for j in range(i + 1, size)]
        save_instance("complete-graph-normal-dist", f"WEIGHT-mu{mu}-sigma-{sigma}-n-{size}", edges, size)

def complete_graph_limited_values(k, values):
    """ Generates k i-complete graphs (i from 2 to k) with edge weights randomly chosen from values, a given list.

    Arguments: \n
    int k -- a number indicating the amount of vertices. \n
    list(int) values -- a list containing the possible values the edge weights can have.\n
    """ 

    for size in range(2, k+1):
        edges = [f"{i} {j} {random.choice(values)}" for i in range(size) for j in range(i + 1, size)]
        save_instance("complete-graph-limited-values", f"WEIGHT-limited-n-{size}", edges, size)


complete_graph_random_weight(200, 1, 1000)

