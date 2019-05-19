#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct heightVertex {
    heightVertex(int height, int vertex) : height(height), vertex(vertex) {}

    heightVertex() : height(0), vertex(0) {}

    int height;
    int vertex;
};

heightVertex minHV(const heightVertex &first, const heightVertex &second) {
    if (first.height > second.height) {
        return second;
    }
    return first;
}

class SparseTable {

public:

    SparseTable(vector<heightVertex> a) {
        int n = a.size();
        logs.resize(n + 1);
        for (int i = 2; i <= n; ++i) {
            logs[i] = logs[i >> 1] + 1;
        }
        table = vector<vector<heightVertex>>(20, vector<heightVertex>(n));
        table[0] = a;
        for (unsigned l = 1; l < table.size(); ++l) {
            for (int i = 0; i + (1 << l) <= n; ++i) {
                table[l][i] = minHV(table[l - 1][i], table[l - 1][i + (1 << (l - 1))]);
            }
        }
    }

    SparseTable() {}

    int get(int l, int r) {
        int L = logs[r - l + 1];
        return minHV(table[L][l], table[L][r - (1 << L) + 1]).vertex;
    }

private:
    vector<int> logs;
    vector<vector<heightVertex>> table;

};

class LCA {

public:
    LCA(const vector<vector<int> > &sons) : position(sons.size(), -1), sons(sons) {
        dfs(0, 0);
        table = SparseTable(e);
    }

    int getLCA(int a, int b) {
        int l = position[a];
        int r = position[b];
        if (l > r)
            swap(l, r);
        return table.get(l, r);
    }

private:
    void dfs(int vertex, int height) {
        position[vertex] = e.size();
        e.push_back(heightVertex(height, vertex));
        for (int to : sons[vertex]) {
            dfs(to, height + 1);
            e.push_back(heightVertex(height, vertex));
        }
    }


    vector<int> position;
    vector<heightVertex> e;
    vector<vector<int> > sons;
    SparseTable table;
};


int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > sons(n);
    for (int i = 1; i < n; ++i) {
        int x;
        cin >> x;
        sons[x].push_back(i);
    }

    LCA lca(sons);
    unsigned long long a1, a2, y, x, z, prev = 0;
    cin >> a1 >> a2 >> x >> y >> z;
    unsigned long long sum = 0;
    while (m--) {
        prev = lca.getLCA((a1 + prev) % n, a2);

        sum += prev;
        a1 = (a1 * x + a2 * y + z) % n;
        a2 = (a2 * x + a1 * y + z) % n;
    }

    cout << sum;
    return 0;
}