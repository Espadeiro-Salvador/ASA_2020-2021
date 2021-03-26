class Node:
        def __init__(self):
            self.source = True
            self.visited = False
            self.maxPath = 1

class Graph:
    def __init__(self, V):
        self.graph = [[] for i in range(V)]
        self.vertexes = [Node() for i in range(1,V+1)]

    def addEdge(self, u, v):
        self.graph[u-1].append(v-1)
        self.vertexes[v-1].source = False

    def getTopologicalOrder(self):
        topologicalOrder = []
        for i in range(len(self.vertexes)):
            if not self.vertexes[i].visited:
                topologicalOrder = self.explore(i) + topologicalOrder
        return topologicalOrder
    
    def explore(self, v):
        stack = [v]
        topologicalOrder = []
        while stack:
            vi = stack[-1]

            self.vertexes[vi].visited = True

            closed = True
            for n in self.graph[vi]:
                if not self.vertexes[n].visited:
                    closed = False
                    stack.append(n)

            if closed:
                stack.pop()
                topologicalOrder = [vi] + topologicalOrder
        
        return topologicalOrder
    
# Process input
file = open("testes/enunciado.in", "r")
lines = file.read().splitlines()
settings = lines[0].split()
V = int(settings[0])
E = int(settings[1])

# Initialize graph
g = Graph(V)
for i in range(E):
    splitted = lines[i+1].split()
    g.addEdge(int(splitted[0]), int(splitted[1]))


maxPath = 1
numberSources = 0
for el in g.getTopologicalOrder():
    if g.vertexes[el].source == True:
        numberSources += 1
    for link in g.graph[el]:
        if g.vertexes[el].maxPath + 1 > g.vertexes[link].maxPath:
            g.vertexes[link].maxPath = g.vertexes[el].maxPath + 1
            if g.vertexes[link].maxPath > maxPath:
                maxPath = g.vertexes[link].maxPath
    
print(numberSources, maxPath)