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

using VLL = vector <long long>;
using VVLL = vector < VLL >;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;

        VVLL coin(N, VLL(N));

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> coin[i][j];
            }
        }

        long long ans = 0;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (coin[i][j] >= 0) {
                    long long res = 0;
                    int r = i;
                    int c = j;

                    while (r < N && c < N) {
                        res += coin[r][c];
                        coin[r][c] = -1;
                        ++r;
                        ++c;
                    }

                    ans = max(ans, res);
                }
            }
        }


        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
