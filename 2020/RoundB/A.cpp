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
        int peak = 0;
        cin >> N;

        vector <int> h(N);

        for (int i = 0; i < N; ++i) {
            cin >> h[i];
        }

        for (int i = 1; i < N-1; ++i) {
            if (h[i-1] < h[i] && h[i+1] < h[i]) {
                ++peak;
            }
        }

        cout << "Case #" << tc << ": " << peak << endl;
    }

    return 0;
}
