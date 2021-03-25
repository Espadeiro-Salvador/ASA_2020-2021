#include <iostream>
#include <fstream>

// 0 1 1
// 0 0 0
// 0 0 0

// 2 0 1

void printHist(int** graph, int numberOfPeople) {
    int histogram[numberOfPeople] = {0};
    int counter = 0;

    for (int i = 0; i < numberOfPeople; i++) {
        for (int j = 0; j < numberOfPeople; j++) {
            if (i == j) continue;
            else if (graph[i][j] != 0) {
                counter++;
            }
        }

        histogram[counter]++;
        counter = 0;
    }

    for (int i = 0; i < numberOfPeople; i++) {
        std::cout << histogram[i] << std::endl;
    }
}

void printHist2(int** graph, int numberOfPeople) {
    int histogram[numberOfPeople] = {0};
    int counter = 0;

    for (int i = 0; i < numberOfPeople; i++) {
        for (int j = 0; j < numberOfPeople; j++) {
            if (i == j) continue;
            else if (graph[j][i] != 0) {
                counter++;
            }
        }

        histogram[counter]++;
        counter = 0;
    }

    for (int i = 0; i < numberOfPeople; i++) {
        std::cout << histogram[i] << std::endl;
    }
}

void initializeGraph(int** graph, int maxNodes) {
    for (int i = 0; i < maxNodes; i++) {
        for (int j = 0; j < maxNodes; j++) {
            graph[i][j] = 0;
        }
    }
}

void addRelation(int** graph, int index, int relation, int totalFriendships) {
    graph[index - 1][relation - 1] = 1;
}

int main() {
    char line[10];

    std::ifstream inputFile;
    inputFile.open("p0.in");

    inputFile.getline(line, 10);
    int numberPeople, totalFriendships;
    std::sscanf(line, "%d,%d", &numberPeople, &totalFriendships);

    int **graph = new int*[numberPeople];
    for(int i = 0; i < numberPeople; i++) {
        graph[i] = new int[totalFriendships];
    }
    initializeGraph(graph, numberPeople);

    for (int i = 0; i < totalFriendships; i++) {
        int person, friendOfPerson;
        inputFile.getline(line,10);
        std::sscanf(line, "%d %d", &person, &friendOfPerson);
        addRelation(graph, person, friendOfPerson, totalFriendships);
    }
    
    std::cout << "Histograma 1" << std::endl;
    printHist(graph, numberPeople);

    std::cout << "Histograma 2" << std::endl;
    printHist2(graph, numberPeople);

    return 0;
}