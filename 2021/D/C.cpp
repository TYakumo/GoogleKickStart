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
using UMI = unordered_map<int, int>;
using UMLL = unordered_map<long long, long long>;
using VS = vector <string>;
using VC = vector <char>;


using MLL = map <long long, long long>;

inline long long bestDist(MLL::iterator iter, long long v) {
    if (v >= iter->first && v <= iter->second) {
        return 0;
    } else if (v >= iter->second) {
        return abs(v-iter->second);
    }
    return abs(v-iter->first);
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int M;
        cin >> N >> M;

        VVLL A(N, VLL(2));
        VLL ans(M);
        MLL smap;

        for (int i = 0; i < N; ++i) {
            cin >> A[i][0] >> A[i][1];
            smap[A[i][0]] = A[i][1];
        }

        VVLL S(M, VLL(2));

        for (int i = 0; i < M; ++i) {
            cin >> S[i][0];
            S[i][1] = i;
        }

        for (int i = 0; i < S.size(); ++i) {
            if (smap.empty()) {
                break;
            }

            auto iter = smap.lower_bound(S[i][0]);
            auto iter2 = iter;

            if (iter2 == smap.begin()) {
                iter2 = smap.end();
            } else {
                --iter2;
            }

            int cho = iter == smap.end() ? 1 : 0;

            if (cho == 0) {
                // compare iter2
                if (iter2 != smap.end()) {
                    if (bestDist(iter2, S[i][0]) <= bestDist(iter, S[i][0])) {
                        cho = 1;
                        iter = iter2;
                    }
                }
            } else {
                iter = iter2;
            }

            if (iter->first >= S[i][0]) {
                long long from = iter->first+1;
                long long to = iter->second;
                smap.erase(smap.find(iter->first));
                long long diff = abs(iter->first - S[i][0]);
                ans[S[i][1]] = iter->first;

                if (from <= to) {
                    smap[from] = to;
                }
            } else if (iter->second <= S[i][0]) {
                long long from = iter->first;
                long long to = iter->second-1;
                smap.erase(smap.find(iter->first));
                long long diff = abs(iter->second - S[i][0]);
                ans[S[i][1]] = iter->second;

                if (from <= to) {
                    smap[from] = to;
                }
            } else { // if (iter->first <= S[i] && iter->second >= S[i]) {
                long long from1 = iter->first;
                long long to1 = S[i][0]-1;
                long long from2 = S[i][0]+1;
                long long to2 = iter->second;
                smap.erase(smap.find(iter->first));
                ans[S[i][1]] = S[i][0];

                if (from1 <= to1) {
                    smap[from1] = to1;
                }

                if (from2 <= to2) {
                    smap[from2] = to2;
                }
            }
        }

        cout << "Case #" << tc << ":";
        for (int i = 0; i < ans.size(); ++i) {
            cout << " " << ans[i];
        }
        cout << endl;
    }

    return 0;
}
