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

using VI = vector <int>;
using VVI = vector <VI>;
const int MAXLEVEL = 21; // Must be greater than 1 (> 1), and 2^MAXLEVEL >= #nodes

struct TreeNode {
    int val;
    int idx;
    int depth;
    int treeSize;
    TreeNode* leftChild;
    TreeNode* rightChild;
    vector <TreeNode*> parent;

    TreeNode (int pv, int pi) : val(pv), idx(pi) {
        depth = 0;
        treeSize = 1;
        leftChild = nullptr;
        rightChild = nullptr;
        parent = vector <TreeNode*>(MAXLEVEL, nullptr);
    }

    static int getTreeSize(TreeNode* node) {
        return (node == nullptr) ? 0 : node->treeSize;
    }
};

class CartesianTree {
    TreeNode* root;
    unordered_map<int, TreeNode*> idxMap;

    void getIdxMapping(TreeNode* root, unordered_map<int, TreeNode*>& idxMap) {
        deque <TreeNode*> que;
        que.push_back(root);

        while (!que.empty()) {
            TreeNode* now = que.front();
            que.pop_front();

            idxMap[now->idx] = now;

            if (now->leftChild) {
                que.push_back(now->leftChild);
            }

            if (now->rightChild) {
                que.push_back(now->rightChild);
            }
        }
    }

    void treeTraversal(TreeNode* root, int precalLevel) {
        root->depth = 0;
        root->treeSize = 0;
        deque <TreeNode*> que;
        que.push_back(root);

        for (int i = 0; i < que.size(); ++i) {
            TreeNode* now = que[i];

            TreeNode* p = now->parent[precalLevel-1];
            if (p != nullptr) {
                now->parent[precalLevel] = p->parent[precalLevel-1];
            }

            if (now->leftChild != nullptr) {
                now->leftChild->depth = now->depth+1;
                que.push_back(now->leftChild);
            }

            if (now->rightChild != nullptr) {
                now->rightChild->depth = now->depth+1;
                que.push_back(now->rightChild);
            }
        }

        while (!que.empty()) {
            TreeNode* now = que.back();
            que.pop_back();

            now->treeSize = 1;
            if (now->leftChild != nullptr) {
                now->treeSize += now->leftChild->treeSize;
            }

            if (now->rightChild != nullptr) {
                now->treeSize += now->rightChild->treeSize;
            }
        }
    }

    void precalculationLCA(TreeNode* root) {
        // precalculation
        for (int l = 1; l < MAXLEVEL; ++l) {
            treeTraversal(root, l);
        }
    }

    TreeNode* __buildCartesianTree(VI& seq) {
        vector <TreeNode*> stk;
        auto cmp = [](int v1, int v2) { return v1 > v2; }; // customize this if type or order needs to be changed

        for (int i = 0; i < seq.size(); ++i) {
            TreeNode* now = new TreeNode(seq[i], i);

            // cout << "SEQ " << seq[i] << endl;
            if (stk.empty() || cmp(stk.back()->val, seq[i])) {
                stk.push_back(now);
            } else {
                // clearing the stack
                TreeNode* topNode = nullptr;

                while (!stk.empty() && !cmp(stk.back()->val, seq[i])) {
                    stk.back()->rightChild = topNode;
                    if (topNode != nullptr) {
                        topNode->parent[0] = stk.back();
                    }

                    topNode = stk.back();
                    stk.pop_back();
                }

                now->leftChild = topNode;
                if (topNode != nullptr) {
                    topNode->parent[0] = now;
                }
                stk.push_back(now);
            }
        }

        if (stk.size() > 1) {
            TreeNode* topNode = nullptr;

            while (!stk.empty()) {
                stk.back()->rightChild = topNode;
                if (topNode != nullptr) {
                    topNode->parent[0] = stk.back();
                }
                topNode = stk.back();
                stk.pop_back();
            }

            return topNode;
        }

        return stk.back();
    }
public:
    static CartesianTree* buildCartesianTree(vector<int>& seq) {
        CartesianTree* ctree = new CartesianTree();
        ctree->root = ctree->__buildCartesianTree(seq);
        ctree->precalculationLCA(ctree->root);
        ctree->getIdxMapping(ctree->root, ctree->idxMap);
        return ctree;;
    }

    TreeNode* getTreeNodeByIdx(int idx) {
        return idxMap[idx];
    }

    TreeNode* getRoot() {
        return root;
    }
};

int main()
{
    int TC;

    cin >> TC;

    for (int tc = 1; tc <= TC; tc++) {
        int N;
        int Q;
        cin >> N >> Q;

        VI b(N-1);

        for (int i = 0; i < N-1; ++i) {
            cin >> b[i];
        }

        cout << "Case #" << tc << ":";
        CartesianTree* ctree = CartesianTree::buildCartesianTree(b);

        for (int q = 0; q < Q; ++q) {
            int K;
            int S;
            cin >> S >> K;

            TreeNode* node = ctree->getTreeNodeByIdx(--S);
            --K;

            if (node == nullptr) { //S == N-1
                cout << " " << (S-K) + 1;
                continue;
            }

            int startIdx = node->idx;
            int ans = -1;

            if (node->treeSize >= K) {
                if (startIdx == S) { // from left
                    if (K <= TreeNode::getTreeSize(node->leftChild)) { // to left
                        ans = S - K;
                    } else { // to right
                        ans = S + (K - TreeNode::getTreeSize(node->leftChild));
                    }
                }
                // } else { // from right, startIdx == S+1
                //     if (K <= TreeNode::getTreeSize(node->rightChild)) { // to right
                //         ans = S + K;
                //     } else { // to left
                //         ans = S - (K - TreeNode::getTreeSize(node->rightChild));
                //     }
                // }
            } else { // find a node->treeSize >= K
                for (int l = MAXLEVEL-1; l >= 0; --l) {
                    TreeNode* ptr = node->parent[l];
                    if (ptr != nullptr && ptr->treeSize < K) {
                        node = ptr;
                    }
                }

                if (node->treeSize < K) {
                    node = node->parent[0];
                }

                if (S > node->idx) { // from right to left
                    ans = node->idx + 1 - (K - TreeNode::getTreeSize(node->rightChild));
                } else { // left to right
                    ans = node->idx + (K - TreeNode::getTreeSize(node->leftChild));
                }
            }

            cout << " " << ans+1 ;
        }

        cout << endl;
    }

    return 0;
}
