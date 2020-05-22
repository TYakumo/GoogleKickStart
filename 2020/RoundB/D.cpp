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

using VD = vector <double> ;
using VVD = vector <VD> ;

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int W;
        int H;
        int L;
        int U;
        int R;
        int D;

        cin >> W >> H >> L >> U >> R >> D;
        VVD prob(W, VD(H));
        --L;
        --R;
        --U;
        --D;

        prob[0][0] = 1;

        auto checkValid = [&L, &U, &R, &D](int w, int h) {
            return !((h >= U && h <= D) && (w >= L && w <= R));
        };

        for (int i = 0; i < W; ++i) {
            for (int j = 0; j < H; ++j) {
                if (i == W-1) { // to right
                    if (j+1 < H && checkValid(i, j+1)) {
                        prob[i][j+1] += prob[i][j];
                    }
                } else if (j == H-1) { // to down
                    if (i+1 < W && checkValid(i+1, j)) {
                        prob[i+1][j] += prob[i][j];
                    }
                } else {
                    if (i+1 < W && checkValid(i+1, j)) {
                        prob[i+1][j] += prob[i][j] * 0.5;
                    }

                    if (j+1 < H && checkValid(i, j+1)) {
                        prob[i][j+1] += prob[i][j] * 0.5;
                    }
                }
            }
        }


        cout << "Case #" << tc << ": " << prob[W-1][H-1] << endl;
    }

    return 0;
}
