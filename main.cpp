#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

class Graph
{
public:
    Graph(unsigned int Number):ConstVerticesNumber(Number),OutVector(Number){}
    void GetNextVertices(int vertex, vector<int> & NextVertices) const;
    int MinCycle();
    int VerticesNumber() const;
    void AddRib(int from, int to);
private:
    struct Node
    {
        Node():depth(0),visited(false){}
        int depth;
        int previous;
        bool visited;
    };
    int Cycle(int vertex);
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

int Graph :: Cycle(int vertex)
{
    vector<Node> Vertices(VerticesNumber());
    queue<int> Queue;
    Queue.push(vertex);
    Vertices[vertex].visited = true;

    while(Queue.size() != 0)
    {
        vector<int> NextVertices;
        int CurrentVertex = Queue.front();
        GetNextVertices(CurrentVertex, NextVertices);
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
    return VerticesNumber() + 1;
}

int Graph :: MinCycle()
{
    int minCycle = VerticesNumber() + 1;
    for(int i = 0; i < VerticesNumber(); ++i)
    {
        int cycle = Cycle(i);
        if (cycle < minCycle) minCycle = cycle;
    }
    return minCycle;
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

    int min = graph.MinCycle();
    if (min == graph.VerticesNumber() + 1) min = -1;
    cout << min;
    return 0;
}