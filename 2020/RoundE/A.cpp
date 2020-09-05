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

using VI = vector<int>;
using VVI = vector <VI>;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;

        VI A(N);
        VI dp(N);

        for (int i = 0; i < N; ++i) {
            cin >> A[i];
            dp[i] = i;
        }

        for (int l = 0; (1<<l) < N; ++l) {
            VI newdp = dp;

            for (int i = 0; i < N; ++i) {
                int j = dp[i]+1;

                if (j < N) {
                    if (A[j]-A[j-1] == A[i+1] - A[i]) {
                        newdp[i] = max(newdp[i], j);

                        if (j+1 < N) {
                            if (A[j+1]-A[j] == A[i+1]-A[i]) {
                                newdp[i] = max(newdp[i], dp[j]);
                            }
                        }
                    }
                }
            }

            dp = newdp;
        }

        int ans = 0;
        for (int i = 0; i < N; ++i) {
            ans = max(ans, dp[i]-i+1);
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
