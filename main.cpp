#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <set>

struct Dot
{
    Dot (int a, int b): vertex(a), weight(b){}
    int vertex;
    int weight;
};

class CGraph
{
public:
    CGraph(int numOfVertices) : AmountOfVertices(numOfVertices), lists(numOfVertices) {}

    virtual void AddEdge(int from, int to, int weight);

    void GetRelated(int vertex, std::vector<Dot> &vertices) const;

    virtual int VerticesCount() const;

private:
    int AmountOfVertices;
    std::vector<std::list<Dot>> lists;
};

void CGraph::AddEdge(int from, int to, int weight)
{
    lists[to].push_back(Dot(from, weight));
    lists[from].push_back(Dot(to, weight));
}

int CGraph::VerticesCount() const
{
    return AmountOfVertices;
}


void CGraph::GetRelated(int vertex, std::vector<Dot> &vertices) const
{
    vertices.clear();
    for (const Dot &i : lists[vertex])
        vertices.push_back(i);
}

int FindMinWays(const CGraph &graph, int from, int to)
{
    std::set<std::pair<int, int>> waySet;
    waySet.emplace(std::make_pair(0, from));

    std::vector<int> way(graph.VerticesCount(), INT_MAX);
    way[from] = 0;

    while (waySet.size() != 0)
    {
        int v = (waySet.begin())->second;
        std::vector<Dot> ways;
        graph.GetRelated(v, ways);
        waySet.erase(waySet.begin());

        for (Dot p : ways)
        {
            if (way[p.vertex] > p.weight + way[v])
            {
                if (way[p.vertex] != INT_MAX)
                    waySet.erase(std::make_pair(way[p.vertex], p.vertex));

                way[p.vertex] = p.weight + way[v];
                waySet.emplace(std::pair<int, int>(way[p.vertex], p.vertex));
            }
        }
    }

    if (way[to] != INT_MAX)
        return way[to];
    else
        return -1;
}


int main()
{
    int N, M;
    std::cin >> N;
    std::cin >> M;
    CGraph graph(N);
    for (int i = 0; i < M; ++i)
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        graph.AddEdge(a, b, c);
    }
    int f, t;
    std::cin >> f >> t;
    std::cout << FindMinWays(graph, f, t);
    return 0;
}