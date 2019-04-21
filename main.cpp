#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <set>

const unsigned INF = INT_MAX;

struct Dot
{
    Dot (int a, int b): vertex(a), weight(b){}
    int vertex;
    int weight;
};

class Graph
{
public:
    Graph(int numOfVertices) : AmountOfVertices(numOfVertices), lists(numOfVertices) {}

    virtual void AddEdge(int from, int to, int weight);

    void GetRelated(int vertex, std::vector<Dot> &vertices) const;

    virtual int VerticesCount() const;

private:
    int AmountOfVertices;
    std::vector<std::list<Dot>> lists;
};

void Graph::AddEdge(int from, int to, int weight)
{
    lists[to].push_back(Dot(from, weight));
    lists[from].push_back(Dot(to, weight));
}

int Graph::VerticesCount() const
{
    return AmountOfVertices;
}


void Graph::GetRelated(int vertex, std::vector<Dot> &vertices) const
{
    vertices.clear();
    for (const Dot &i : lists[vertex])
        vertices.push_back(i);
}

int Dijkstra(Graph const &graph, int from, int to)
{
    std::set<std::pair<int, int>> PairSet;
    PairSet.emplace(std::make_pair(0, from));

    std::vector<int> way(graph.VerticesCount(), INF);
    way[from] = 0;

    while (PairSet.size() != 0)
    {
        int v = (PairSet.begin())->second;
        std::vector<Dot> ways;
        graph.GetRelated(v, ways);
        PairSet.erase(PairSet.begin());

        for (Dot p : ways)
        {
            if (way[p.vertex] > p.weight + way[v])
            {
                if (way[p.vertex] != INF)
                    PairSet.erase(std::make_pair(way[p.vertex], p.vertex));

                way[p.vertex] = p.weight + way[v];
                PairSet.emplace(std::pair<int, int>(way[p.vertex], p.vertex));
            }
        }
    }

    if (way[to] != INF)
        return way[to];
    else
        return -1;
}


int main()
{
    int N, M, f, t;
    std::cin >> N;
    std::cin >> M;
    Graph graph(N);
    for (int i = 0; i < M; ++i)
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        graph.AddEdge(a, b, c);
    }
    std::cin >> f >> t;
    std::cout << Dijkstra(graph, f, t);
    return 0;
}