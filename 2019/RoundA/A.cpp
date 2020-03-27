#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
using namespace std;

int main() {
    int T;

    cin >> T;

    for (int t = 1; t <= T; ++t) {
        int N;
        int P;
        cin >> N >> P;

        vector <int> skill(N);
        vector <int> sum(N);

        for (int i = 0; i < N; ++i) {
            cin >> skill[i];
        }

        sort(skill.begin(), skill.end());

        sum[0] = skill[0];
        for (int i = 1; i < N; ++i) {
            sum[i] = sum[i-1] + skill[i];
        }

        const int INF = 1000000010;
        int minNeeded = INF;

        for (int i = P-1; i < N; ++i) {
            int allPower = P * skill[i];
            int segSum = sum[i];

            if (i-P >= 0) {
                segSum -= sum[i-P];
            }

            int upgrade = allPower - segSum;
            minNeeded = min(minNeeded, upgrade);
        }

        cout << "Case #" << t << ": " << minNeeded << endl;
    }

    return 0;
}