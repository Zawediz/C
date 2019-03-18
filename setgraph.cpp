#include "setgraph.h"

void SetGraph::AddEdge(int from, int to)
{
    tableFrom[from].insert(to);
    tableTo[to].insert(from);
}

int SetGraph::VerticesCount() const
{
    return AmountOfVertices;
}

void SetGraph::GetNextVertices(int vertex, vector<int> &vertices) const
{
    vertices.clear();
    for(int i : tableFrom[vertex])
    {
        vertices.push_back(i);
    }
}

void SetGraph::GetPrevVertices(int vertex, vector<int> &vertices) const
{
    vertices.clear();
    for(int i : tableTo[vertex])
    {
        vertices.push_back(i);
    }
}
