#include "igraph.h"

class Graph: public IGraph
{

public:

    Graph(int numOfVertices): AmountOfVertices(numOfVertices), listsTo(numOfVertices), listsFrom(numOfVertices){}

    Graph(const IGraph* graph): AmountOfVertices(graph->VerticesCount()), listsTo(graph->VerticesCount()), listsFrom(graph->VerticesCount())
    {
        for (int i = 0; i < AmountOfVertices; ++i)
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

    vector<vector<int>> listsTo;
    vector<vector<int>> listsFrom;
};