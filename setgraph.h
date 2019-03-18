#include "igraph.h"
#include <unordered_set>

class SetGraph: public IGraph
{

public:

    SetGraph(int numOfVertices): AmountOfVertices(numOfVertices), tableTo(numOfVertices), tableFrom(numOfVertices){}

    SetGraph(const IGraph* graph): AmountOfVertices(graph->VerticesCount()),tableTo(graph->VerticesCount()), tableFrom(graph->VerticesCount())
    {
        for(int i = 0; i < AmountOfVertices; ++i)
        {
            vector<int> vertices;
            graph->GetNextVertices(i, vertices);
            for(int j = 0; j < vertices.size(); ++j)
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

    vector<unordered_set<int>> tableTo;
    vector<unordered_set<int>> tableFrom;
};