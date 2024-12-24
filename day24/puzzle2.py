# --------------------------------- FILE OPEN -------------------------------- #
import os
inputf = open("input.txt", "r")
input = inputf.read().split("\n")
inputf.close()
# -------------------------------- PUZZLE CODE ------------------------------- #

from collections import defaultdict
import graphviz as gv

g = defaultdict(dict)
for l in input:
    try:
        i1, t, i2, _, out = l.split(' ')
        g[out] = {"type": t, "in": [i1, i2]}
    except:
        pass

g["gvw"], g["qjb"] = g["qjb"], g["gvw"]
g["z15"], g["jgc"] = g["jgc"], g["z15"]
g["z22"], g["drg"] = g["drg"], g["z22"]
g["z35"], g["jbp"] = g["jbp"], g["z35"]

def make_graph(g):

    dot = gv.Digraph(engine='dot')

    for key in g.keys():
        if g[key]["type"] == "AND":
            dot.node(key, shape='square', color='green')
        elif g[key]["type"] == "XOR":
            dot.node(key, shape='diamond', color='red')
        elif g[key]["type"] == "OR":
            dot.node(key, shape='circle', color='blue')

    for key, val in g.items():
        dot.edge(val["in"][0], key)
        dot.edge(val["in"][1], key)
    
    file_name = "tmp"

    # save and return
    # with open(file_name + ".dot", "w") as f:
    #     f.write(dot.source)
    dot.render(file_name + ".dot", format="png", cleanup=True)

make_graph(g)

res = sorted(["gvw", "qjb", "z15", "jgc", "z22", "drg", "z35", "jbp"])
print(",".join(res))