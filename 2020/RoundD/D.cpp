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
        int Q;
        cin >> N >> Q;

        VI b(N);

        for (int i = 0; i < N-1; ++i) {
            cin >> b[i];
        }

        cout << "Case #" << tc << ":";
        const int INF = 10000010;

        for (int q = 0; q < Q; ++q) {
            int K;
            int S;
            cin >> S >> K;

            int now = --S;
            int left = S-1;
            int right = S+1;

            for (int k = 1; k < K; ++k) {
                int leftD = INF;
                int rightD = INF;

                if (left >= 0) {
                    leftD = b[left];
                }

                if (right < N) {
                    rightD = b[right-1];
                }

                if (leftD < rightD) {
                    now = left;
                    --left;
                } else {
                    now = right;
                    ++right;
                }
            }

            cout << " " << now+1 ;
        }

        cout << endl;
    }

    return 0;
}
