#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <unordered_map>
using namespace std;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;
        vector <int> val(N);

        // max => 10^5 * 100 => 10^7 => sqrt(10^7) <= 4000

        // prefixSum' - prefixSum => perfect square
        // prefixSum' => perfect square + prefixSum
        int prefixSum = 0;
        int SHIFT = N*100;
        int UPPER = N*100 + SHIFT;

        vector <int> cnt(UPPER);

        for (int v = 0; v*v+SHIFT <= UPPER; ++v) {
            cnt[v*v + SHIFT] = 1;
        }

        long long ans = 0;

        for (int i = 0; i < N; ++i) {
            cin >> val[i];
            prefixSum += val[i];
            ans += cnt[prefixSum + SHIFT];

            for (int v = 0; v*v+prefixSum+SHIFT <= UPPER; ++v) {
                ++cnt[v*v+prefixSum + SHIFT];
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
