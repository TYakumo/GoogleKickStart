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
        int R;
        int C;
        cin >> R >> C;

        VVI graph(R, VI(C));
        VVI maxLeft(R, VI(C));
        VVI maxRight(R, VI(C));
        VVI maxUp(R, VI(C));
        VVI maxDown(R, VI(C));
        long long ans = 0;

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cin >> graph[i][j];
            }
        }

        for (int i = 0; i < R; ++i) {
            int now = 0;
            for (int j = 0; j < C; ++j) {
                if (graph[i][j]) {
                    if (i-1 >= 0) {
                        maxUp[i][j] = maxUp[i-1][j] + 1;
                    } else {
                        maxUp[i][j] = 1;
                    }
                    ++now;
                } else {
                    now = 0;
                }
                maxLeft[i][j] = now;
            }

            now = 0;
            for (int j = C-1; j >= 0; --j) {
                if (graph[i][j]) {
                    ++now;
                } else {
                    now = 0;
                }
                maxRight[i][j] = now;
            }
        }

        for (int i = R-1; i >= 0; --i) {
            for (int j = 0; j < C; ++j) {
                if (graph[i][j]) {
                    if (i+1 < R) {
                        maxDown[i][j] = maxDown[i+1][j] + 1;
                    } else {
                        maxDown[i][j] = 1;
                    }
                }
            }
        }

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                // up(long), right(short)
                if (maxUp[i][j] >= 4 && maxRight[i][j] >= 2) {
                    ans += min(maxUp[i][j]/2, maxRight[i][j]);
                    --ans;
                }

                // left, up
                if (maxLeft[i][j] >= 4 && maxUp[i][j] >= 2) {
                    ans += min(maxLeft[i][j]/2, maxUp[i][j]);
                    --ans;
                }

                // down, left
                if (maxDown[i][j] >= 4 && maxLeft[i][j] >= 2) {
                    ans += min(maxDown[i][j]/2, maxLeft[i][j]);
                    --ans;
                }

                // right, down
                if (maxRight[i][j] >= 4 && maxDown[i][j] >= 2) {
                    ans += min(maxRight[i][j]/2, maxDown[i][j]);
                    --ans;
                }

                // up(long), left(short)
                if (maxUp[i][j] >= 4 && maxLeft[i][j] >= 2) {
                    ans += min(maxUp[i][j]/2, maxLeft[i][j]);
                    --ans;
                }

                // right, up
                if (maxRight[i][j] >= 4 && maxUp[i][j] >= 2) {
                    ans += min(maxRight[i][j]/2, maxUp[i][j]);
                    --ans;
                }

                // down, left
                if (maxDown[i][j] >= 4 && maxRight[i][j] >= 2) {
                    ans += min(maxDown[i][j]/2, maxRight[i][j]);
                    --ans;
                }

                // left, down
                if (maxLeft[i][j] >= 4 && maxDown[i][j] >= 2) {
                    ans += min(maxLeft[i][j]/2, maxDown[i][j]);
                    --ans;
                }
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
