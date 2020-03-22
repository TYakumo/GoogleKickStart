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
        int B;
        cin >> N >> B;

        vector <int> price(N);
        for (int i = 0; i < N; ++i) {
            cin >> price[i];
        }

        sort(price.begin(), price.end());

        int ans = 0;
        for (int i = 0; i < N; ++i) {
            if (B >= price[i]) {
                B -= price[i];
                ++ans;
            } else {
                break;
            }
        }

        cout << "Case #" << t << ": " << ans << endl;
    }

    return 0;
}