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

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int K;
        cin >> N >> K;

        int expected = K;
        int ans = 0;

        for (int i = 0; i < N; ++i) {
            int v;
            cin >> v;

            if (expected == v) {
                --expected;
            } else {
                expected = K;
                if (v == K) {
                    --expected;
                }
            }

            if (expected == 0) {
                ++ans;
                expected = K;
            }
        }
        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
