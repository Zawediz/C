#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

struct Edge {
    Edge(int vertex, int weight) : vertex(vertex), weight(weight) {}

    int vertex;
    int weight;

};

class CGraph {

public:

    CGraph(int n) : AmountOfVertices(n), lists(n) {}

    int VerticesCount() const;

    void AddEdge(int from, int to, int weight);

    void GetEdges(int vertex, vector <Edge> &edges) const;

private:
    unsigned AmountOfVertices;
    vector <vector<Edge>> lists;
};

int CGraph::VerticesCount() const {
    return AmountOfVertices;
}

void CGraph::AddEdge(int from, int to, int weight) {
    lists[from].push_back(Edge(to, weight));
    lists[to].push_back(Edge(from, weight));
}

void CGraph::GetEdges(int vertex, vector <Edge> &edges) const {
    edges.clear();

    for (Edge item: lists[vertex]) {
        edges.push_back(item);
    }
}

int PrimFunction(CGraph &graph) {
    int answer = 0;

    std::set<pair<int, int>> Q;
    int size = graph.VerticesCount();
    vector<bool> used(size, false);
    Q.emplace(std::make_pair(0, 0));

    while (!Q.empty()) {
        pair<int, int> f = *Q.begin();
        Q.erase(Q.begin());


        int weight = f.first;
        int v = f.second;

        if (!used[v]) {
            used[v] = true;
            answer += weight;

            vector <Edge> edges;
            graph.GetEdges(v, edges);

            for (Edge edge: edges) {
                if (!used[edge.vertex]) {
                    Q.emplace(make_pair(edge.weight, edge.vertex));
                }
            }
        }
    }

    return answer;
}


int main() {
    int n, m;

    cin >> n >> m;
    CGraph graph(n);
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph.AddEdge(from - 1, to - 1, weight);
    }

    cout << PrimFunction(graph);
    return 0;
}