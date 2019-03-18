#include "matrixgraph.h"

void MatrixGraph::AddEdge(int from, int to)
{
    matrix[from][to] = true;
    matrix[to][from] = true;
}

int MatrixGraph::VerticesCount() const
{
    return AmountOfVertices;
}

void MatrixGraph::GetNextVertices(int vertex, vector<int>& vertices) const
{
    vertices.clear();
    for (int i = 0; i < VerticesCount(); ++i)
    {
        if(matrix[vertex][i])
        {
            vertices.push_back(i);
        }
    }
}
void MatrixGraph::GetPrevVertices(int vertex, vector<int>& vertices) const
{
    vertices.clear();
    for (int i = 0; i < VerticesCount(); ++i)
    {
        if(matrix[i][vertex])
        {
            vertices.push_back(i);
        }
    }
}
