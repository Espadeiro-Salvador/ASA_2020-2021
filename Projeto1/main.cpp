#include <cstdio>
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
        for (int i = 0; i < graph[v].size(); i++) {
            if (!vertexes[graph[v][i]].visited) {
                closed = false;
                stack.push(graph[v][i]);
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
    std::scanf("%d %d", &V, &E);
    graph = std::vector<std::vector<int>>(V, std::vector<int>());
    vertexes = std::vector<Node>(V);

    for (int i = 0; i < E; i++) {
        int from, to;
        std::scanf("%d %d", &from, &to);
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
    for (auto i : topological) {
        if (vertexes[i].isSource) {
            numberSources++;
        }

        for (int j = 0; j < graph[i].size(); j++) {
            if (vertexes[i].maxPath + 1 > vertexes[graph[i][j]].maxPath) {
                vertexes[graph[i][j]].maxPath = vertexes[i].maxPath + 1;
                if (maxPath < vertexes[graph[i][j]].maxPath) {
                    maxPath = vertexes[graph[i][j]].maxPath;
                }
            }
        }
    }

    std::printf("%d %d\n", numberSources, maxPath);

    return 0;
}