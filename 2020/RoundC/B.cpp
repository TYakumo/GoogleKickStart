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

const int MAXST = 1<<26;
vector <int> searched(MAXST);
string ans;

void solve(string str, vector <string>& poly, int st, int finSt) {
    if (ans != "") {
        return ;
    }

    if (st == finSt) {
        ans = str;
        return ;
    }

    if (searched[st]) {
        return ;
    }

    searched[st] = 1;

    for (int i = 0; i < 26; ++i) {
        int cho = 1<<i;
        if (cho&finSt && (cho&st) == 0) {
            // checking
            char ch = i+'A';

            bool pass = true;
            int R = poly.size();
            int C = poly[0].size();

            for (int r = 0; r < R && pass; ++r) {
                for (int c = 0; c < C; ++c) {
                    if (poly[r][c] == ch) {
                        if (r+1 < R) {
                            char bCh = poly[r+1][c];
                            int bSt = 1<<(poly[r+1][c]-'A');
                            if (bCh != ch && (bSt&st) == 0) {
                                pass = false;
                                break;
                            }
                        }
                    }
                }
            }

            if (pass) {
                solve(str+ch, poly, st|cho, finSt);
            }
        }
    }
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int R;
        int C;
        cin >> R >> C;

        vector <string> poly(R);
        int finSt = 0;
        for (int i = 0; i < R; ++i) {
            cin >> poly[i];
            for (int j = 0; j < C; ++j) {
                finSt |= 1<<(poly[i][j] - 'A');
            }
        }

        ans = "";
        fill(searched.begin(), searched.end(), 0);
        solve("", poly, 0, finSt);

        if (ans.size()) {
            cout << "Case #" << tc << ": " << ans << endl;
        } else {
            cout << "Case #" << tc << ": -1" << endl;
        }

    }

    return 0;
}
