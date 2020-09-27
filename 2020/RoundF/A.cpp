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
        int X;
        cin >> N >> X;

        VVI info;
        VI order(N);

        for (int i = 0; i < N; ++i) {
            int A;
            cin >> A;

            info.push_back({(A+X-1)/X, i});
        }

        sort(info.begin(), info.end());

        for (int i = 0; i < info.size(); ++i) {
            order[i] = info[i][1]+1;
        }

        cout << "Case #" << tc << ":" ;
        for (int i = 0; i < order.size(); ++i) {
            cout << " " << order[i];
        }
        cout << endl;

    }

    return 0;
}
