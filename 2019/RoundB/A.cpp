#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
using namespace std;

int main() {
    int T;

    cin >> T;

    for (int t = 1; t <= T; ++t) {
        int N;
        int Q;
        cin >> N >> Q;

        string s;
        cin >> s;
        vector< vector <int> > vCnt(N+1, vector<int>(26));

        for (int i = 1; i <= N; ++i) {
            vCnt[i] = vCnt[i-1];
            ++vCnt[i][s[i-1]-'A'];
        }

        int ans = 0;

        for (int q = 0; q < Q; ++q) {
            int L;
            int R;
            cin >> L >> R;

            vector <int> acc = vCnt[R];
            int evenOddCnt[2] = {0, 0};

            for (int i = 0; i < 26; ++i) {
                acc[i] -= vCnt[L-1][i];
                ++evenOddCnt[acc[i]%2];
            }

            if (evenOddCnt[1] <= 1) {
                ++ans;
            }
        }

        cout << "Case #" << t << ": " << ans << endl;
    }

    return 0;
}