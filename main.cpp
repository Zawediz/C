#include <iostream>
#include <vector>
using namespace std;

int rangeMaxSum(vector<int>& mas,int l, int r){
    int ans = mas[l];
    int	sum = 0;
    for (int i = l; i <= r; ++i) {
        if (mas[i] == 0){
            sum = 0;
            continue;
        }

        sum += mas[i];

        if (sum > ans) {
            ans = sum;
        }
    }
    return ans;
}

int main()
{
    int n,m;
    cin >> n >> m;
    vector<int> mas;
    for (int i = 0; i < n; ++i){
        int a;
        cin >> a;
        mas.push_back(a);
    }

    for (int i = 0; i < m; ++i){
        int l,r;
        cin >> l >> r;
        cout << rangeMaxSum(mas,l,r) << std::endl;
    }

    return 0;
}