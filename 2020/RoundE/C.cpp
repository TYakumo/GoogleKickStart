#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
using namespace std;

using VLL = vector<long long>;
using PLL = pair<long long, long long>;
using PLI = pair<long long, int>;
using VPLI = vector <PLI>;

template<class T>
class FenwickTree {
    vector <T> sum;
public:
    FenwickTree (int treeSize) {
        sum = move(vector<T>(treeSize+1));
    }

    void addVal(int idx, T val) {
        while (idx < sum.size()) {
            sum[idx] += val;
            idx += (idx & (-idx));
        }
    }

    T getVal(int idx) {
        if (idx <= 0) {
            return 0;
        }

        T ret = 0;

        while (idx) {
            ret += sum[idx];
            idx -= (idx & (-idx));
        }

        return ret;
    }

    T queryRange(int a, int b) {
        return getVal(b) - getVal(a-1);
    }
};

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        long long sum = 0;

        int N;
        cin >> N;

        VLL R(N);
        VLL E(N);
        VPLI vec;
        long long ans = 0;
        FenwickTree<long long> ft(N);

        for (int i = 0; i < N; ++i) {
            cin >> E[i] >> R[i];
            sum += E[i];
            ft.addVal(i+1, E[i]);
            vec.emplace_back(make_pair(R[i]+E[i], i));
        }

        sort(vec.begin(), vec.end(), greater<PLI>());

        long long osum = sum;
        int idx = 0;
        int cnt = 0;
        int ansCnt = 0;
        priority_queue < int, vector<int>, greater<int> > pq; // min queue

        while (idx < vec.size() || !pq.empty()) {
            if (idx < vec.size() && vec[idx].first <= sum && pq.empty()) {
                break;
            }

            while (idx < vec.size() && vec[idx].first > sum) {
                pq.push(vec[idx].second);
                ++idx;
            }

            // select the min to remove
            int cho = pq.top();

            pq.pop();
            long long res = sum;
            ft.addVal(cho+1, -E[cho]);
            res += ft.queryRange(1, cho+1);

            if (res > ans) {
                ans = res;
                ansCnt = cnt;
            }

            sum -= E[cho];
            ++cnt;
        }

        if (cnt < vec.size()) {
            cout << "Case #" << tc << ": " << cnt << " INDEFINITELY" << endl;
        } else { // impossible to achieve "INDEFINITELY"
            cout << "Case #" << tc << ": " << ansCnt << " " << ans << endl;
        }
    }

    return 0;
}
