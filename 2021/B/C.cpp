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

long long modPow(long long n, long long p, long long mod) {
    if (n == 0) {
        return 1;
    }

    long long hf = modPow(n/2, p, mod);
    long long mul = (n&1)*(p-1) + 1;
    return (((hf*hf)%mod)*mul) % mod;
}

bool primalityTest(long long n, const VLL& primeWitness) {
    if (n <= 1 || n == 4) {
        return false;
    }

    if (n == 2) {
        return true;
    }

    for (int i = 0; i < primeWitness.size(); i++) {
        long long phi = n-1;
        long long pw = primeWitness[i];

        if (pw+2 >= n) {
            continue;
        }

        if (modPow(phi, pw, n) != 1) {
            return false;
        }

        long long d = n-1;
        while (d % 2 == 0) {
            d /= 2;
        }

        bool testOK = false;
        if (modPow(d, pw, n) == 1 || modPow(d, pw, n) == n-1) {
            testOK = true;
        }

        d *= 2;
        while (d < n-1 && !testOK) {
            if(modPow(d, pw, n) == n-1) {
                testOK = true;
            }
            d *= 2;
        }

        if (!testOK) {
            return false;
        }
    }

    return true;
}

VLL defaultWitness() {
    VLL ret;

    ret.push_back(2);
    ret.push_back(3);
    ret.push_back(5);
    ret.push_back(7);
    ret.push_back(11);
    ret.push_back(13);
    ret.push_back(17);
    ret.push_back(19);
    ret.push_back(23);
    ret.push_back(29);
    ret.push_back(31);
    ret.push_back(37);

    return ret;
}

int main()
{
    int TC;

    cin >> TC;
    VLL witness = defaultWitness();

    for (int tc = 1; tc <= TC; tc++) {
        long long Z;
        cin >> Z;

        long long sq = sqrt(Z);
        long long oriSq = sq;
        VLL p;

        while (sq > 0 && p.size() < 1) {
            if (primalityTest(sq, witness)) {
                p.push_back(sq);
            }
            --sq;
        }

        long long mul = Z/p[0];

        for (long long v = oriSq+1; v <= mul; ++v) {
            if (primalityTest(v, witness)) {
                p.push_back(v);
                break;
            }
        }

        while (sq > 0 && p.size() < 2) {
            if (primalityTest(sq, witness)) {
                p.push_back(sq);
            }
            --sq;
        }

        cout << "Case #" << tc << ": " <<  p[0]*p[1] << endl;
    }

    return 0;
}
