#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <sstream>
using namespace std;

using VLL = vector <long long>;
using VVLL = vector <VLL>;

long long solve(VVLL& dp, int now, int st, string v, long long small, int odd) {
    if (now == v.size()) {
        return 1;
    }

    if (dp[small][now] >= 0) {
        return dp[small][now];
    }

    long long ret = 0;
    int vd = v[now] - '0';
    int upper = small ? 9 : vd;
    for (int d = st; d <= upper; ++d) {
        if (odd && (d%2 != 0)) {
            ret += solve(dp, now+1, 0, v, small || (d < vd), odd^1);
        } else if (odd == 0 && (d%2 == 0)) {
            ret += solve(dp, now+1, 0, v, small || (d < vd), odd^1);
        }
    }

    return dp[small][now] = ret;
}

long long boring(long long v) {
    if (v <= 0) {
        return v;
    }

    stringstream ss;
    string str;

    ss << v;
    ss >> str;

    long long ret = 0;
    for (int d = 0; d < str.size(); ++d) {
        VVLL dp(2, VLL(20, -1));
        ret += solve(dp, d, 1, str, d > 0, 1);
    }

    return ret;
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        long long L;
        long long R;
        cin >> L >> R;

        cout << "Case #" << tc << ": " << (boring(R) - boring(L-1)) << endl;
    }

    return 0;
}
