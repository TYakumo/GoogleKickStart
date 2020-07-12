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

using VI = vector <int>;
using VVI = vector <VI>;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int K;
        cin >> K;

        const int INF = 100000000;
        VVI dp(K+1, VI(4, INF));
        VI pitch(K);

        for (int i = 0; i < K; ++i) {
            cin >> pitch[i];
        }

        dp[0][0] = dp[0][1] = dp[0][2] = dp[0][3] = 0;

        for (int i = 1; i < K; ++i) {
            for (int a = 0; a < 4; ++a) {
                for (int b = 0; b < 4; ++b) {
                    int defy = 0;

                    if ((pitch[i] > pitch[i-1] && b <= a)
                        || (pitch[i] < pitch[i-1] && b >= a)
                        || (pitch[i] == pitch[i-1] && b != a)) {
                        defy = 1;
                    }

                    dp[i][b] = min(dp[i][b], dp[i-1][a] + defy);
                }
            }
        }

        int ans = INF;
        for (int p = 0; p < 4; ++p) {
            ans = min(ans, dp[K-1][p]);
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
