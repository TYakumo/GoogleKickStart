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
        cin >> N;

        VI X(N);
        VI Y(N);

        for (int i = 0; i < N; ++i) {
            cin >> X[i] >> Y[i];
        }

        long long ans = 0;
        sort(Y.begin(), Y.end());
        long long cho = Y[Y.size()/2];

        for (int i = 0; i < N; ++i) {
            ans += abs(Y[i]-cho);
        }

        sort(X.begin(), X.end());
        VI tmpX = X;
        for (int i = 0; i < N; ++i) {
            tmpX[i] -= i;
        }

        sort(tmpX.begin(), tmpX.end());
        cho = tmpX[tmpX.size()/2];

        for (int i = 0; i < N; ++i) {
            ans += abs(X[i]-(cho+i));
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
