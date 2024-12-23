# --------------------------------- FILE OPEN -------------------------------- #
import os
inputf = open("input.txt", "r")
input = inputf.read().split("\n")
inputf.close()
# -------------------------------- PUZZLE CODE ------------------------------- #

from collections import defaultdict
import networkx as nx

G = nx.Graph()
for l in input:
    ll, lr = l.split('-')
    G.add_edge(ll, lr)
    
c = nx.algorithms.max_weight_clique(G, weight=None)
c[0].sort()
print(",".join(c[0]))
