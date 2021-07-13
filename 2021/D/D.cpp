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

using VFT = vector <FenwickTree<long long>>;
using VVFT = vector <VFT>;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int Q;
        long long P;
        cin >> N >> Q >> P;

        VLL A(N);
        VFT precal(4, FenwickTree<long long>(N+5));

        for (int i = 0; i < N; ++i) {
            cin >> A[i];

            long long MP = A[i]%P;
            long long vval = A[i];
            long long mval = MP;

            for (int k = 0; k < 4; ++k) {
                long long diff = vval - mval;
                int cnt = 0;

                while (diff%P == 0 && diff) {
                    diff /= P;
                    ++cnt;
                }
                precal[k].addVal(i+1, cnt);
                vval *= A[i];
                mval *= MP;
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
                A[pos-1] = val;
                long long MP = val%P;
                long long vval = val;
                long long mval = MP;

                for (int k = 0; k < 4; ++k) {
                    long long diff = vval - mval;
                    int cnt = 0;

                    while (diff%P == 0 && diff) {
                        diff /= P;
                        ++cnt;
                    }

                    precal[k].addVal(pos, -precal[k].queryRange(pos, pos));
                    precal[k].addVal(pos, cnt);
                    vval *= val;
                    mval *= MP;
                }
            } else {
                long long S;
                long long L;
                long long R;
                cin >> S >> L >> R;
                cout << " " << precal[S-1].queryRange(L, R);
            }
        }
        cout << endl;
    }

    return 0;
}
