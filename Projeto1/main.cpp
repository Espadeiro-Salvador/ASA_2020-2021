#include <cstdio>
#include <vector>

struct Node {
    bool isSource = true;
    bool visited = false;
};

int V, E;
std::vector<std::vector<int>> graph;
std::vector<int> topological;
std::vector<Node> vertexes;

void processInput() {
    std::scanf("%d %d", &V, &E);
    graph = std::vector<std::vector<int>>(V, std::vector<int>());
    vertexes = std::vector<Node>(V);

    for (int i = 0; i < E; i++) {
        int from, to;
        std::scanf("%d %d", &from, &to);
        graph[from - 1].push_back(to);
        vertexes[to - 1].isSource = false;
    }
}

int main() {
    processInput();
    return 0;
}