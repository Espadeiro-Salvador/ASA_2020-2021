all: a.out randomDAG

a.out: main.cpp
	g++ -std=c++11 -O3 -Wall main.cpp -lm

randomDAG: randomDAG.cpp
	g++ -O3 -Wall -o randomDAG randomDAG.cpp -lm

clean:
	rm a.out randomDAG
