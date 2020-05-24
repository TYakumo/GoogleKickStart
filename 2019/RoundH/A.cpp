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

using VI = vector <int> ;
using VVI = vector <VI> ;

class FenwickTree {
    VI sum;
public:
    FenwickTree (int treeSize) {
        sum = move(VI(treeSize+1));
    }

    void addVal(int idx, int val) {
        while (idx < sum.size()) {
            sum[idx] += val;
            idx += (idx & (-idx));
        }
    }

    int getVal(int idx) {
        if (idx <= 0) {
            return 0;
        }

        int ret = 0;

        while (idx) {
            ret += sum[idx];
            idx -= (idx & (-idx));
        }

        return ret;
    }

    int queryRange(int a, int b) {
        return getVal(b) - getVal(a-1);
    }
};

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        const int MAXV = 100010;
        int N;
        cin >> N;

        FenwickTree ft(MAXV);

        cout << "Case #" << tc << ":";

        for (int i = 0; i < N; ++i) {
            int v;
            cin >> v;
            ft.addVal(v, 1);

            int low = 1;
            int up = MAXV;
            int h = 1;

            while (low <= up) {
                int mid = (low + up) / 2;

                int sum = ft.queryRange(mid, MAXV);

                if (sum >= mid) {
                    h = mid;
                    low = mid+1;
                } else {
                    up = mid-1;
                }
            }

            cout << " " << h;
        }

        cout << endl;
    }

    return 0;
}
