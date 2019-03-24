#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

struct Node
{
    Node():depth(0),visited(false){}
    int depth;
    int previous;
    bool visited;
};

class Graph
{
public:
    Graph(unsigned int Number):ConstVerticesNumber(Number),OutVector(Number){}
    void GetNextVertices(int vertex, vector<int> & NextVertices) const;
    int VerticesNumber() const;
    void AddRib(int from, int to);
private:

    unsigned int ConstVerticesNumber;
    vector<unordered_set<int>> OutVector;
};

int Graph :: VerticesNumber() const
{
    return ConstVerticesNumber;
}

void Graph :: AddRib(int from, int to)
{
    OutVector[to].insert(from);
    OutVector[from].insert(to);
}

void Graph :: GetNextVertices(int vertex, vector<int> & NextVertices) const
{
    for (int i : OutVector[vertex]) NextVertices.push_back(i);
}

int Cycle(int vertex, Graph& graph)
{
    vector<Node> Vertices(graph.VerticesNumber());
    queue<int> Queue;
    Queue.push(vertex);
    Vertices[vertex].visited = true;

    while(Queue.size() != 0)
    {
        vector<int> NextVertices;
        int CurrentVertex = Queue.front();
        graph.GetNextVertices(CurrentVertex, NextVertices);
        Queue.pop();

        for(int i : NextVertices)
        {
            if(Vertices[i].visited == false)
            {
                Vertices[i].visited = true;
                Vertices[i].depth = Vertices[CurrentVertex].depth + 1;
                Vertices[i].previous = CurrentVertex;
                Queue.push(i);
            }

            else if(i != Vertices[CurrentVertex].previous)
            {
                return Vertices[CurrentVertex].depth + Vertices[i].depth + 1;
            }
        }
    }
    return -1;
}

int MinCycle(Graph& graph)
{
    bool f = false;
    int minCycle = graph.VerticesNumber() + 1;
    for(int i = 0; i < graph.VerticesNumber(); ++i)
    {
        int cycle = Cycle(i, graph);
        if (cycle < minCycle)
        {
            minCycle = cycle;
            f = true;
        }
    }
    if (f)
        return minCycle;
    else
        return -1;
}

int main()
{
    unsigned int v = 0;
    cin >> v;
    Graph graph(v);

    int n;
    cin >> n;

    for(int i = 0; i < n; ++i)
    {
        int f, s;
        cin >> f >> s;
        graph.AddRib(f, s);
    }

    int min = MinCycle(graph);
    cout << min;
    return 0;
}
