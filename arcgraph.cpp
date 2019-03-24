#include "arcgraph.h"

void ArcGraph :: AddEdge(int from, int to)
{
    Ribs.push_back(Rib(from, to));
}

int ArcGraph :: VerticesCount() const
{
    return AmountOfVertices;
}

void ArcGraph :: GetNextVertices(int vertex, std::vector<int>& vertices) const
{
    vertices.clear();
    for (auto Rib : Ribs)
    {
        if (Rib.from == vertex)
        {
            vertices.push_back(Rib.to);
        }
    }
}

void ArcGraph :: GetPrevVertices(int vertex, std::vector<int>& vertices) const
{
    vertices.clear();
    for (auto Rib : Ribs)
    {
        if (Rib.to == vertex)
        {
            vertices.push_back(Rib.from);
        }
    }
}
