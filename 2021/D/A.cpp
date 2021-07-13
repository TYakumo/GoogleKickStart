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
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;
using VS = vector <string>;
using VC = vector <char>;

bool progression(long long A, long long B, long long C) {
    return (B-A) == (C-B);
}

int main()
{
    int TC;
    cin >> TC;
    const int MAXN = 3;

    for (int tc = 1; tc <= TC; tc++) {
        VVLL A(MAXN, VLL(MAXN));
        UMLL needed;

        for (int i = 0; i < MAXN; ++i) {
            for (int j = 0; j < MAXN; ++j) {
                if (i == 1 && j == 1) {
                    continue;
                }
                cin >> A[i][j];
            }
        }

        // horizontal
        long long diff = A[1][2] - A[1][0];
        if (diff%2 == 0) {
            ++needed[A[1][0] + diff/2];
        }

        // vertical
        diff = A[2][1] - A[0][1];
        if (diff%2 == 0) {
            ++needed[A[0][1] + diff/2];
        }

        // diag 1
        diff = A[2][2] - A[0][0];
        if (diff%2 == 0) {
            ++needed[A[0][0] + diff/2];
        }

        // diag 2
        diff = A[2][0] - A[0][2];
        if (diff%2 == 0) {
            ++needed[A[0][2] + diff/2];
        }

        long long maxCnt = 0;
        long long bestVal = 0;
        auto iter = needed.begin();

        while (iter != needed.end()) {
            if (maxCnt < iter->second) {
                maxCnt = iter->second;
                bestVal = iter->first;
            }
            ++iter;
        }

        A[1][1] = bestVal;

        int ans = 0;

        for (int i = 0; i < MAXN; ++i) {
            ans += progression(A[i][0], A[i][1], A[i][2]);
            ans += progression(A[0][i], A[1][i], A[2][i]);
        }

        ans += progression(A[0][0], A[1][1], A[2][2]);
        ans += progression(A[0][2], A[1][1], A[2][0]);

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
