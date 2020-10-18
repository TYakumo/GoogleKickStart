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

using VLL = vector <long long>;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        string S;

        cin >> S;

        long long ans = 0;
        VLL kick;
        VLL start;

        for (int i = 0; i < S.size(); ++i) {
            if (i+4 <= S.size() && S.substr(i, 4) == "KICK") {
                kick.push_back(i);
            }

            if (i+5 <= S.size() && S.substr(i, 5) == "START") {
                start.push_back(i);
            }
        }

        int now = 0;
        for (int i = 0; i < kick.size(); ++i) {
            while (now < start.size() && kick[i] + 3 >= start[now]) {
                ++now;
            }

            ans += (start.size()-now);
        }


        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}
