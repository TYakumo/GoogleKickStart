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
        cin >> N;

        int ans = 0;
        vector <int> val(N);

        for (int i = 0; i < N; ++i) {
            cin >> val[i];
        }

        int preMax = -1;
        for (int i = 0; i < N; ++i) {
            int nextVal = i+1 < N ? val[i+1] : -1;

            if (val[i] > preMax && val[i] > nextVal) {
                ++ans;
            }

            preMax = max(preMax, val[i]);
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
