#include <cstdio>
#include <vector>

int people = 0;
int relations = 0;

void printHistograma(std::vector<int> *graph, int hist) {
    int histograma[people] = {0};
    for (int i = 0; i < people; ++i) {
        histograma[graph[i].size()]++;
    }

    std::printf("Histograma %d\n", hist);
    for (int i = 0; i < people; i++) {
        std::printf("%d\n", histograma[i]);
    }
}

int main() {
    std::scanf("%d,%d", &people, &relations);
    std::vector<int> graph1[people];
    std::vector<int> graph2[people];

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
