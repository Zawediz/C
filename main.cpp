#include <iostream>
#include <vector>
#include <algorithm>

class Graph{
public:
    Graph(int N):N(N), graph(N, std::vector<int>(N, 0)){}
    void AddEdge(int i, int j, int a);
    void MinPaths();
    int GetEdge(int i, int j);
private:
    std::vector<std::vector<int>> graph;
    int N;
};

void Graph::AddEdge(int i, int j, int a) {
    graph[i][j] = a;
}

void Graph::MinPaths() {
    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                graph[i][j] = min(graph[i][j], (graph[i][k] + graph[k][j]));
            }
}

int Graph::GetEdge(int i, int j) {
    return graph[i][j];
}

int main() {
    int N;
    std::cin >> N;
    Graph G(N);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            int a;
            std::cin >> a;
            G.AddEdge(i,j,a);
        }

    G.MinPaths();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << G.GetEdge(i,j) << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}