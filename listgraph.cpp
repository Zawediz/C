#include "listgraph.h"

Graph::Graph(const IGraph *graph):AmountOfVertices(graph->VerticesCount()),listsTo(graph->VerticesCount()),listsFrom(graph->VerticesCount())
{
    {
        for (int i = 0; i < AmountOfVertices; ++i)
        {
            std::vector<int> vertices;
            graph->GetNextVertices(i, vertices);
            for (int j = 0; j < vertices.size(); ++j)
            {
                AddEdge(i, j);
            }

        }
    }
}

void Graph::AddEdge(int from, int to)
{
    listsTo[to].push_back(from);
    listsFrom[from].push_back(to);
}

int Graph::VerticesCount() const
{
    return AmountOfVertices;
}

void Graph::GetNextVertices(int vertex, std::vector<int>& vertices) const
{
    vertices.clear();
    for (int i : listsFrom[vertex])
    {
        vertices.push_back(i);
    }
}

void Graph::GetPrevVertices(int vertex, std::vector<int>& vertices) const
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
