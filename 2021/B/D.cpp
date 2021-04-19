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
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <iomanip>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;
using VVVI = vector <VVI>;
using VLL = vector <long long>;
using VVLL = vector <VLL>;
using VVVLL = vector <VVLL>;
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;
using VS = vector <string>;
using VC = vector <char>;

long long gcd(long long a, long long b) {
    return b ? gcd(b, a%b) : a;
}

int UPPER = 200005;

class SegmentTree {
    VLL gres;

    int sx;
    int ex;
    vector <SegmentTree *> children;

    inline void checkAndCreateChildren() {
        if (children.size() == 0) {
            int mid =  (sx + ex) / 2;

            children.emplace_back(new SegmentTree(sx, mid));
            children.emplace_back(new SegmentTree(mid, ex));
        }
    }
public:

    SegmentTree (int spaceSize) {
        sx = ex = 0;

        ex = 1;
        while (ex < spaceSize) {
            ex *= 2;
        }
    }

    SegmentTree (int psx, int pex) : sx(psx), ex(pex) {
    }

    void updateSegment(int x1, int x2, long long v) {
        if (x1 >= x2) {
            return ;
        }

        if (x1 == sx && x2 == ex) {
            if (gres.size()) {
                gres.push_back(gcd(v, gres.back()));
            } else {
                gres.push_back(v);
            }
            return ;
        }

        int mid =  (sx + ex) / 2;
        checkAndCreateChildren();

        if (x1 < mid) {
            children[0]->updateSegment(x1, min(x2, mid), v);
        }

        if (x2 > mid) {
            children[1]->updateSegment(max(x1, mid), x2, v);
        }
    }

    void removeSegment(int x1, int x2) {
        if (x1 >= x2) {
            return ;
        }

        if (x1 == sx && x2 == ex) {
            if (gres.size()) {
                gres.pop_back();
            }
            return ;
        }

        int mid =  (sx + ex) / 2;
        checkAndCreateChildren();

        if (x1 < mid) {
            children[0]->removeSegment(x1, min(x2, mid));
        }

        if (x2 > mid) {
            children[1]->removeSegment(max(x1, mid), x2);
        }
    }

    long long query(int x1, int x2) {
        if (x1 >= x2) {
            return 0;
        }

        if (x1 == sx && x2 == ex) {
            if (gres.size()) {
                return gres.back();
            } else {
                return 0;
            }
        }

        long long ret = gres.size() ? gres.back() : 0;
        int mid =  (sx + ex) / 2;
        checkAndCreateChildren();

        if (x1 < mid) {
            ret = gcd(ret, children[0]->query(x1, min(x2, mid)));
        }

        if (x2 > mid) {
            ret = gcd(ret, children[1]->query(max(x1, mid), x2));
        }

        return ret;
    }
};

void solve(const VVVLL& adja, const VVVLL& query, int now, VI& used, SegmentTree& st, VLL& ans) {
    used[now] = 1;

    for (int q = 0; q < query[now].size(); ++q) {
        int qnum = query[now][q][0];
        long long load = query[now][q][1];

        ans[qnum] = st.query(load, load+1);
    }

    for (int i = 0; i < adja[now].size(); ++i) {
        int nextv = adja[now][i][0];
        long long L = adja[now][i][1];
        long long A = adja[now][i][2];

        if (used[nextv] == 0) {
            st.updateSegment(L, UPPER, A);
            solve(adja, query, nextv, used, st, ans);
            st.removeSegment(L, UPPER);
        }
    }
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int Q;
        cin >> N >> Q;

        VVVLL adja(N);
        VVLL parent(N);
        VI used(N);

        for (int i = 1; i < N; ++i) {
            int X;
            int Y;
            long long L;
            long long A;

            cin >> X >> Y >> L >> A;
            --X;
            --Y;

            adja[X].push_back({Y, L, A});
            adja[Y].push_back({X, L, A});
        }

        VVVLL query(N);
        VLL ans(Q);
        SegmentTree st(UPPER+5000);

        for (int q = 0; q < Q; ++q) {
            int C;
            long long W;
            cin >> C >> W;
            --C;
            query[C].push_back({q, W});
        }

        solve(adja, query, 0, used, st, ans);

        cout << "Case #" << tc << ":" ;
        for (int q = 0; q < Q; ++q) {
            cout << " " << ans[q];
        }
        cout << endl;
    }

    return 0;
}
