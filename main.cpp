#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "Graph.hpp"

using namespace std;

void printUsage() {
    cout << "Usage: ./graph -v <vertices> -e <edges> -s <seed>" << endl;
}

int main(int argc, char* argv[]) {
    int vertices = 0, edges = 0, seed = time(0);
    int opt;
    while ((opt = getopt(argc, argv, "v:e:s:")) != -1) {
        switch (opt) {
            case 'v':
                vertices = atoi(optarg);
                break;
            case 'e':
                edges = atoi(optarg);
                break;
            case 's':
                seed = atoi(optarg);
                break;
            default:
                printUsage();
                return EXIT_FAILURE;
        }
    }

    if (vertices <= 0 || edges <= 0) {
        printUsage();
        return EXIT_FAILURE;
    }

    srand((unsigned int)seed);
    Graph graph(vertices);

    for (size_t i = 0; i < edges; i++) {
        size_t u = (size_t)(rand() % vertices);
        size_t v = (size_t)(rand() % vertices);
        graph.addEdge(u, v);
    }

    graph.printGraph();
    graph.findEulerCircuit();

    return 0;
}
