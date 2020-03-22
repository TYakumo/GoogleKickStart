#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int T;

    cin >> T;

    for (int t = 1; t <= T; ++t) {
        int N;
        int K;
        int P;

        const int INF = 100000000;

        cin >> N >> K >> P;
        vector<vector <int>> dp(N+1, vector<int>(P+1, -INF));

        dp[0][0] = 0;

        for (int i = 0; i < N; ++i) {
            int upper = min(i*K, P-1);
            vector <int> choice(K);

            for (int j = 0; j < K; ++j) {
                cin >> choice[j];
            }

            int beauti = 0;

            // no choice from this stack
            dp[i+1] = dp[i];

            for (int c = 1; c <= K; ++c) {
                beauti += choice[c-1];

                for (int j = 0; j <= upper && j+c <= P; ++j) {
                    if (dp[i][j] >= 0) {
                        dp[i+1][j+c] = max(dp[i+1][j+c], dp[i][j] + beauti);
                    }
                }
            }
        }

        cout << "Case #" << t << ": " << dp[N][P] << endl;
    }

    return 0;
}