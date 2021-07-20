#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <iomanip>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using VVVLL = vector <VVLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;
using VS = vector <string>;
using VC = vector <char>;

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

inline long long powCnt(long long val, long long P) {
    long long ret = 0;
    while (val%P == 0 && val != 0) {
        ++ret;
        val /= P;
    }
    return ret;
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int Q;
        long long P;
        cin >> N >> Q >> P;

        FenwickTree<long long> ft(N+5);
        FenwickTree<long long> fts(N+5);
        FenwickTree<long long> ftd(N+5);
        FenwickTree<long long> ftdc(N+5);

        for (int i = 0; i < N; ++i) {
            long long val;
            cin >> val;

            long long MP = val%P;
            if (MP == val) {
                ftdc.addVal(i+1, 1);
                continue;
            }

            if (MP != 0) {
                long long diff = val-MP;
                ft.addVal(i+1, powCnt(diff, P));
                fts.addVal(i+1, powCnt(diff, P) + powCnt(val+MP, P) - 1);
            } else {
                ftd.addVal(i+1, powCnt(val, P));
                ftdc.addVal(i+1, 1);
            }
        }

        cout << "Case #" << tc << ":";
        for (int q = 0; q < Q; ++q) {
            int T;
            cin >> T;

            if (T == 1) {
                long long pos;
                long long val;
                cin >> pos >> val;
                long long MP = val%P;
                ft.addVal(pos, -ft.queryRange(pos, pos));
                fts.addVal(pos, -fts.queryRange(pos, pos));
                ftd.addVal(pos, -ftd.queryRange(pos, pos));
                ftdc.addVal(pos, -ftdc.queryRange(pos, pos));

                if (MP == val) {
                    ftdc.addVal(pos, 1);
                    continue;
                }

                if (MP != 0) {
                    long long diff = val-MP;
                    ft.addVal(pos, powCnt(diff, P));
                    fts.addVal(pos, powCnt(diff, P) + powCnt(val+MP, P) - 1);
                } else {
                    ftd.addVal(pos, powCnt(val, P));
                    ftdc.addVal(pos, 1);
                }
            } else {
                long long S;
                long long L;
                long long R;
                cin >> S >> L >> R;

                long long len = R-L+1;
                long long ans = ftd.queryRange(L, R)*S + (len - ftdc.queryRange(L, R))*powCnt(S, P);
                if (P == 2 && S%2 == 0) {
                    ans += fts.queryRange(L, R);
                } else {
                    ans += ft.queryRange(L, R);
                }

                cout << " " << ans;
            }
        }
        cout << endl;
    }

    return 0;
}
