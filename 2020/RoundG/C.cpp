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
#include <unordered_set>
using namespace std;

using VLL = vector <long long>;
using VI = vector <int>;
using UM = unordered_map <int, long long>;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int W;
        long long N;

        cin >> W >> N;

        VLL X(W);
        VLL cand;
        UM toInc;
        UM toDec;

        // for v > Xi
        // min (v-Xi, N-v+xi)
        // N-v+Xi <= v-Xi
        // N-2v <= 2*Xi
        // N <= 2*(Xi+v), around N/2

        int CHN = (N+1)/2;
        for (int i = 0; i < W; ++i) {
            cin >> X[i];
            --X[i];
            cand.push_back(X[i]);
            cand.push_back((X[i]+CHN)%N);

            ++toInc[X[i]];
            ++toDec[(X[i]+CHN)%N];
        }

        const long long INF = 1000000000000000000LL;
        long long ans = INF;
        sort(cand.begin(), cand.end());
        sort(X.begin(), X.end());

        long long res = 0;
        long long incGroup = 0;
        long long decGroup = 0;

        auto getDist = [&N] (long long a, long long b) {
            long long large = max(a, b);
            long long small = min(a, b);
            return min(large-small, N-large+small);
        };

        auto isIncGroup = [&N, &getDist](long long a, long long b) {
            return getDist((a+1)%N, b) >= getDist(a, b);
        };

        for (int i = 0; i < 1; ++i) {
            for (int j = 0; j < X.size(); ++j) {
                if (isIncGroup(cand[i], X[j])) {
                    ++incGroup;
                } else {
                    ++decGroup;
                }
                res += getDist(cand[i], X[j]);
            }

            ans = min(ans, res);
        }

        long long prev = cand[0];

        for (int i = 1; i < cand.size(); ++i) {
            if (cand[i] == cand[i-1]) {
                continue;
            }

            int xpos = cand[i];
            res += incGroup * (xpos - prev);
            res -= decGroup * (xpos - prev);

            // update groupgs
            if (toInc.find(xpos) != toInc.end()) {
                decGroup -= toInc[xpos];
                incGroup += toInc[xpos];
            }

            if (toDec.find(xpos) != toDec.end()) {
                if (N%2 == 1) {
                    res -= toDec[xpos];
                }

                incGroup -= toDec[xpos];
                decGroup += toDec[xpos];
            }

            ans = min(ans, res);
            prev = xpos;
        }


        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
