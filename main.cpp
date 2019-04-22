#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int N;
    std::cin >> N;
    std::vector<std::vector<int>> Graph(N, std::vector<int>(N, 0));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            int a;
            std::cin >> a;
            Graph[i][j] = a;
        }

    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                Graph[i][j] = min(Graph[i][j], (Graph[i][k] + Graph[k][j]));
            }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cout << Graph[i][j]<<" ";
        }
        std::cout << std::endl;
    }
    return 0;
}