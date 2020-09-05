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
pair <int, int> checkReverse(VI& A) {
    pair <int, int> ret;

    int theMax = -1;

    for (int i = 0; i < A.size(); ++i) {
        if (A[i] >= theMax) {
            ++ret.first;
        }
        theMax = max(theMax, A[i]);
    }

    theMax = -1;

    for (int i = A.size()-1; i >= 0; --i) {
        if (A[i] >= theMax) {
            ++ret.second;
        }
        theMax = max(theMax, A[i]);
    }

    return ret;
}

bool checkArrOK(int A, int B, VI& H) {
    pair <int, int> ret = checkReverse(H);

    return ret.first == A && ret.second == B;
}

void outputArr(int tc, VI& A) {
    cout << A[0];

    for (int i = 1; i < A.size(); ++i) {
        cout << " " << A[i];
    }

    cout << endl;
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int A;
        int B;
        int C;
        cin >> N >> A >> B >> C;

        int RA = A-C;
        int RB = B-C;
        int R = N-C-RA-RB;

        VI H(N);

        if (R < 0 || RA < 0 || RB < 0 || (RA == 0 && RB == 0 && C < 2 && R > 0)) {
            cout << "Case #" << tc << ": IMPOSSIBLE" << endl;
        } else {
            cout << "Case #" << tc << ": ";
            // notice C >= 1
            if (RA > 0) {
                int cnt = 0;

                for (int i = 0; i < RA; ++i) {
                    H[cnt++] = N-1;
                }

                for (int i = 0; i < R; ++i) {
                    H[cnt++] = 1;
                }

                for (int i = 0; i < C; ++i) {
                    H[cnt++] = N;
                }

                for (int i = 0; i < RB; ++i) {
                    H[cnt++] = N-1;
                }

                if (checkArrOK(A, B, H)) {
                    outputArr(tc, H);
                } else {
                    cout << "Case #" << tc << ": IMPOSSIBLE" << endl;
                }
            } else if (RB > 0) { // RA == 0
                int cnt = 0;

                for (int i = 0; i < C; ++i) {
                    H[cnt++] = N;
                }

                for (int i = 0; i < R; ++i) {
                    H[cnt++] = 1;
                }

                for (int i = 0; i < RB; ++i) {
                    H[cnt++] = N-1;
                }

                if (checkArrOK(A, B, H)) {
                    outputArr(tc, H);
                } else {
                    cout << "Case #" << tc << ": IMPOSSIBLE" << endl;
                }
            } else {
                cout << N ;
                for (int i = 0; i < R; ++i) {
                    cout << " " << 1;
                }

                for (int i = 1; i < C; ++i) {
                    cout << " " << N;
                }

                cout << endl;
            }
        }
    }

    return 0;
}
