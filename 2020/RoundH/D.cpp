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
    const int MAXC = 30;
    int TC;
    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int Q;
        cin >> N >> Q;

        VVI IG(N);
        VVI adja(MAXC, VI(MAXC));
        auto charToIdx = [](char ch) { return ch-'A'; };

        for (int i = 0; i < N; ++i) {
            string S;
            cin >> S;

            for (int j = 0; j < S.size(); ++j) {
                IG[i].push_back(charToIdx(S[j]));
            }

            for (int j = 0; j < S.size(); ++j) {
                for (int k = 0; k < S.size(); ++k) {
                    adja[charToIdx(S[j])][charToIdx(S[k])] = 1;
                }
            }
        }

        cout << "Case #" << tc << ":";

        while (Q--) {
            int f;
            int t;
            cin >> f >> t;
            --f;
            --t;

            const int INF = 100000;
            VI best(MAXC, INF);
            int ans = f == t ? 0 : INF;
            deque <int> que;

            for (int i = 0; i < IG[f].size(); ++i) {
                if (best[IG[f][i]] == INF) {
                    que.push_back(IG[f][i]);
                    best[IG[f][i]] = 0;
                }
            }

            while (!que.empty()) {
                int now = que.front();
                que.pop_front();

                for (int i = 0; i < MAXC; ++i) {
                    if (adja[now][i]) {
                        if (best[i] == INF) {
                            que.push_back(i);
                            best[i] = best[now]+1;
                        }
                    }
                }
            }

            for (int i = 0; i < IG[t].size(); ++i) {
                ans = min(ans, best[IG[t][i]]);
            }

            cout << " " << (ans == INF ? -1 : ans+2);
        }

        cout << endl;
    }

    return 0;
}
