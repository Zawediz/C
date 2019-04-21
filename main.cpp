#include <iostream>
#include <vector>

class MatrixGraph
{
public:

    MatrixGraph(int n) : AmountOfVertices(n), matrix(n)
    {
        for (int i = 0; i < AmountOfVertices; ++i)
        {
            matrix[i].resize(AmountOfVertices, -1);
        }
    }

    virtual void AddEdge(int from, int to, double weight);

    virtual int VerticesCount() const;

    virtual void GetNextVertices(int vertex, std::vector<int> &vertices) const;

    virtual void GetPrevVertices(int vertex, std::vector<int> &vertices) const;

    virtual double GetWeight(int i, int j) const;

private:

    int AmountOfVertices;
    std::vector<std::vector<double>> matrix;
};

void MatrixGraph::AddEdge(int from, int to, double weight)
{
    matrix[from][to] = weight;
}

int MatrixGraph::VerticesCount() const
{
    return AmountOfVertices;
}

void MatrixGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const
{
    vertices.clear();
    for (int i = 0; i < VerticesCount(); ++i)
    {
        if (matrix[vertex][i] != -1)
        {
            vertices.push_back(i);
        }
    }
}

void MatrixGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const
{
    vertices.clear();
    for (int i = 0; i < VerticesCount(); ++i)
    {
        if (matrix[i][vertex] != -1)
        {
            vertices.push_back(i);
        }
    }
}

double MatrixGraph::GetWeight(int i, int j) const
{
    return matrix[i][j];
}

bool Arbitrage(const MatrixGraph &graph)
{
    for (int r = 0; r < graph.VerticesCount(); ++r)
    {
        std::vector<double> weights(graph.VerticesCount(), -1);
        std::vector<int> vertices(graph.VerticesCount());
        weights[r] = 1;
        for (int t = 0; t < graph.VerticesCount() - 1; ++t)
        {
            for (int j = 0; j < graph.VerticesCount(); ++j)
            {
                graph.GetPrevVertices(j, vertices);
                for (int i : vertices)
                    if (weights[i] != -1)
                    {
                        if (weights[j] < weights[i] * graph.GetWeight(i, j))
                            weights[j] = weights[i] * graph.GetWeight(i, j);
                    }
            }
        }

        for (int j = 0; j < graph.VerticesCount(); ++j)
        {
            graph.GetPrevVertices(j, vertices);
            for (int i : vertices)
                if (weights[i] != -1)
                {
                    if (weights[j] < weights[i] * graph.GetWeight(i, j))
                        return true;
                }
        }
    }
    return false;
}

int main()
{
    int n;
    std::cin >> n;
    MatrixGraph graph(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i != j)
            {
                double a;
                std::cin >> a;
                graph.AddEdge(i, j, a);
            }
        }
    }

    if (Arbitrage(graph))
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}