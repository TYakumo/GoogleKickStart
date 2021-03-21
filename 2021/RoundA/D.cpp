#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <unordered_set>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using US = unordered_set<int>;
using VUS = vector <US>;

struct State {
    VUS RS;
    VUS CS;
    State () {}
    State (int N) {
        RS = VUS(N);
        CS = VUS(N);
    }

    bool done() {
        int N = RS.size();
        for (int i = 0; i < N; ++i) {
            if (RS[i].size() != 0 || CS[i].size() != 0) {
                return false;
            }
        }

        return true;
    }

    bool operator<(const State& s) const {
        int N = RS.size();
        for (int i = 0; i < N; ++i) {
            if (RS[i].size() < s.RS[i].size()) {
                return true;
            }

            if (CS[i].size() < s.CS[i].size()) {
                return true;
            }
        }
        return false;
    }
};

bool solve(State s) {
    int N = s.RS.size();
    while (true) {
        bool update = false;

        for (int i = 0; i < N; ++i) {
            if (s.RS[i].size() == 1) {
                int cnum = *s.RS[i].begin();
                s.RS[i].clear();
                update = true;
                s.CS[cnum].erase(s.CS[cnum].find(i));
            }
        }

        for (int i = 0; i < N; ++i) {
            if (s.CS[i].size() == 1) {
                int rnum = *s.CS[i].begin();
                s.CS[i].clear();

                update = true;
                s.RS[rnum].erase(s.RS[rnum].find(i));
            }
        }

        if (!update) {
            break;
        }
    }

    return s.done();
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;

        VVI A(N, VI(N));
        VVI B(N, VI(N));
        VI R(N);
        VI C(N);
        State s(N);

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> A[i][j];

                if (A[i][j] == -1) {
                    s.RS[i].insert(j);
                    s.CS[j].insert(i);
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> B[i][j];
            }
        }

        for (int i = 0; i < N; ++i) {
            cin >> R[i];
        }

        for (int i = 0; i < N; ++i) {
            cin >> C[i];
        }

        // fill in
        while (true) {
            bool update = false;

            for (int i = 0; i < N; ++i) {
                if (s.RS[i].size() == 1) {
                    int cnum = *s.RS[i].begin();
                    s.RS[i].clear();
                    update = true;
                    s.CS[cnum].erase(s.CS[cnum].find(i));
                }
            }

            for (int i = 0; i < N; ++i) {
                if (s.CS[i].size() == 1) {
                    int rnum = *s.CS[i].begin();
                    s.CS[i].clear();

                    update = true;
                    s.RS[rnum].erase(s.RS[rnum].find(i));
                }
            }

            if (!update) {
                break;
            }
        }

        VVI cand;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (s.RS[i].count(j) && s.CS[j].count(i)) {
                    cand.push_back({i, j});
                }
            }
        }

        int upper = 1<<cand.size();
        const long long INF = 1000000000LL * 1000000000LL;
        long long ans = INF;

        for (int st = 0; st < upper; ++st) {
            State news = s;
            long long cost = 0;

            for (int i = 0; i < cand.size(); ++i) {
                if (st & (1 << i)) {
                    int r = cand[i][0];
                    int c = cand[i][1];

                    news.RS[r].erase(news.RS[r].find(c));
                    news.CS[c].erase(news.CS[c].find(r));
                    cost += B[r][c];
                }
            }

            if (solve(news)) {
                ans = min(ans, cost);
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
