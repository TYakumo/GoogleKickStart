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
        int N;
        int K;

        cin >> N >> K;

        VVI times;

        for (int i = 0; i < N; ++i) {
            int f;
            int t;
            cin >> f >> t;

            times.push_back({f, t});
        }

        sort(times.begin(), times.end());
        int ans = 0;
        int endTime = -1;

        for (int i = 0; i < times.size(); ++i) {
            if (endTime < times[i][1]) {
                int deployTime = max(times[i][0], endTime);
                int timeLength = times[i][1] - deployTime;
                int needed = (timeLength + K - 1) / K;

                ans += needed;
                endTime = deployTime + needed*K;
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
