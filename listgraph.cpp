#include "listgraph.h"

void Graph::AddEdge(int from, int to)
{
    listsTo[to].push_back(from);
    listsFrom[from].push_back(to);
}

int Graph::VerticesCount() const
{
    return AmountOfVertices;
}

void Graph::GetNextVertices(int vertex, vector<int>& vertices) const
{
    vertices.clear();
    for (int i : listsFrom[vertex])
    {
        vertices.push_back(i);
    }
}

void Graph::GetPrevVertices(int vertex, vector<int>& vertices) const
{
    vertices.clear();

    for (int i = 0; i < listsFrom.size(); ++i)
    {
        for (auto j: listsFrom[i])
        {
            if (j == vertex)
            {
                vertices.push_back(j);
            }
        }
    }
}
