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
        VI targetLen(2);
        cin >> N >> targetLen[0] >> targetLen[1];

        const int MAXL = 22;
        VI p(N, -1);
        VVI targetParent(2, VI(N, -1));
        VVI child(N);
        VVI accTargetCnt(2, VI(N));
        VVI parent(N, VI(MAXL, -1));

        deque <int> que;
        que.push_back(0);

        for (int i = 1; i < N; ++i) {
            cin >> p[i];
            parent[i][0] = --p[i];
            child[p[i]].push_back(i);
        }

        for (int l = 1; l < MAXL; ++l) {
            for (int i = 0; i < N; ++i) {
                if (parent[i][l-1] != -1) {
                    parent[i][l] = parent[parent[i][l-1]][l-1];
                }
            }
        }

        double ans = 0;

        for (int i = 0; i < 2; ++i) {
            for (int c = 0; c < N; ++c) {
                int nowp = c;

                for (int l = 0; l < MAXL; ++l) {
                    if ((1<<l) & targetLen[i]) {
                        nowp = parent[nowp][l];

                        if (nowp == -1) {
                            break;
                        }
                    }
                }

                if (nowp != -1) {
                    ++accTargetCnt[i][nowp];
                    targetParent[i][c] = nowp;
                }
            }
        }

        // calculate accTargetCnt
        for (int i = 0; i < que.size(); ++i) {
            int now = que[i];

            for (int j = 0; j < child[now].size(); ++j) {
                que.push_back(child[now][j]);
            }
        }

        while (!que.empty()) {
            int now = que.back();
            que.pop_back();

            for (int i = 0; i < 2; ++i) {
                int tp = targetParent[i][now];

                if (tp != -1) {
                    accTargetCnt[i][tp] += accTargetCnt[i][now];
                }
            }
        }

        // bayesian
        for (int i = 0; i < N; ++i) {
            double left = (accTargetCnt[0][i] + 1) / (double)N;
            double right = (accTargetCnt[1][i] + 1) / (double)N;

            ans += left + right - left*right;
        }

        cout.precision(10);
        cout << std::fixed << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
