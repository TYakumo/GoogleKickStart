#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int T;

    cin >> T;

    for (int t = 1; t <= T; ++t) {
        int N;
        int K;
        cin >> N >> K;

        vector <int> exercise(N);

        for (int i = 0; i < N; ++i) {
            cin >> exercise[i];
        }

        const int UPPER = 1000000000;
        int low = 1;
        int up = UPPER;
        int ans = UPPER;

        while (low <= up) {
            int mid = (low + up) / 2;
            int consume = 0;

            for (int i = 1; i < N; ++i) {
                if (exercise[i] - exercise[i-1] > mid) {
                    int dist = exercise[i] - exercise[i-1];
                    int mul = dist / mid;

                    if (dist % mid == 0) {
                        --mul;
                    }

                    consume += mul;
                }
            }

            if (consume <= K) {
                up = mid-1;
                ans = mid;
            } else {
                low = mid+1;
            }
        }


        cout << "Case #" << t << ": " << ans << endl;
    }

    return 0;
}