#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

using namespace std;

void parallelBFS(vector<vector<int>>& graph, int source) {
    int numVertices = graph.size();
    vector<bool> visited(numVertices, false);
    vector<int> level(numVertices, -1);

    queue<int> q;
    level[source] = 0;
    visited[source] = true;
    q.push(source);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        #pragma omp parallel for
        for (int i = 0; i < graph[current].size(); ++i) {
            int neighbor = graph[current][i];

            if (!visited[neighbor]) {
                #pragma omp critical
                {
                    visited[neighbor] = true;
                    level[neighbor] = level[current] + 1;
                    q.push(neighbor);
                }
            }
        }
        cout << "Processing node: " << current << " (Thread: " << omp_get_thread_num() << ")" << endl;

    }

    // Print the level of each vertex
    cout << "Vertex\tLevel" << endl;
    for (int i = 0; i < numVertices; ++i) {
        cout << i << "\t" << level[i] << endl;
    }
}

int main() {
    int numVertices = 7;
    vector<vector<int>> graph(numVertices);

    // Add edges to the graph
    graph[0] = {1, 2};
    graph[1] = {0, 3, 4};
    graph[2] = {0, 5, 6};
    graph[3] = {1};
    graph[4] = {1};
    graph[5] = {2};
    graph[6] = {2};

    int source = 0;
    parallelBFS(graph, source);

    return 0;
}

