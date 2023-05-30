#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

void bfs(int start, vector<vector<int>>& graph, vector<bool>& visited) {
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int size = q.size();

        #pragma omp parallel for
        for (int i = 0; i < size; i++) {
            int current;
            #pragma omp critical
            {
                current = q.front();
                q.pop();
            }

            cout << current << " ";

            for (int j = 0; j < graph[current].size(); j++) {
                int neighbor = graph[current][j];
                if (!visited[neighbor]) {
                    #pragma omp critical
                    {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
        }
    }
}

int main() {
    int vertices, edges;
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edges;

    vector<vector<int>> graph(vertices);
    vector<bool> visited(vertices, false);

    cout << "Enter the edges (format: vertex1 vertex2):\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int start;
    cout << "Enter the starting vertex: ";
    cin >> start;

    cout << "BFS traversal: ";
    bfs(start, graph, visited);
    cout << endl;

    return 0;
}
