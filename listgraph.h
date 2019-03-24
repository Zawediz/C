#include "igraph.h"

class Graph: public IGraph
{

public:

    Graph(int numOfVertices): AmountOfVertices(numOfVertices), listsTo(numOfVertices), listsFrom(numOfVertices){}

    Graph(const IGraph* graph);

    virtual void AddEdge(int from, int to);

    virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const;

private:
    int AmountOfVertices;

    std::vector<std::vector<int>> listsTo;
    std::vector<std::vector<int>> listsFrom;
};