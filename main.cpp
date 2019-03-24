#include <iostream>
#include <assert.h>
#include "setgraph.h"
#include <algorithm>

int main()
{
    SetGraph Graph1(6);
    Graph1.AddEdge(0, 1);
    Graph1.AddEdge(1, 2);
    Graph1.AddEdge(2, 3);
    Graph1.AddEdge(4, 5);

    assert(Graph1.VerticesCount() == 6);

    std::vector<int> nexts;
    Graph1.GetNextVertices(1, nexts);

    std::vector<int> NextsTrue;
    NextsTrue.push_back(2);

    sort(NextsTrue.begin(), NextsTrue.end());
    sort(nexts.begin(), nexts.end());

    for (int i = 0; i < __min(nexts.size(),NextsTrue.size()); ++i)
    {
        assert(nexts[i] == NextsTrue[i]);
    }

    std::vector<int> prevs;
    Graph1.GetPrevVertices(1, prevs);

    std::vector<int> PrevsTrue;
    PrevsTrue.push_back(0);

    sort(PrevsTrue.begin(), PrevsTrue.end());
    sort(prevs.begin(), prevs.end());

    for (int i = 0; i < __min(prevs.size(),PrevsTrue.size()); ++i)
    {
        assert(prevs[i] == PrevsTrue[i]);
    }
    return 0;
}