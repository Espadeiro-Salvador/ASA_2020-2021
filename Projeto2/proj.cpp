#include <cstdio>
#include <queue>
#include <stack>
#include <vector>
#include <cstdlib>

void ProcessInput(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &residualNetwork) {
    int P, E;
    if (std::scanf("%d %d", &P, &E) < 0) {
        std::exit(-1);
    }

    graph.resize(P + 2);
    residualNetwork.resize(P + 2);
    for (size_t i = 0; i < residualNetwork.size(); i++) {
        residualNetwork[i].resize(P + 2);
    }

    // Adds all processes and connects them with the processors (processing costs)
    for (int i = 0; i < P; i++) {
        int X, Y;
        if (std::scanf("%d %d", &X, &Y) < 0) {
            std::exit(-1);
        }
        residualNetwork[0][i+2] = X;
        graph[0].push_back(i+2);

        residualNetwork[i+2][1] = Y;
        graph[i+2].push_back(1);
    }

    // Adds edges between processes (communication costs)
    for (int i = 0; i < E; i++) {
        int from, to, c;

        if (std::scanf("%d %d %d", &from, &to, &c) < 0) {
            std::exit(-1);
        }

        residualNetwork[from+1][to+1] = c;
        residualNetwork[to+1][from+1] = c;
        graph[from+1].push_back(to+1);
        graph[to+1].push_back(from+1);
    }

}

void UpdateResidualNetwork(std::stack<int> &path, int &fpath, std::vector<std::vector<int>> &residualNetwork) {    
    int v = path.top();
    path.pop();

    while(v != 1) {
        residualNetwork[v][path.top()] = residualNetwork[v][path.top()] - fpath;
        residualNetwork[path.top()][v] = residualNetwork[path.top()][v] + fpath;
        v = path.top();
        path.pop();
    }
}

bool ShortestPath(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &residualNetwork, std::stack<int> &path, int &fpath) {
    std::vector<int> pi(residualNetwork.size(), -1);
    std::vector<bool> isVisited(residualNetwork.size(), false);
    std::queue<int> explorationQueue;

    // Starts exploring the source
    explorationQueue.push(0);
    isVisited[0] = true;

    while (!explorationQueue.empty()) {

        int v = explorationQueue.front();
        explorationQueue.pop();

        for (size_t i = 0; i < graph[v].size(); i++) {
            int child = graph[v][i];
            if (residualNetwork[v][child] > 0 && !isVisited[child]) {
                isVisited[child] = true;
                pi[child] = v;

                // When the sink is found, uses the parents to obtain the shortest path
                if (child == 1) {
                    int j = child;
                    path.push(j);

                    fpath = residualNetwork[pi[j]][j];
                    while (pi[j] != -1) {
                        if (residualNetwork[pi[j]][j] < fpath) {
                            fpath = residualNetwork[pi[j]][j];
                        }
                        path.push(pi[j]);
                        j = pi[j];
                    }
                    return true;
                }

                explorationQueue.push(child);
            }
        }
    }
    return false;
}

int EdmondsKarp(std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &residualNetwork) {
    // Stores the shortest path of the residual network
    std::stack<int> path;
    // Stores the maximmum flow
    int maxFlow = 0;
    while (true) {

        int fpath = 0;

        // If there is not a path form the source to the sink returns the maximmum flow
        if (!ShortestPath(graph, residualNetwork, path, fpath)) return maxFlow;
        
        UpdateResidualNetwork(path, fpath, residualNetwork);
        maxFlow = maxFlow + fpath;    
    }
}

int main() {
    std::vector<std::vector<int>> graph;
    std::vector<std::vector<int>> residualNetwork;
    ProcessInput(graph, residualNetwork);
    int minCapacity = EdmondsKarp(graph, residualNetwork);
    std::printf("%d\n", minCapacity);
    return 0;
}
