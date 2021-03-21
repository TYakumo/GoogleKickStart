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

class UnionAndFind {
    public:
    vector <int> groupSize;
    vector <int> groupParent;

    UnionAndFind (int gSize) {
        groupSize = vector<int> (gSize, 1);
        groupParent = vector<int> (gSize, -1);
    }

    int findGroup(int n) {
        if (groupParent[n] == -1) {
            return n;
        }
        return groupParent[n] = findGroup(groupParent[n]);
    }

    void unionGroup(int x, int y) {
        y = findGroup(y);
        x = findGroup(x);

        if (x == y) {
            return ;
        }

        if (groupSize[x] > groupSize[y]) {
            swap(x, y);
        }

        groupSize[y] += groupSize[x];
        groupParent[x] = y;
    }
};

struct Edge {
    int f;
    int t;
    int w;

    Edge() {}
    Edge(int pf, int pt, int pw) : f(pf), t(pt), w(pw) {}

    bool operator<(const Edge& e) const {
        return w < e.w;
    }
};

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
        vector <Edge> edges;

        long long ans = 0;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> A[i][j];
            }
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> B[i][j];

                if (A[i][j] == -1) {
                    edges.push_back({i, j+N, -B[i][j]});
                    ans += B[i][j];
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            cin >> R[i];
        }

        for (int i = 0; i < N; ++i) {
            cin >> C[i];
        }

        sort(edges.begin(), edges.end());
        UnionAndFind ut(2*N);

        for (int i = 0; i < edges.size(); ++i) {
            int gf = ut.findGroup(edges[i].f);
            int gt = ut.findGroup(edges[i].t);

            if (gf != gt) {
                ans += edges[i].w;
                ut.unionGroup(gf, gt);
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
