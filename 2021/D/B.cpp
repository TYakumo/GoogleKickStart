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


typedef long long ll;

#define EL printf("\n")
#define pb push_back
#define FOR(i,l,r) for (int i=l;i<=r;i++)
#define FORD(i,r,l) for (int i=r;i>=l;i--)

const int base = 1e9;
using BigInt = vector<int>;


void Set(BigInt &a) {
    while (a.size() > 1 && a.back() == 0) a.pop_back();
}

void Print(BigInt a) {
    Set(a);
    printf("%d", (a.size() == 0) ? 0 : a.back());
    FORD(i,a.size()-2,0) printf("%09d", a[i]); EL;
}

BigInt Integer(string s) {
    BigInt ans;
    if (s[0] == '-') return ans;
    if (s.size() == 0) {ans.pb(0); return ans;}
    while (s.size()%9 != 0) s = '0'+s;
    for (int i=0;i<s.size();i+=9) {
        int v = 0;
        for (int j=i;j<i+9;j++) v = v*10+(s[j]-'0');
        ans.insert(ans.begin(),v);
    }
    Set(ans);
    return ans;
}

// BigInt Integer(char c[]) {
//     string s = "";
//     FOR(i,0,strlen(c)-1) s = s + c[i];
//     return Integer(s);
// }

BigInt Integer(ll x) {
    // cout << "CALLED" << endl;
    string s = "";
    while (x > 0) s = char(x%10+'0') + s, x /= 10;
    return Integer(s);
}

BigInt Integer(int x) {
    return Integer((ll) x);
}

void operator >> (istream &in, BigInt &a) {
    string s;
    getline(cin, s);
    a = Integer(s);
}

void operator << (ostream &out, BigInt a) {
    Print(a);
}

bool operator < (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    if (a.size() != b.size()) return (a.size() < b.size());
    FORD(i,a.size()-1,0)
        if (a[i] != b[i]) return (a[i] < b[i]);
    return false;
}

bool operator > (BigInt a, BigInt b) {
    return (b < a);
}

bool operator == (BigInt a, BigInt b) {
    return (!(a < b) && !(b < a));
}

bool operator <= (BigInt a, BigInt b) {
    return (a < b || a == b);
}

bool operator >= (BigInt a, BigInt b) {
    return (b < a || b == a);
}

bool operator < (BigInt a, int b) {
    return (a < Integer(b));
}

bool operator > (BigInt a, int b) {
    return (a > Integer(b));
}

bool operator == (BigInt a, int b) {
    return (a == Integer(b));
}

bool operator >= (BigInt a, int b) {
    return (a >= Integer(b));
}

bool operator <= (BigInt a, int b) {
    return (a <= Integer(b));
}

BigInt max(BigInt a, BigInt b) {
    if (a > b) return a;
    return b;
}

BigInt min(BigInt a, BigInt b) {
    if (a < b) return a;
    return b;
}

BigInt operator + (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    BigInt ans;
    int carry = 0;
    FOR(i,0,max(a.size(), b.size())-1) {
        if (i < a.size()) carry += a[i];
        if (i < b.size()) carry += b[i];
        ans.pb(carry%base);
        carry /= base;
    }
    if (carry) ans.pb(carry);
    Set(ans);
    return ans;
}

BigInt operator + (BigInt a, int b) {
    return a + Integer(b);
}

BigInt operator ++ (BigInt &a) { // ++a
    a = a + 1;
    return a;
}

void operator += (BigInt &a, BigInt b) {
    a = a + b;
}

void operator += (BigInt &a, int b) {
    a = a + b;
}

BigInt operator * (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    BigInt ans;
    ans.assign(a.size()+b.size(), 0);
    FOR(i,0,a.size()-1) {
        ll carry = 0ll;
        for (int j=0;j<b.size() || carry > 0;j++) {
            ll s = ans[i+j] + carry + (ll)a[i]*(j<b.size()?(ll)b[j]:0ll);
            ans[i+j] = s%base;
            carry = s/base;
        }
    }
    Set(ans);
    return ans;
}

BigInt operator * (BigInt a, int b) {
    return a * Integer(b);
}

void operator *= (BigInt &a, BigInt b) {
    a = a * b;
}

void operator *= (BigInt &a, int b) {
    a = a * b;
}

inline string IntToString(long long v) {
    string ret;
    stringstream ss;
    ss << v;
    ss >> ret;
    return ret;
}

inline string IntToString(long long v, int d) {
    string ret;
    stringstream ss;
    ss << std::setfill('0') << std::setw(d) << v;
    ss >> ret;
    return ret;
}

string BigIntToString(BigInt& a) {
    string ret;

    if (a.size() == 0) {
        return "0";
    }

    vector <string> res;

    ret += IntToString(a.back());
    for (int i = a.size()-2; i >= 0; --i) {
        ret += IntToString(a[i], 9);
    }

    return ret;
}

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        cin >> N;

        long long C;
        cin >> C;
        map <long long, long long> pntCnt;

        for (int i = 0; i < N; ++i) {
            long long L;
            long long R;
            cin >> L >> R;

            ++pntCnt[L+1];
            pntCnt[L] += 0;
            pntCnt[R-1] += 0;
            --pntCnt[R];
        }

        VVLL seg;
        auto iter = pntCnt.begin();
        long long segCnt = 0;
        long long prevCoor = 0;

        while (iter != pntCnt.end()) {
            segCnt += iter->second;

            if (segCnt > 0) {
                if (prevCoor == 0) {
                    prevCoor = iter->first;
                }
                seg.push_back({segCnt, prevCoor, iter->first});
            }

            prevCoor = iter->first+1;
            ++iter;
        }

        sort(seg.begin(), seg.end());
        BigInt ans = Integer(N);

        for (int i = (int)seg.size()-1; i >= 0; --i) {
            long long maxlen = seg[i][2]-seg[i][1]+1;
            long long maxmul = min(C, maxlen);
            BigInt maxval = Integer(seg[i][0]) * Integer(maxmul);
            ans = ans + maxval;
            C -= maxmul;
        }

        cout << "Case #" << tc << ": ";
        Print(ans);
        cout << endl;
    }

    return 0;
}
