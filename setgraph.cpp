#include "setgraph.h"

SetGraph::SetGraph(const IGraph* graph): AmountOfVertices(graph->VerticesCount()),tableTo(graph->VerticesCount()), tableFrom(graph->VerticesCount())
{
    for(int i = 0; i < AmountOfVertices; ++i)
    {
        std::vector<int> vertices;
        graph->GetNextVertices(i, vertices);
        for(int j = 0; j < vertices.size(); ++j)
            {
            AddEdge(i, j);
            }
    }
}

void SetGraph::AddEdge(int from, int to)
{
    tableFrom[from].insert(to);
    tableTo[to].insert(from);
}

int SetGraph::VerticesCount() const
{
    return AmountOfVertices;
}

void SetGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const
{
    vertices.clear();
    for(int i : tableFrom[vertex])
    {
        vertices.push_back(i);
    }
}

void SetGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const
{
    vertices.clear();
    for(int i : tableTo[vertex])
    {
        vertices.push_back(i);
    }
}
