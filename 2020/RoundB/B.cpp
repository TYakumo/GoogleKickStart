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
        long long D;
        long long ans = 0;

        cin >> N >> D;

        vector <long long> X(N);

        for (int i = 0; i < N; ++i) {
            cin >> X[i];
        }

        long long low = 0;
        long long up = D;

        while (low <= up) {
            long long mid = (low+up) / 2;
            long long nowd = mid;

            for (int i = 0; i < N; ++i) {
                long long nextd = (nowd+X[i]-1) / X[i];
                nextd *= X[i];
                nowd = nextd;
            }

            if (nowd <= D) {
                ans = mid;
                low = mid+1;
            } else {
                up = mid-1;
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
