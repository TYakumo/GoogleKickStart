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

using VI = vector<int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;

void colorV(int now, VI& colors, VVVI& adja, int& black, int& tot) {
    if (black < 0) { // invalid
        return ;
    }

    ++tot;

    for (int a = 0; a < 2; ++a) {
        for (int i = 0; i < adja[a][now].size(); ++i) {
            int nextv = adja[a][now][i];
            if (colors[nextv] == -1) {
                colors[nextv] = colors[now]^a;
                colorV(nextv, colors, adja, black, tot);
                black += colors[nextv];
            } else if (colors[nextv] != (colors[now]^a)) {
                black = -1;
                return ;
            }
        }
    }
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;

        vector <string> graph(N);

        for (int i = 0; i < N; ++i) {
            cin >> graph[i];
        }

        int V = 2*N-1;
        VVVI adja(2, VVI(V*2));

        auto getLv = [&N](int r, int c) {
            return (r-c) + (N-1);
        };

        auto getRv = [&V](int r, int c) {
            return r+c + V;
        };

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                int lv = getLv(r, c);
                int rv = getRv(r, c);

                if (graph[r][c] != '#') {
                    adja[1][lv].push_back(rv);
                    adja[1][rv].push_back(lv);
                } else {
                    adja[0][rv].push_back(lv);
                    adja[0][lv].push_back(rv);
                }
            }
        }

        VI colors(2*V, -1);
        int ans = 0;
        for (int v = 0; v < V; ++v) {
            if (colors[v] == -1) {
                int res = 0;
                int tot = 0;
                colors[v] = 0;
                colorV(v, colors, adja, res, tot);
                ans += min(res, tot-res);
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
