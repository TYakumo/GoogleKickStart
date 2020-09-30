#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <iomanip>
using namespace std;

using VI = vector <int>;
using MVID = map <VI, double> ;

double solve(MVID& dp, const VI& target, VI st) {
    if (dp.find(st) != dp.end()) {
        return dp[st];
    }

    if (target == st) {
        return 0;
    }

    double ret = 1.0;
    double coeff = 1.0;
    double prob = 1.0 / st.size();
    VI news(st);

    for (int i = 0; i < st.size();) {
        int ends = i;
        while (ends < st.size() && st[ends] == st[i]) {
            ++ends;
        }

        double newprob = prob * (ends - i);
        news[i] = min(news[i]+1, target[i]);

        if (news[i] == st[i]) { // hitting cap
            coeff -= newprob;
        } else {
            ret += solve(dp, target, news) * newprob;
        }

        news[i] = st[i]; // restore
        i = ends;
    }

    dp[st] = ret / coeff;
    return ret / coeff;
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int M;
        int K;

        cin >> N >> M >> K;

        VI needed(M);
        MVID dp;

        for (int i = 0; i < K; ++i) {
            cin >> needed[i];
        }

        sort(needed.begin(), needed.end(), greater<int>());
        cout << fixed << setprecision(14) << "Case #" << tc << ": " << solve(dp, needed, VI(M)) << endl;
    }

    return 0;
}
