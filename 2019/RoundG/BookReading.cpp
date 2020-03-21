#include <cstdio>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int T;

    cin >> T;

    for (int t = 1; t <= T; ++t) {
        int N;
        int M;
        int Q;

        cin >> N >> M >> Q;
        vector <int> pages(M);

        for (int i = 0; i < M; ++i) {
            cin >> pages[i];
        }

        long long ret = 0;

        unordered_map <int, long long> subtract;

        for (int i = 0; i < Q; ++i) {
            int reader;
            cin >> reader;
            ret += N / reader; // reading without torn

            if (subtract.find(reader) != subtract.end()) {
                ret -= subtract[reader];
                continue;
            }

            int sub = 0;

            // sum of N / reader[i] => O(NlogN); total : O(NlogNlogM)
            int idx = 0;

            for (int m = 1; reader*m <= N && reader*m <= pages.back(); ++m) {
                int v = reader*m;
                int low = 0;
                int up = M-1;

                // O(logM)
                while (low <= up) {
                    int mid = (low+up) / 2;

                    if (pages[mid] == v) {
                        ++sub;
                        break;
                    } else if (pages[mid] < v) {
                        low = mid+1;
                    } else {
                        up = mid-1;
                    }
                }
            }

            ret -= sub;
            subtract[reader] = sub;
        }

        cout << "Case #" << t << ": " << ret << endl;
    }

    return 0;
}