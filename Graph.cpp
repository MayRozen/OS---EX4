// Graph.cpp
#include "Graph.hpp"

Graph::Graph(int myVertices) {
    vertices = myVertices;
    adjList.resize((size_t)myVertices);
}

void Graph::addEdge(size_t u, size_t v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u); // Since the graph is undirected
}

bool Graph::isConnected() {
    vector<bool> visited((size_t)vertices, false);
    size_t i;

    // Find a vertex with a non-zero degree
    for (i = 0; i < vertices; i++) {
        if (!adjList[i].empty()) {
            break;
        }
    }

    // If no edges in the graph, return true
    if (i == vertices) {
        return true;
    }

    // Start DFS traversal from a vertex with a non-zero degree
    DFS(i, visited);

    // Check if all vertices with non-zero degree are visited
    for (i = 0; i < vertices; i++) {
        if (!adjList[i].empty() && !visited[i]) {
            return false;
        }
    }

    return true;
}

void Graph::DFS(size_t v, vector<bool>& visited) {
    visited[v] = true;

    for (size_t i = 0; i < vertices;i++) {
        if (!visited[i]) {
            DFS(i, visited);
        }
    }
}

int Graph::findStartVertex() {
    int start = 0;
    for (size_t i = 0; i < vertices; i++) {
        if (adjList[i].size() % 2 != 0) {
            return i;
        }
    }
    return start;
}

bool Graph::isEulerian() {
    if (!isConnected()) {
        return false;
    }

    int odd = 0;
    for (size_t i = 0; i < vertices; i++) {
        if (adjList[i].size() % 2 != 0) {
            odd++;
        }
    }

    return (odd == 0);
}

void Graph::findEulerCircuit() {
    if (!isEulerian()) {
        cout << "The graph does not have an Eulerian circuit." << endl;
        return;
    }

    list<int> circuit;
    map<pair<int, int>, bool> edgeVisited;
    vector<int> stack;
    int startVertex = findStartVertex();

    stack.push_back(startVertex);

    while (!stack.empty()) {
        size_t v = (size_t)stack.back();

        bool found = false;
        for (size_t i = 0;i < vertices ;i++) {
            if (!edgeVisited[{v, i}]) {
                edgeVisited[{v, i}] = edgeVisited[{i, v}] = true;
                stack.push_back(i);
                found = true;
                break;
            }
        }

        if (!found) {
            circuit.push_front(v);
            stack.pop_back();
        }
    }

    for (int vertex : circuit) {
        cout << vertex << " ";
    }
    cout << endl;
}

void Graph::printGraph() {
    for (size_t i = 0; i < vertices; i++) {
        cout << i << " -> ";
        for (size_t j = 0;j < vertices ;j++) {
            cout << adjList[i][j] << " ";
        }
        cout << endl;
    }
}
