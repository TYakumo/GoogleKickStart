#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
using namespace std;

// mincost maxflow works for S all equal
struct Stone {
    int S;
    long long E;
    long long L;

    // swap i, j, k (multiple) in between (i ~ k follows the constraints)
    // diff = (Si-Sj) * Sigma Lk - Li * Sigma Sk + Lj * Sigma Sk + Lj * Si - Li * Sj
    // = (Si - Sj) * Sigma Lk + (Lj - Li) * Sigma Sk + (Lj * Si - Li * Sj)
    // if (Lj * Si - Li * Sj) > 0 => (Lj * Sk - Lk * Sj), keep swapping with no element in between (adjacent swap)
    // => generating better result
    // => it must follow the order Li * Sj >= Lj * Si for i < j
    bool operator<(const Stone& a) const {
        return L*a.S > a.L*S;
    }
};

using VLL = vector <long long>;
using VVLL = vector <VLL>;

int main() {
    int T;

    cin >> T;

    for (int t = 1; t <= T; ++t) {
        int N;
        cin >> N;

        vector <Stone> stones(N);
        int sum = 0;
        long long ans = 0;

        for (int i = 0; i < N; ++i) {
            cin >> stones[i].S >> stones[i].E >> stones[i].L;
            sum += stones[i].S;
        }

        sort(stones.begin(), stones.end());
        VVLL dp(2, VLL(sum+10, -1));

        dp[0][0] = dp[1][0] = 0;
        int tot = 0;

        for (int i = 0; i < N; ++i) {
            // dp[1] = dp[0];

            for (int j = 0; j <= tot; ++j) {
                // dp[i+1][j] = dp[i][j]; // no eatting
                if (dp[0][j] >= 0) {
                    long long plus = stones[i].E - stones[i].L * j;
                    int news = j + stones[i].S;

                    dp[1][news] = max(dp[1][news], dp[0][j] + plus);
                    ans = max(ans, dp[1][news]);
                }
            }

            dp[0] = dp[1];
            tot += stones[i].S;
        }

        cout << "Case #" << t << ": " << ans << endl;
    }

    return 0;
}