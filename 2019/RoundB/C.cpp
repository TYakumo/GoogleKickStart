#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <deque>
using namespace std;

template<class T>
class CusMaxOp {
public:
    inline T op(T a, T b) {
        return a + b;
    }

    inline T retOp(T a, T b) {
        return max(a, b);
    }

    inline T childOp(T a, T b) {
        return max(a, b);
    }

    inline T parentToChildOp(T a, T b) {
        return a + b;
    }

    inline T sumOp(T val, T sx, T ex) {
        return val;
    }
};

template<class T, class C, class O>
class SegmentTree {
    const T INIT_VAL = 0;
    T val;
    T sum;
    O op;
    int sx;
    int ex;
    vector <SegmentTree *> children;

    inline void recalculateSum() {
        T childSum = 0;
        for (int i = 0; i < children.size(); ++i) {
            childSum = op.childOp(childSum, children[i]->sum);
        }

        this->sum = op.parentToChildOp(this->val, childSum);
    }

    inline void propagateVal() {
        if (children.size() != 0) {

            for (int i = 0; i < children.size(); ++i) {
                children[i]->val = op.op(children[i]->val, this->val);
                children[i]->recalculateSum();
            }

            this->val = 0;
        }
    }

    inline void checkAndCreateChildren() {
        if (children.size() == 0) {
            C mid =  (sx + ex) / 2;

            children.emplace_back(new SegmentTree(sx, mid));
            children.emplace_back(new SegmentTree(mid, ex));
            propagateVal();
        }
    }

public:

    SegmentTree (C spaceSize) {
        sum = val = INIT_VAL;
        sx = ex = 0;

        ex = 1;
        while (ex < spaceSize) {
            ex *= 2;
        }
    }

    SegmentTree (C psx, C pex) : sx(psx), ex(pex) {
        sum = val = INIT_VAL;
    }

    void updateSegment(C x1, C x2, T v) {
        if (x1 >= x2) {
            return ;
        }

        if (x1 == sx && x2 == ex) {
            val = op.op(val, v);
            recalculateSum();
            return ;
        }

        C mid =  (sx + ex) / 2;
        checkAndCreateChildren();
        propagateVal();

        if (x1 < mid) {
            children[0]->updateSegment(x1, min(x2, mid), v);
        }

        if (ex > mid) {
            children[1]->updateSegment(max(x1, mid), x2, v);
        }

        recalculateSum();
    }

    T query(C x1, C x2) {
        if (x1 >= x2) {
            return INIT_VAL;
        }

        if (x1 == sx && x2 == ex) {
            return this->sum;
        }

        T ret = INIT_VAL;
        C mid =  (sx + ex) / 2;
        checkAndCreateChildren();
        propagateVal();

        if (x1 < mid) {
            ret = op.retOp(ret, children[0]->query(x1, min(x2, mid)));
        }

        if (x2 > mid) {
            ret = op.retOp(ret, children[1]->query(max(x1, mid), x2));
        }

        recalculateSum();

        return ret;
    }
};

int main() {
    int T;

    cin >> T;

    for (int t = 1; t <= T; ++t) {
        int N;
        int S;

        cin >> N >> S;

        SegmentTree<int, int, CusMaxOp<int>> st(N+10);
        const int MAXV = 100010;
        vector < deque <int> > idx(MAXV+1);
        vector <int> lastCancelPos(MAXV+1, -1);
        int ans = 0;

        for (int i = 1; i <= N; ++i) {
            int A;
            cin >> A;

            idx[A].push_back(i);
            st.updateSegment(0, i, 1);

            if (idx[A].size() > S) {
                int removeIdx = idx[A].front();
                if (lastCancelPos[A] != -1) {
                    st.updateSegment(0, lastCancelPos[A], S);
                }

                st.updateSegment(0, removeIdx, -(S+1));
                lastCancelPos[A] = removeIdx;
                idx[A].pop_front();
            }

            ans = max(ans, st.query(0, i));
        }


        cout << "Case #" << t << ": " << ans << endl;
    }

    return 0;
}