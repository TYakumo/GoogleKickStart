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

using VLL = vector <long long>;
using VD = vector <double>;
using VVD = vector <VD>;

int main()
{
    int TC;

    cin >> TC;
    cout.precision(9);

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;

        VLL val(N);
        VLL sum(N);
        VVD dp(N+1, VD(N+1));
        VD frontdp(N+1);
        VD reardp(N+1);

        for (int i = 0; i < N; ++i) {
            cin >> val[i];
            sum[i] = val[i];

            if (i) {
                sum[i] += sum[i-1];
            }
        }

        for (int l = 2; l <= N; ++l) {
            for (int i = 0; i+l <= N; ++i) {
                int j = i+l-1;
                double prob = 1.0 / (j-i);
                double rangeSum = i ? sum[j] - sum[i-1] : sum[j];
                double total = rangeSum * (j-i) + frontdp[i] + reardp[j];

                // for (int k = i; k < j; ++k) {
                //     // double total = dp[i][k] + dp[k+1][j] + rangeSum;
                //     dp[i][j] += total * prob;
                // }
                dp[i][j] += total * prob;
            }

            for (int i = 0; i < N; ++i) {
                int tj = i+l-1;
                // j = i+l-1, i = j-l+1
                int ti = i-l+1;
                frontdp[i] += dp[i][tj];

                if (ti >= 0) {
                    reardp[i] += dp[ti][i];
                }
            }
        }

        cout << fixed << "Case #" << tc << ": " << dp[0][N-1] << endl;
    }

    return 0;
}
