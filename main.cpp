#include <iostream>
#include <algorithm>
#include <vector>

struct Node {
    Node() { value = prefix_value = suffix_value = is_full = 0; };

    Node(int value) : value(value), prefix_value(value), suffix_value(value), is_full(value) {};

    int value;
    int prefix_value;
    int suffix_value;
    int is_full;
};

class SegmentTree {
public:
    SegmentTree() {};

    SegmentTree(std::vector<int> &a) {
        t.resize(4 * a.size());
        build(0, 0, a.size() - 1, a);
    }

    int calc_answer(int l, int r) {
        return get(0, 0, t.size() / 4 - 1, l, r).value;
    }

private:
    std::vector<Node> t;

    Node recalc(Node l, Node r) {
        Node result;
        result.value = std::max({l.value, r.value, l.suffix_value + r.prefix_value});
        result.prefix_value = l.is_full ? l.value + r.prefix_value : l.prefix_value;
        result.suffix_value = r.is_full ? r.value + l.suffix_value : r.suffix_value;
        result.is_full = l.is_full * r.is_full;
        return result;
    }

    void build(int v, int tl, int tr, std::vector<int> &a) {
        if (tl == tr) {
            t[v] = Node(a[tl]);
            return;
        }
        int tm = (tl + tr) >> 1;
        build(2 * v + 1, tl, tm, a);
        build(2 * v + 2, tm + 1, tr, a);
        t[v] = recalc(t[2 * v + 1], t[2 * v + 2]);
    }

    Node get(int v, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return Node();
        }
        if (l <= tl && tr <= r) {
            return t[v];
        }
        int tm = (tl + tr) >> 1;
        return recalc(get(2 * v + 1, tl, tm, l, r), get(2 * v + 2, tm + 1, tr, l, r));
    }
};


int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    SegmentTree T(a);
    for (int i = 0; i < m; ++i) {
        int l, r;
        std::cin >> l >> r;
        std::cout << T.calc_answer(l, r) << std::endl;
    }
    return 0;
}