#include <cstdio>
#include <vector>
#include <map>

void printHistograma(std::vector<std::vector<int>> graph, int hist) {
    std::map<int, int> histograma;
    int max = 0;
    for (int i = 0; i < graph.size(); ++i) {
        int n = graph[i].size();
        if (n > max) max = n;
        histograma[n]++;
    }
    
    std::printf("Histograma %d\n", hist);
    for (int i = 0; i < max; i++) {
        std::printf("%d\n", histograma[i]);
    }
}

int main() {
    int people = 0;
    int relations = 0;

    std::scanf("%d,%d", &people, &relations);
    std::vector<std::vector<int>> graph1(people);
    std::vector<std::vector<int>> graph2(people);

    for (int i = 0; i < relations; ++i) {
        int p1, p2;
        std::scanf("%d %d", &p1, &p2);
        graph1[p1 - 1].push_back(p2);
        graph2[p2 - 1].push_back(p1);
    }

    printHistograma(graph1, 1);
    printHistograma(graph2, 2);

    return 0;
}
