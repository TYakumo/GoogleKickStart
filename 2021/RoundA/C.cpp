#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <queue>
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

        VVI G(R, VI(C));
        VVI cand;

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cin >> G[i][j];
                cand.push_back({-G[i][j], i, j});
            }
        }

        // init
        VVI NG = G;
        sort(cand.begin(), cand.end());

        VVI inQue(R, VI(C, 1));
        deque <pair<int, int>> que;

        for (int i = 0; i < cand.size(); ++i) {
            que.push_back({cand[i][1], cand[i][2]});
        }

        while (!que.empty()) {
            pair <int, int> now = que.front();
            que.pop_front();
            inQue[now.first][now.second] = 0;

            const int dr[] = {1, -1, 0, 0};
            const int dc[] = {0, 0, 1, -1};
            for (int dir = 0; dir < 4; ++dir) {
                int newr = now.first + dr[dir];
                int newc = now.second + dc[dir];

                if (newr >= 0 && newr < R
                && newc >= 0 && newc < C) {
                    if (NG[newr][newc]+1 < NG[now.first][now.second]) {
                        NG[newr][newc] = NG[now.first][now.second]-1;
                        if (inQue[newr][newc] == 0) {
                            que.push_back({newr, newc});
                        }
                    }
                }
            }
        }

        long long ans = 0;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                ans += NG[i][j] - G[i][j];
            }
        }


        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
