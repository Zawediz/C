#include "igraph.h"
#include <unordered_set>

class SetGraph: public IGraph
{

public:

    SetGraph(int numOfVertices): AmountOfVertices(numOfVertices), tableTo(numOfVertices), tableFrom(numOfVertices){}

    SetGraph(const IGraph* graph);

    virtual void AddEdge(int from, int to);

    virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const;

private:
    int AmountOfVertices;

    std::vector<std::unordered_set<int>> tableTo;
    std::vector<std::unordered_set<int>> tableFrom;
};