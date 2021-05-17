from dataclasses import dataclass

@dataclass
class Node:
    id: int
    color: str = "x"
    visited: bool = False
    cost: int = 0


class Graph:
    def __init__(self):
        self.graph = []
        self.vertexes = []

    def addVertex(self, vertex):
        self.vertexes.append(vertex)

        for r in self.graph:
            r.append(0)

        row = []
        for _ in self.vertexes:
            row.append(0)
        self.graph.append(row)

    def addEdge(self, v1, v2, cost):
        self.graph[v1][v2] = cost
        self.graph[v2][v1] = cost

    def show(self):
        for i in range(len(self.graph)):
            print(self.vertexes[i].id, self.vertexes[i].color)
            for j in range(len(self.graph)):
                if self.graph[i][j] > 0:
                    print("  ", self.vertexes[j].id, self.graph[i][j])

    def explore(self, v):
        stack = [v]

        while stack:
            vi = stack[-1]

            self.vertexes[vi].visited = True
            closed = True

            for i, n in enumerate(self.graph[vi]):
                if n > 0 and not self.vertexes[i].visited:
                    closed = False
                    stack.append(i)

                    if self.vertexes[vi].color == self.vertexes[i].color:
                        self.vertexes[vi].cost += n
                        self.vertexes[i].cost += n
                    else:
                        self.vertexes[vi].cost -= n
                        self.vertexes[i].cost -= n
            
            if closed:
                stack.pop()
            else:
                if self.vertexes[vi].color == 'y':
                    self.vertexes[vi].cost += y_costs[vi] - x_costs[vi]
                else:
                    self.vertexes[vi].cost += x_costs[vi] - y_costs[vi]

    def calculateCosts(self):
        for v in self.vertexes:
            self.vertexes[v.id].cost = 0
        
        for v in self.vertexes:
            if not v.visited:
                self.explore(v.id)


graph = Graph()
x_costs = []
y_costs = []

with open("input2.in") as file:
    line = file.readline()
    splitted = line.split()
    P = int(splitted[0])
    Edges = int(splitted[1])

    for i in range(P):
        v = Node(i)
        graph.addVertex(v)
        x_cost, y_cost = [int(cost) for cost in file.readline().split()]
        x_costs.append(x_cost)
        y_costs.append(y_cost)
    
    for _ in range(Edges):
        v1, v2, cost = [int(cost) for cost in file.readline().split()]
        graph.addEdge(v1 - 1, v2 - 1, cost)

graph.show()
graph.calculateCosts()

for v in graph.vertexes:
    print(v.cost)
    if v.cost < 0:
        if v.color == "x":
            graph.vertexes[v.id].color = "y"
        else:
            graph.vertexes[v.id].color = "x"

print()
graph.calculateCosts()

for v in graph.vertexes:
    print(v.cost)
