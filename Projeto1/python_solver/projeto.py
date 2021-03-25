# Python3 program to print DFS traversal
# from a given given graph
from collections import defaultdict
 
# This class represents a directed graph using
# adjacency list representation
 
class Node:
    def __init__(self, ident):
        self.source = True
        self.visited = False
        

class Graph:
    # Constructor
    def __init__(self, V):
 
        # default dictionary to store graph
        self.graph = defaultdict(list)
        self.topological_order = []
        self.vertexs = [Node(i) for i in range(1,V+1)]

    # function to add an edge to graph
    def addEdge(self, u, v):
        self.graph[u].append(v)
        self.vertexs[v-1].source = False
 
    # A function used by DFS
    # def explore(self, v, stack):
    #     self.vertexs[v-1].visited = True
    
    #     for neighbour in self.graph[v]:
    #         if not self.vertexs[neighbour-1].visited:
    #             self.DFSUtil(neighbour)
    #     self.topological_order = [v] + self.topological_order
 
    # def DFS(self, v):
    #     stack = []
    #     for i in range(len(self.vertexs)):
    #         if not self.vertexs[i+1].visited:
    #             for child in self.vertexs[i+1]:
    #                 stack = [child] + stack
    #             self.explore

    def explore(self, v):
        stack = [v]

        while stack:
            vi = stack[-1]

            self.vertexs[vi - 1].visited = True

            closed = True
            for n in self.graph[vi]:
                if not self.vertexs[n - 1].visited:
                    closed = False
                    stack.append(n)

            if closed:
                stack.pop()
                self.topological_order = [vi] + self.topological_order
 
    def DFS(self):
        for i in range(len(self.vertexs)):
            if not self.vertexs[i].visited:
                self.explore(i + 1)
    
 
# Driver code
file = open("graph.in", "r")
lines = file.read().splitlines()
settings = lines[0].split()
V = int(settings[0])
E = int(settings[1])

 
# Create a graph given
# in the above diagram
g = Graph(V)
for i in range(E):
    splitted = lines[i+1].split()
    g.addEdge(int(splitted[0]), int(splitted[1]))


# for i in range(len(g.vertexs)):
#     if not g.vertexs[i].visited:
#         g.DFS(i+1)
g.DFS()

mp = {}
for el in g.topological_order:
    mp[el] = 1
for el in g.topological_order:
    for link in g.graph[el]:
        if mp[el] + 1 > mp[link]:
            mp[link] = mp[el] + 1
    
count = 0
for el in g.vertexs:
    if el.source == True:
        count += 1

print(count, max(mp.values()))

 
# This code is contributed by Neelam Yadav