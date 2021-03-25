#include <iostream>
#include <vector>

class Graph {
    int _V;
    int _E;
    std::vector<int>* _adj;

public:
    Graph() {}

    void initGraph(int V, int E) {
        _V = V;
        _E = E;
        _adj = new std::vector<int>[V];
    }

    void addEdge(int from, int to) {
        _adj[from-1].push_back(to-1);
    }

    void printGraph(){
        for (int i = 0; i < _V; i++) {
            std::cout << i + 1 << std::endl;
            for (int j = 0; j < _adj[i].size(); j++) {
                std::cout << "  " << _adj[i][j] + 1 << std::endl;
            }
        }
    }
};

void processInput(Graph &graph) {
    int numberVertexs, numberEdges;
    scanf("%d %d", &numberVertexs, &numberEdges);
    graph.initGraph(numberVertexs, numberEdges);

    for (int i = 0; i < numberEdges; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        graph.addEdge(from, to);
    }
}

int main() {
    Graph graph;
    processInput(graph);
    std::cout << std::endl;
    graph.printGraph();
    return 0;
}