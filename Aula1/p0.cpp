#include <iostream>
#include <fstream>

void printHist(int** graph, int dim1, int dim2) {
    int *histogram = new int[dim1];
    int counter = 0;
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++) {
            if (graph[i][j] != 0) {
                counter++;
            }
            else {
                break;
            }
        }
        histogram[counter]++;
        counter = 0;
    }
    for (int i = 0; i < dim1; i++) {
        std::cout << histogram[i] << std::endl;
    }
}
void initializeGraph(int** graph, int maxNodes, int maxRelations) {
    for (int i = 0; i < maxNodes; i++) {
        for (int j = 0; j < maxRelations; j++) {
            graph[i][j] = 0;
        }
    }
}

void addRelation(int** graph, int index, int relation, int totalFriendships) {
    for (int i = 0; i < totalFriendships; i++) {
        if (graph[index-1][i] == 0) {
            graph[index-1][i] = relation;
            break;
        }
    }
}

int main() {
    char line[10];

    std::ifstream inputFile;
    inputFile.open("p0.in");

    inputFile.getline(line, 10);
    int numberPeople, totalFriendships;
    std::sscanf(line, "%d,%d", &numberPeople, &totalFriendships);

    int **graph1 = new int*[numberPeople];
    for(int i = 0; i < numberPeople; i++) {
        graph1[i] = new int[totalFriendships];
    }
    initializeGraph(graph1, numberPeople, totalFriendships);

    int **graph2 = new int*[numberPeople];
    for(int i = 0; i < numberPeople; i++) {
        graph2[i] = new int[totalFriendships];
    }
    initializeGraph(graph2, numberPeople, totalFriendships);
    

    for (int i = 0; i < totalFriendships; i++) {
        int person, friendOfPerson;
        inputFile.getline(line,10);
        std::sscanf(line, "%d %d", &person, &friendOfPerson);
        addRelation(graph1, person, friendOfPerson, totalFriendships);
        addRelation(graph2, friendOfPerson, person, totalFriendships);
    }
    
    std::cout << "Histograma 1" << std::endl;
    printHist(graph1, numberPeople, totalFriendships);

    std::cout << "Histograma 2" << std::endl;
    printHist(graph2, numberPeople, totalFriendships);

    return 0;
}