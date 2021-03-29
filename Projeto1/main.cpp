#include <cstdio>
#include <cstdlib>
#include <vector>
#include <list>
#include <stack>

struct Node {
    bool isSource = true;
    bool visited = false;
    int maxPath = 1;
};

int V, E;
std::vector<std::vector<int>> graph;
std::list<int> topological;
std::vector<Node> vertexes;

/* O(V+E) */
void exploreFromVertex(int vertex) {
    std::stack<int> stack;
    stack.push(vertex);

    while (!stack.empty()) {
        int v = stack.top();
        vertexes[v].visited = true;
        
        bool closed = true;
        for (auto &child : graph[v]) {
            if (!vertexes[child].visited) {
                closed = false;
                stack.push(child);
            }
        }
        
        if (closed) {
            stack.pop();
            topological.push_front(v);
        }
    }
}

/* Θ(V+E) */
void getTopologicalOrder() {
    topological = std::list<int>();
    for (int i = 0; i < V; i++) {
        if (!vertexes[i].visited) {
            exploreFromVertex(i);
        }
    }
}

/* Θ(E) ou Θ(V+E) */
void processInput() {
    if (std::scanf("%d %d", &V, &E) < 0) {
        std::exit(-1);
    }
    
    graph = std::vector<std::vector<int>>(V, std::vector<int>());
    vertexes = std::vector<Node>(V);

    for (int i = 0; i < E; i++) {
        int from, to;
        if (std::scanf("%d %d", &from, &to) < 0) {
            std::exit(-1);
        }

        graph[from - 1].push_back(to - 1);
        vertexes[to - 1].isSource = false;
    }
}

int main() {
    processInput();
    getTopologicalOrder();

    int maxPath = 1;
    int numberSources = 0;
    
    // O(V+E)
    for (auto &vertex : topological) {
        if (vertexes[vertex].isSource) {
            numberSources++;
        }

        for (auto &child : graph[vertex]) {
            if (vertexes[vertex].maxPath + 1 > vertexes[child].maxPath) {
                vertexes[child].maxPath = vertexes[vertex].maxPath + 1;
                if (maxPath < vertexes[child].maxPath) {
                    maxPath = vertexes[child].maxPath;
                }
            }
        }
    }

    std::printf("%d %d\n", numberSources, maxPath);

    return 0;
}