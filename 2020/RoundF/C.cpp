#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <unordered_map>
using namespace std;

using UMI = unordered_map <long long, int>;
using VI = vector <int>;
using VVI = vector <UMI>;
using VVVI = vector <VVI>;
using VVVVI = vector <VVVI>;
const int INF = 10000;

inline int coorToNum(int r, int c) {
    return r*r + c;
}

int solve(VVVVI& dp, int S, int RA, int CA, int RB, int CB, int turn, long long st) {
    int S1 = coorToNum(RA, CA);
    int S2 = coorToNum(RB, CB);

    if (dp[turn][S1][S2].find(st) != dp[turn][S1][S2].end()) {
        return dp[turn][S1][S2][st];
    }

    const int dr[] = {1, 0, 0};
    const int dc[] = {1, 1, -1};
    dp[turn][S1][S2][st] = 0;
    int ret = turn == 0 ? -INF : INF;

    int nowR = turn == 0 ? RA : RB;
    int nowC = turn == 0 ? CA : CB;
    bool noMove = true;

    for (int dir = 0; dir < 3; ++dir) {
        int newr = nowR + dr[dir] * (nowC%2 == 1 ? -1 : 1);
        int newc = nowC + dc[dir] * (dir == 0 && nowC%2 == 1 ? -1 : 1);
        long long news = 1LL << coorToNum(newr, newc);
        int CMAX = (newr+1) * 2 - 1;

        if (newr < S && newr >= 0
        && newc < CMAX && newc >= 0
        && (news & st) == 0) {
            noMove = false;
            if (turn == 0) { // max
                ret = max(ret, solve(dp, S, newr, newc, RB, CB, turn^1, st|news)+1);
            } else { // min
                ret = min(ret, solve(dp, S, RA, CA, newr, newc, turn^1, st|news)-1);
            }
        }
    }

    if (noMove) {
        dp[turn][S1][S2][st] = solve(dp, S, RA, CA, RB, CB, turn^1, st);
    } else {
        dp[turn][S1][S2][st] = ret;
    }

    return dp[turn][S1][S2][st];
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        // #T = S * (S+1) / 2 + (S-1) * S / 2 = S*S => S3 = 6+3 = 9, S6 = 36
        // 36*36*2^36
        int S;
        int RA;
        int CA;
        int RB;
        int CB;
        int C;

        cin >> S >> RA >> CA >> RB >> CB >> C;

        int tot = S*S;
        VVVVI dp(2, VVVI(tot, VVI(tot)));
        long long initSt = 0;

        for (int i = 0; i < C; ++i) {
            int r;
            int c;
            cin >> r >> c;

            initSt |= 1LL << coorToNum(r-1, c-1);
        }

        initSt |= 1LL << coorToNum(RA-1, CA-1);
        initSt |= 1LL << coorToNum(RB-1, CB-1);

        cout << "Case #" << tc << ": " << solve(dp, S, RA-1, CA-1, RB-1, CB-1, 0, initSt) << endl;
    }

    return 0;
}
