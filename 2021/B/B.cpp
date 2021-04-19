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

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int ans = 2;
        cin >> N;

        VI A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }

        VI dp(N);

        dp[N-1] = 1;
        dp[N-2] = 2;
        for (int i = N-3; i >= 0; --i) {

            dp[i] = 2;
            // no change
            if (A[i+1] - A[i] == A[i+2] - A[i+1]) {
                dp[i] = max(dp[i], dp[i+1]+1);
            }
        }

        for (int i = 0; i < N-1; ++i) {
            int np = i+dp[i];
            int delta = A[i+1] - A[i];

            ans = max(ans, dp[i]);
            if (np < N) {
                ans = max(ans, dp[i] + 1);
            }

            if (i >= 1) {
                ans = max(ans, dp[i] + 1);
            }

            if (i >= 2 && A[i-2]+2*delta == A[i]) {
                ans = max(ans, dp[i] + 2);
            }

            if (np < N-1) {
                int td = A[np+1] - A[np-1];
                if (td == 2*delta) { // OK
                    ans = max(ans, dp[i] + 2);

                    if (np+2 < N && A[np+2]-A[np+1] == delta) {
                        ans = max(ans, dp[i] + 1 + dp[np+1]);
                    }
                }
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
