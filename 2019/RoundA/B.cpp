#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <queue>
using namespace std;

int main() {
    int T;

    cin >> T;

    for (int t = 1; t <= T; ++t) {
        const int INF = 100000;
        int ans = INF;
        int R;
        int C;
        cin >> R >> C;

        vector <string> grid(R);
        for (int i = 0; i < R; ++i) {
            cin >> grid[i];
        }

        int low = 0;
        int up = R + C;

        while (low <= up) {
            int mid = (low+up) / 2;
            vector<vector <int>> dist(R, vector<int>(C, INF));
            vector<vector <int>> covered(R, vector<int>(C));

            deque < pair<int, int> > que;

            for (int i = 0; i < R; ++i) {
                for (int j = 0; j < C; ++j) {
                    if (grid[i][j] == '1') {
                        que.emplace_back(make_pair(i, j));
                        dist[i][j] = 0;
                    }
                }
            }

            // mark distance
            while (!que.empty()) {
                pair <int, int> now = que.front();
                que.pop_front();

                const int dr[] = {1, -1, 0, 0};
                const int dc[] = {0, 0, 1, -1};
                int newdist = dist[now.first][now.second] + 1;

                for (int dir = 0; dir < 4; ++dir) {
                    int nr = now.first + dr[dir];
                    int nc = now.second + dc[dir];

                    if (nr >= 0 && nr < R
                    && nc >= 0 && nc < C) {
                        if (newdist < dist[nr][nc]) {
                            dist[nr][nc] = newdist;
                            que.emplace_back(make_pair(nr, nc));
                        }
                    }
                }
            }

            // find not covered
            // abs(x1-x2) + abs(y1-y2)
            // = max(abs(x1+y1-x2-y2), abs(x1-y1-x2+y2))
            int maxxyp[2] = {-INF, -INF};
            int minxyp[2] = {INF, INF};

            for (int i = 0; i < R; ++i) {
                for (int j = 0; j < C; ++j) {
                    if (dist[i][j] > mid) {
                        maxxyp[0] = max(maxxyp[0], i+j);
                        minxyp[0] = min(minxyp[0], i+j);

                        maxxyp[1] = max(maxxyp[1], i-j);
                        minxyp[1] = min(minxyp[1], i-j);
                    }
                }
            }

            bool pass = false;
            for (int i = 0; i < R && !pass; ++i) {
                for (int j = 0; j < C; ++j) {
                    int maxDist = 0;

                    if (minxyp[0] != INF) {
                        maxDist = max(abs(i+j-maxxyp[0]), abs(i+j-minxyp[0]));
                    }

                    if (minxyp[1] != INF) {
                        maxDist = max(maxDist, abs(i-j-maxxyp[1]));
                        maxDist = max(maxDist, abs(i-j-minxyp[1]));
                    }

                    if (maxDist <= mid) {
                        pass = true;
                        break;
                    }
                }
            }

            if (pass) {
                ans = mid;
                up = mid-1;
            } else {
                low = mid+1;
            }
        }

        cout << "Case #" << t << ": " << ans << endl;
    }

    return 0;
}