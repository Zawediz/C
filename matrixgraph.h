#include "igraph.h"

class MatrixGraph: public IGraph
{

public:

    MatrixGraph(int n): AmountOfVertices(n), matrix(n)
    {
        for(int i = 0; i < AmountOfVertices; ++i)
        {
            matrix[i].resize(AmountOfVertices, false);
        }
    }

    MatrixGraph(const IGraph* graph): AmountOfVertices(graph->VerticesCount()), matrix(graph->VerticesCount())
    {

        for(int i = 0; i < AmountOfVertices; ++i)
        {
            matrix[i].resize(AmountOfVertices, false);
        }

        for(int i = 0; i < AmountOfVertices; ++i)
        {
            vector<int> vertices;
            graph->GetNextVertices(i, vertices);
            for (int j = 0; j < vertices.size(); ++j)
            {
                AddEdge(i, j);
            }
        }
    }

    virtual void AddEdge(int from, int to);

    virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, vector<int>& vertices) const;
    virtual void GetPrevVertices(int vertex, vector<int>& vertices) const;

private:

    int AmountOfVertices;

    vector<vector<bool>> matrix;
};