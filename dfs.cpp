#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

void dfs(int start, vector<vector<int>>& graph, vector<bool>& visited) {
    stack<int> st;
    visited[start] = true;
    st.push(start);

    while (!st.empty()) {
        int current;
        #pragma omp critical
        {
            current = st.top();
            st.pop();
        }

        cout << current << " ";

        #pragma omp parallel for
        for (int i = 0; i < graph[current].size(); i++) {
            int neighbor = graph[current][i];
            if (!visited[neighbor]) {
                #pragma omp critical
                {
                    visited[neighbor] = true;
                    st.push(neighbor);
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

    cout << "DFS traversal: ";
    dfs(start, graph, visited);
    cout << endl;

    return 0;
}

