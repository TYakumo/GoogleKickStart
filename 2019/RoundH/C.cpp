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
        const int MAXN = 9;
        const int MOD = 11;
        const int UPPER = 10;
        VI A(MAXN);
        VI B(MAXN);

        for (int i = 0; i < MAXN; ++i) {
            cin >> A[i];
            A[i] = min(8 * UPPER + (A[i]%2), A[i]); // one kind = sigma other kinds, UPPER * 8
        }

        B = A;
        sort(B.begin(), B.end(), greater<int>());

        // for (B-A) * x = r mod 11, where 0 <= r < 11 and B > A
        // because gcd(B-A, 11) = 1, 10 >= x >= 0 is getting all answers, upper = 10
        // x can be 10, 8, 6, ... , -6, -8, -10, notice -10 = 1 mod 11
        bool flag = false;

        if (B[0] >= UPPER && B[1] >= UPPER) {
            flag = true;
        } else {
            int cnt = 0;
            int sum = 0;

            // finding sigma (2 * val) - sum mod 11 = 0
            for (int i = 0; i < MAXN; ++i) {
                cnt += A[i];
                sum += A[i] * (i+1);
            }

            int targetCnt = (cnt+1)/2;

            VVI dp1(targetCnt+1, VI(MOD));
            VVI dp2(targetCnt+1, VI(MOD));
            int maxCnt = 0;
            dp1[0][(MOD-sum%MOD)%MOD] = 1;

            for (int n = 0; n < MAXN; ++n) {
                int newMaxCnt = min(maxCnt + A[n], targetCnt);
                dp2 = dp1;

                for (int num = maxCnt; num >= 0; --num) {
                    for (int v = 0; v < MOD; ++v) {
                        if (dp1[num][v] == 0) {
                            continue;
                        }

                        for (int i = A[n]; i >= 0; --i) {
                            int plus = i*(n+1)*2;
                            int newVal = (v + plus) % MOD;
                            if (num + i <= targetCnt) {
                                dp2[num+i][newVal] = 1;
                            }
                        }
                    }
                }

                dp1 = dp2;
                maxCnt = newMaxCnt;
            }

            if (dp1[targetCnt][0]) {
                flag = true;
            }
        }

        cout << "Case #" << tc << ": " << (flag ? "YES" : "NO") << endl;
    }

    return 0;
}
