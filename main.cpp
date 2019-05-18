#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    Edge(int from, int to, int capacity) : from(from), to(to), capacity(capacity), usedCapacity(0) {}
    int from;
    int to;
    int capacity;
    int usedCapacity;
};

class Graph{
public:
    Graph(int n): numberOfVertices(n), numbersOfEdges(n), positionOfEdge(n, 0), path(n) {}
    void addEdge(int from, int to, int capacity);

    int maxFlow(int from , int to);
private:
    bool BFS(int current, int to);
    bool DFS(int current, int to);
    int numberOfVertices;

    vector<Edge> edges;
    vector<int> used;
    vector<vector<int> > numbersOfEdges;
    vector<int> positionOfEdge;
    vector<int> path;
};

void Graph::addEdge(int from, int to, int capacity){
    edges.push_back(Edge(from, to, capacity));
    numbersOfEdges[from].push_back(edges.size() - 1);
    numbersOfEdges[to].push_back(edges.size() - 1);
}

bool Graph::BFS(int current, int to) {
    queue<int> q;
    used[current] = 1;
    q.push(current);
    while (!q.empty()) {
        current = q.front();
        q.pop();
        if (current == to){
            return true;
        }
        for (unsigned i = 0; i < numbersOfEdges[current].size(); i++) {
            int number = numbersOfEdges[current][i];

            int to;
            if (edges[number].from == current){
                to = edges[number].to;
            } else {
                to = edges[number].from;
            }

            if (!used[to]){
                int capacity;
                if (edges[number].to == to){
                    capacity = edges[number].capacity - edges[number].usedCapacity;
                } else {
                    capacity = edges[number].usedCapacity;
                }
                if (capacity){
                    path[to] = number;
                    used[to] = used[current] + 1;
                    q.push(to);
                }
            }
        }
    }
    return false;
}

bool Graph::DFS(int current, int target) {
    if (current == target){
        return true;
    }
    while(positionOfEdge[current] < (int)numbersOfEdges[current].size()){
        int number = numbersOfEdges[current][positionOfEdge[current]];

        int to;
        if (edges[number].from == current){
            to = edges[number].to;
        } else {
            to = edges[number].from;
        }

        if (used[current] + 1 == used[to]) {
            int capacity;
            if (edges[number].to == to){
                capacity = edges[number].capacity - edges[number].usedCapacity;
            } else {
                capacity = edges[number].usedCapacity;
            }
            if (capacity){
                path[to] = number;
                if (DFS(to, target)){
                    return true;
                }
            }
        }
        positionOfEdge[current]++;
    }
    return false;
}

int Graph::maxFlow(int from , int to){
    int maxFlow = 0;
    while (true) {
        used.assign(numberOfVertices, 0);
        if (!BFS(from, to)){
            break;
        }
        positionOfEdge.assign(numberOfVertices, 0);
        while (DFS(from, to)) {
            int flow = INT_MAX;
            int v = to;
            while (v != from){
                int capacity;
                if (edges[path[v]].to == v){
                    capacity = edges[path[v]].capacity - edges[path[v]].usedCapacity;
                    v = edges[path[v]].from;
                } else {
                    capacity = edges[path[v]].usedCapacity;
                    v = edges[path[v]].to;
                }

                flow = min(flow, capacity);
            }

            maxFlow += flow;

            v = to;
            while(v != from){
                if (edges[path[v]].to == v){
                    edges[path[v]].usedCapacity += flow;
                    v = edges[path[v]].from;
                } else {
                    edges[path[v]].usedCapacity -= flow;
                    v = edges[path[v]].to;
                }
            }
        }
    }
    return maxFlow;
}

int main() {
    int n, m;
    cin >> n >> m;

    Graph graph(n);

    for (int i = 0; i < m; i++) {
        int from, to, capacity;
        cin >> from >> to >> capacity;
        graph.addEdge(from - 1, to - 1, capacity);
    }

    cout << graph.maxFlow(0, n - 1);
    return 0;
}
