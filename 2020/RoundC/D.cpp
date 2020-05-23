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

using VLL = vector <long long> ;
using VVLL = vector <VLL> ;

class FenwickTree {
    VLL sum;
public:
    FenwickTree (int treeSize) {
        sum = move(VLL(treeSize+1));
    }

    void addVal(int idx, long long val) {
        while (idx < sum.size()) {
            sum[idx] += val;
            idx += (idx & (-idx));
        }
    }

    long long getVal(int idx) {
        if (idx <= 0) {
            return 0;
        }

        long long ret = 0;

        while (idx) {
            ret += sum[idx];
            idx -= (idx & (-idx));
        }

        return ret;
    }

    long long queryRange(int a, int b) {
        return getVal(b) - getVal(a-1);
    }
};

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int Q;
        cin >> N >> Q;

        FenwickTree ftel(N);
        FenwickTree ftol(N);
        FenwickTree fte(N);
        FenwickTree fto(N);

        for (int i = 0; i < N; ++i) {
            int v;
            cin >> v;
            FenwickTree *ftl = nullptr;
            FenwickTree *ft = nullptr;

            if (i&1) {
                ftl = &ftol;
                ft = &fto;
            } else {
                ftl = &ftel;
                ft = &fte;
            }

            ftl->addVal(i+1, v*(i+1));
            ft->addVal(i+1, v);
        }

        long long ans = 0;

        for (int q = 0; q < Q; ++q) {
            char ch;
            int f;
            int t;
            cin >> ch >> f >> t;

            if (ch == 'Q') {
                int oddSign = 1;
                int evenSign = 1;

                if ((f-1)&1) {
                    evenSign = -1;
                } else {
                    oddSign = -1;
                }

                ans += (ftol.queryRange(f, t) - fto.queryRange(f, t)*(f-1)) * oddSign;
                ans += (ftel.queryRange(f, t) - fte.queryRange(f, t)*(f-1)) * evenSign;
            } else {
                FenwickTree *ftl = nullptr;
                FenwickTree *ft = nullptr;

                if ((f-1)&1) {
                    ftl = &ftol;
                    ft = &fto;
                } else {
                    ftl = &ftel;
                    ft = &fte;
                }

                long long val = ft->queryRange(f, f);

                ftl->addVal(f, -val*f);
                ft->addVal(f, -val);

                ftl->addVal(f, f*t);
                ft->addVal(f, t);
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
