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
        cin >> N;
        string S;
        cin >> S;
        VI dp(N);

        dp[0] = 1;

        cout << "Case #" << tc << ": " << 1;

        for (int i = 1; i < N; ++i) {
            dp[i] = 1;

            if (S[i] > S[i-1]) {
                dp[i] += dp[i-1];
            }
            cout << " " << dp[i];
        }
        cout << endl;
    }

    return 0;
}
