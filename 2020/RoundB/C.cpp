#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <unordered_map>
using namespace std;
const long long MOD = 1000000000;

inline vector <long long> toDir(char ch) {
    switch (ch) {
        case 'N':
            return {0, -1};
        case 'S':
            return {0, 1};
        case 'E':
            return {1, 0};
        default:
            return {-1, 0};
    }
}

vector <long long> parseMove(string& str, int s, int e, unordered_map <int, int> bmap) {
    if (s > e) {
        return {0, 0};
    }

    vector <long long> res = {0, 0};
    long long preFact = 1;

    for (int i = s; i <= e; ) {
        if (isalpha(str[i])) {
            vector <long long> subres = toDir(str[i]);
            res[0] += subres[0]*preFact;
            res[1] += subres[1]*preFact;
            res[0] %= MOD;
            res[1] %= MOD;
            preFact = 1;
            ++i;
        } else if (isdigit(str[i])) { // only one digit by definition
            long long fact = (str[i++]-'0');
            preFact = fact;
        } else {
            vector <long long> subres = parseMove(str, i+1, bmap[i]-1, bmap);
            res[0] += subres[0]*preFact;
            res[1] += subres[1]*preFact;
            res[0] %= MOD;
            res[1] %= MOD;
            preFact = 1;
            i = bmap[i]+1;
        }
    }

    return res;
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        string S;
        cin >> S;

        unordered_map <int, int> bmap;
        vector <int> lbStk;

        for (int i = 0; i < S.size(); ++i) {
            if (S[i] == '(') {
                lbStk.push_back(i);
            } else if(S[i] == ')') {
                bmap[lbStk.back()] = i;
                lbStk.pop_back();
            }
        }

        vector <long long> res = parseMove(S, 0, S.size()-1, bmap);
        auto fixPos = [](long long v) {
            v %= MOD;
            v = (v+MOD) % MOD;
            ++v;
            return v;
        };

        res[0] = fixPos(res[0]);
        res[1] = fixPos(res[1]);

        cout << "Case #" << tc << ": " << res[0] << " " << res[1] << endl;
    }

    return 0;
}
