
class Node:
    def __init__(self, id):
        self.id = id
        self.color = -1

class Graph:
    def __init__(self):
        self.graph = []
        self.vertexes = []
    
    def addVertex(self, id):
        self.vertexes.append(Node(id))
        for line in self.graph:
            line.append(float('inf'))
        self.graph.append([float('inf') for i in range(len(self.graph)+1)])

    def addEdge(self, u, v, w):
        self.graph[u-1][v-1] = w
        self.graph[v-1][u-1] = w

    def show(self):
        for i in range(len(self.graph)):
            print(self.vertexes[i].id, self.vertexes[i].color)
            for j in range(len(self.graph)):
                if (self.graph[i][j] != float('inf')):
                    print("  ", self.vertexes[j].id, self.graph[i][j])


costs = [
    [],
    []
]
comunications = []
with open("input2.in") as file:
    line = file.readline()
    splitted = line.split()
    P = int(splitted[0])
    Edges = int(splitted[1])
    for i in range(P):
        comunications.append([])
        for j in range(P):
            comunications[i].append(0)
    for i in range(P):
        costs[0].append(0)
        costs[1].append(0)
    
    for k in range(P):
        line = file.readline()
        splitted = line.split()
        costs[0][k] = int(splitted[0])
        costs[1][k] = int(splitted[1])
    for l in range(Edges):
        line = file.readline()
        splitted = line.split()
        comunications[int(splitted[0])-1][int(splitted[1])-1] = int(splitted[2])
        comunications[int(splitted[1])-1][int(splitted[0])-1] = int(splitted[2])

graph = Graph()

def initializeGraph():
    graph.addVertex("x")
    graph.addVertex("y")
    for i in range(len(comunications)):
        graph.addVertex(str(i+1))
    for i in range(len(comunications)):
        for j in range(len(comunications)):
            if comunications[i][j] != 0:
                graph.addEdge(3+i, 3+j, comunications[i][j])
    for i in range(len(costs)):
        for j in range(len(costs[i])):
            if i == 0:
                graph.addEdge(1, j+3, costs[i][j])
            else:
                graph.addEdge(2, j+3, costs[i][j])

def colorGraph():
    graph.vertexes[0].color = "x"
    graph.vertexes[1].color = "y"
    for i in range(2,len(graph.vertexes)):
        if graph.graph[i][0] > graph.graph[i][1]:
            graph.vertexes[i].color = "x"
        else:
            graph.vertexes[i].color = "y"

def moveVertex():
    minCost = 1
    minVertex = -1
    for i in range(2, len(graph.vertexes)):
        moveCost = 0
        for j in range(2, len(graph.graph[i])):
            if graph.vertexes[i].color != graph.vertexes[j].color and graph.graph[i][j] != float('inf'):
                moveCost = moveCost - graph.graph[i][j]
            elif  graph.graph[i][j] != float('inf'):
                moveCost = moveCost + graph.graph[i][j]
        if graph.vertexes[i].color == "x":
            moveCost = moveCost + graph.graph[i][0] - graph.graph[i][1]
        else:
            moveCost = moveCost + graph.graph[i][1] - graph.graph[i][0]
        if moveCost < minCost:
            minCost = moveCost
            minVertex = i
    if minCost < 0:        
        return minVertex
    else:
        return -1

def getWeight():
    w = 0
    for i in range(2, len(graph.vertexes)):
        if graph.vertexes[i].color == "x":
            w = w + graph.graph[i][1]
        else:
            w = w + graph.graph[i][0]
        for j in range(i, len(graph.vertexes)):
            if graph.vertexes[i].color != graph.vertexes[j].color and graph.graph[i][j] != float('inf'):
                w = w + graph.graph[i][j]        
    return w

initializeGraph()
colorGraph()
minVertex = moveVertex()
while minVertex != -1:
    if graph.vertexes[minVertex].color == "x":
        graph.vertexes[minVertex].color = "y"
    else:
        graph.vertexes[minVertex].color = "x"
    minVertex = moveVertex()

print(getWeight())
#graph.show()


#for el in costs:
#    print(el)

#print()

#for el in comunications:
#    print(el)

