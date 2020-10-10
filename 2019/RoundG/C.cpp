#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <deque>
using namespace std;

using MPLL = map <long long, long long>;
using MMPLL = map <long long, MPLL>;
using VI = vector<long long>;

void precalSum(VI& sum, VI& A) {
    int N = A.size();

    int upper = 1 << N;

    for (int i = 0; i < upper; ++i) {
        long long sa = 0;
        for (int a = 0; a < N; ++a) {
            if (i & (1<<a)) {
                sa += A[a];
            }
        }
        sum[i] = sa;
    }
}

void genDP(VI A, VI B, MMPLL& dp) {
    int N = A.size();
    int upper = 1 << N;

    VI sumA(upper);
    VI sumB(upper);

    precalSum(sumA, A);
    precalSum(sumB, B);

    for (int i = 0; i < upper; ++i) {
        for (int j = 0; j < upper; ++j) {
            long long sa = sumA[i];
            long long sb = sumB[j];

            if ((i | j) == (upper-1)) {
                ++dp[sa][sb];
            } else {
                long long bak = dp[sa][sb];
                dp[sa][sb] = bak;
            }
        }
    }
}

void accDP(MMPLL& dp) {
    auto iter = dp.rbegin();
    auto preIter = dp.rbegin();
    auto nextIter = dp.rbegin();

    while (iter != dp.rend()) {
        nextIter = iter;
        ++nextIter;

        auto iter2 = iter->second.rbegin();
        long long acc = 0;

        while (iter2 != iter->second.rend()) {
            acc += iter2->second;
            iter2->second = acc;

            if (iter != preIter) {
                iter2->second += preIter->second[iter2->first];
            }

            ++iter2;
        }

        preIter = iter;
        ++iter;
    }
}

int main() {
    int T;

    cin >> T;

    for (int t = 1; t <= T; ++t) {
        int N;
        long long H;
        cin >> N >> H;

        VI A(N);
        VI B(N);

        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }

        for (int i = 0; i < N; ++i) {
            cin >> B[i];
        }

        long long ans = 0;

        MMPLL dp;
        if (N >= 4) {
            MMPLL dp2;
            VI AH1(A.begin(), A.begin()+N/2);
            VI AH2(A.begin()+N/2, A.end());

            VI BH1(B.begin(), B.begin()+N/2);
            VI BH2(B.begin()+N/2, B.end());

            genDP(AH1, BH1, dp);
            genDP(AH2, BH2, dp2);
            accDP(dp2);

            auto iter = dp.begin();

            while (iter != dp.end()) {
                auto iter2 = iter->second.begin();

                while (iter2 != iter->second.end()) {
                    long long T1 = H - iter->first;
                    long long T2 = H - iter2->first;

                    auto iterp = dp2.lower_bound(T1);

                    if (iterp != dp2.end()) {
                        auto iterp2 = iterp->second.lower_bound(T2);
                        if (iterp2 != iterp->second.end()) {
                            ans += iter2->second * iterp2->second;
                        }
                    }

                    ++iter2;
                }

                ++iter;
            }
        } else {
            genDP(A, B, dp);
            auto iter = dp.begin();

            while (iter != dp.end()) {
                if (iter->first >= H) {
                    auto iter2 = iter->second.begin();

                    while (iter2 != iter->second.end()) {
                        if (iter2->first >= H) {
                            ans += iter2->second;
                        }
                        ++iter2;
                    }
                }
                ++iter;
            }
        }

        cout << "Case #" << t << ": " << ans << endl;
    }

    return 0;
}