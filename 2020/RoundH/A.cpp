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
        int S;
        int K;
        cin >> N >> K >> S;

        int ans = (K-1) + min(N-S+1 + abs(K-S), N+1);


        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
