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

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int K;
        string S;
        cin >> N >> K >> S;
        int score = 0;

        int hl = S.size()/2;
        for (int i = 0; i < hl; ++i) {
            if (S[i] != S[S.size()-1-i]) {
                ++score;
            }
        }

        cout << "Case #" << tc << ": " << abs(K-score) << endl;
    }

    return 0;
}
