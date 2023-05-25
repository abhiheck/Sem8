#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void parallelDFS(vector<vector<int>>& graph, int current, vector<bool>& visited) {
    visited[current] = true;

    cout << "Visited vertex: " << current << endl;

    #pragma omp parallel for
    for (int i = 0; i < graph[current].size(); ++i) {
        int neighbor = graph[current][i];

        if (!visited[neighbor]) {
            #pragma omp task
            parallelDFS(graph, neighbor, visited);
        }
        int threadNum= omp_get_thread_num();
        cout<<"thread using "<<threadNum << "for processing element " << i<<endl;
    }
}

void parallelDFSWrapper(vector<vector<int>>& graph) {
    int numVertices = graph.size();
    vector<bool> visited(numVertices, false);

    #pragma omp parallel
    {
        #pragma omp single nowait
        parallelDFS(graph, 0, visited);
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

    parallelDFSWrapper(graph);

    return 0;
}


