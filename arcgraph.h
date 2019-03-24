#include "igraph.h"

struct Rib
{
    Rib(int from, int to): from(from), to(to){}

    int from;
    int to;
};


class ArcGraph: public IGraph
{
public:

    ArcGraph(int numOfVertices): AmountOfVertices(numOfVertices){}

    ArcGraph(const IGraph* graph): AmountOfVertices(graph->VerticesCount())
    {
        for(int i = 0; i < AmountOfVertices; ++i)
        {
            std::vector<int> vertices;
            graph->GetNextVertices(i, vertices);
            for (int j = 0; j < vertices.size(); ++j)
            {
                AddEdge(i, j);
            }
        }
    }

    virtual void AddEdge(int from, int to);

    virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const;

private:

    int AmountOfVertices;
    std::vector<Rib> Ribs;

};
