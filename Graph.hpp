// Graph.hpp
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <cstdlib>

using namespace std;

class Graph {
public:
    Graph(int vertices);
    void addEdge(size_t u, size_t v);
    bool isEulerian();
    void findEulerCircuit();
    void printGraph();

private:
    int vertices;
    vector<vector<int>> adjList;
    bool isConnected();
    void DFS(size_t v, vector<bool>& visited);
    int findStartVertex();
};

#endif 