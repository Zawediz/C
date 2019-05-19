#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


struct RangeTwoMins {
    RangeTwoMins() {}

    RangeTwoMins(int a, int b) : first(a), second(b) {}

    int first;
    int second;
};

RangeTwoMins twoRangeTwoMins(RangeTwoMins A, RangeTwoMins B) {
    int range[4];

    range[0] = A.first;
    range[1] = B.first;
    range[2] = A.second;
    range[3] = B.second;

    std::sort(range, range + 4);

    int first = range[0];
    int second = -1;

    int i = 1;
    while (i < 4) {
        if (range[i] != first) {
            second = range[i];
            break;
        }
        ++i;
    }

    return RangeTwoMins(first, second);
}

class RMQ {

public:
    RMQ(std::vector<int> &sequence);

    RangeTwoMins secondOrder(int l, int r);

private:
    std::vector<int> sequence;
    std::vector<int> logs;
    std::vector<std::vector<RangeTwoMins> > sparseTable;
};

RMQ::RMQ(std::vector<int> &sequence) : sequence(sequence), sparseTable(ceil(log2(sequence.size())),
                                                                       std::vector<RangeTwoMins>(sequence.size())) {
    for (int i = 0; i < sequence.size() + 1; ++i) {
        logs.push_back((unsigned) ceil(log2(i)));
    }

    for (int i = 0; i < sparseTable.size(); ++i) {
        for (int j = 0; j < sequence.size() - pow(2, i) + 1; ++j) {
            if (i == 0) {
                RangeTwoMins range(sequence[j], sequence[j]);
                sparseTable[0][j] = range;
            } else {
                RangeTwoMins range = twoRangeTwoMins(sparseTable[i - 1][j],
                                                     sparseTable[i - 1][j + (int) pow(2, i - 1)]);
                sparseTable[i][j] = range;
            }
        }
    }
}

RangeTwoMins RMQ::secondOrder(int l, int r) {
    int k = logs[r - l + 1] - 1;
    return twoRangeTwoMins(sparseTable[k][l], sparseTable[k][(r - (int) pow(2, k) + 1)]);
}

int main() {
    int N, M;
    std::cin >> N;
    std::cin >> M;

    std::vector<int> sequence;

    for (int i = 0; i < N; ++i) {
        int a;
        std::cin >> a;
        sequence.push_back(a);
    }

    RMQ Answer(sequence);

    for (int i = 0; i < M; ++i) {
        int l, r;
        std::cin >> l >> r;
        std::cout << Answer.secondOrder(l - 1, r - 1).second << std::endl;
    }

    return 0;
}