#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <omp.h>

using namespace std;

// Graph class representing an undirected graph
class Graph {
private:
    int numVertices;
    vector<vector<int>> adjacencyList;

public:
    Graph(int numVertices) : numVertices(numVertices), adjacencyList(numVertices) {}

    // Add an edge between two vertices
    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }

    // Parallel Breadth First Search (BFS)
    unordered_set<int> bfsParallel(int startVertex) {
        unordered_set<int> visited;
        queue<int> bfsQueue;
        bfsQueue.push(startVertex);

        #pragma omp parallel
        {
            while (!bfsQueue.empty()) {
                #pragma omp for nowait
                for (int i = 0; i < bfsQueue.size(); i++) {
                    int currentVertex = bfsQueue.front();
                    bfsQueue.pop();

                    // Mark the current vertex as visited
                    #pragma omp critical
                    {
                        if (visited.find(currentVertex) == visited.end()) {
                            visited.insert(currentVertex);
                        }
                    }

                    // Enqueue the unvisited neighbors of the current vertex
                    for (int neighbor : adjacencyList[currentVertex]) {
                        #pragma omp critical
                        {
                            if (visited.find(neighbor) == visited.end()) {
                                bfsQueue.push(neighbor);
                            }
                        }
                    }
                }
            }
        }

        return visited;
    }

    // Parallel Depth First Search (DFS)
    unordered_set<int> dfsParallel(int startVertex) {
        unordered_set<int> visited;
        dfsHelper(startVertex, visited);
        return visited;
    }

private:
    // DFS helper function
    void dfsHelper(int vertex, unordered_set<int>& visited) {
        visited.insert(vertex);

        #pragma omp parallel for
        for (int neighbor : adjacencyList[vertex]) {
            if (visited.find(neighbor) == visited.end()) {
                dfsHelper(neighbor, visited);
            }
        }
    }
};

int main() {
    // Create a sample graph
    Graph graph(8);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(2, 5);
    graph.addEdge(3, 6);
    graph.addEdge(3, 7);

    // Perform parallel BFS
    unordered_set<int> bfsResult = graph.bfsParallel(0);
    cout << "Parallel BFS Result: ";
    for (int vertex : bfsResult) {
        cout << vertex << " ";
    }
    cout << endl;

    // Perform parallel DFS
    unordered_set<int> dfsResult = graph.dfsParallel(0);
    cout << "Parallel DFS Result: ";
    for (int vertex : dfsResult) {
        cout << vertex << " ";
    }
    cout << endl;

    return 0;
}