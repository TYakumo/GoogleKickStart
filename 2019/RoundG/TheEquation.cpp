#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    int T;

    cin >> T;

    for (int t = 1; t <= T; ++t) {
        long long N;
        long long M;

        cin >> N >> M;

        vector <long long> val(N);

        for (int i = 0; i < N; ++i) {
            cin >> val[i];
        }

        long long K = 0;
        const int BITMAX = 50;
        vector< vector <long long> > cost(BITMAX+1, vector<long long>(2));
        vector <long long> mincost(BITMAX+1);

        for (int b = BITMAX; b >= 0; --b) {
            long long bit = 1LL << b;

            long long acc[2] = {0, 0};

            for (int i = 0; i < val.size(); ++i) {
                acc[0] += (bit & val[i]);
                acc[1] += ((bit & val[i]) ^ bit);
            }

            cost[b][0] = acc[0];
            cost[b][1] = acc[1];
            mincost[b] = min(acc[0], acc[1]);
        }

        for (int i = 1; i <= BITMAX; ++i) {
            mincost[i] += mincost[i-1];
        }

        long long acc = 0;

        for (int b = BITMAX; b >= 0; --b) {
            long long bit = 1LL << b;
            long long nextMin = b ? mincost[b-1] : 0;

            if (acc + cost[b][1] + nextMin <= M) {
                K |= bit;
                acc += cost[b][1];
            } else {
                acc += cost[b][0];
            }
        }

        cout << "Case #" << t << ": " << (acc > M ? -1 : K) << endl;
    }

    return 0;
}