#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXC = 26;

struct TrieNode {
    vector <TrieNode*> children;
    TrieNode* parent;
    int wordCount;
    int depth;

    TrieNode() {
        children = move(vector <TrieNode*> (MAXC));
        wordCount = 0;
        depth = 0;
        parent = nullptr;
    }
};

void addToTrie(TrieNode* root, string& str) {
    for (int i = 0; i < str.size(); ++i) {
        int c = str[i] - 'A';
        if (root->children[c] == nullptr) {
            root->children[c] = new TrieNode();
            root->children[c]->depth = root->depth + 1;
            root->children[c]->parent = root;
        }

        ++root->wordCount;
        root = root->children[c];
    }

    ++root->wordCount;
}

void freeTrie(TrieNode* root) {
    if (root == nullptr) {
        return ;
    }

    for (int i = 0; i < MAXC; ++i) {
        freeTrie(root->children[i]);
    }

    delete root;
}

int main() {
    int T;

    cin >> T;

    for (int t = 1; t <= T; ++t) {
        int N;
        int K;
        cin >> N >> K;
        vector <string> names(N);
        TrieNode *root = new TrieNode();

        for (int i = 0; i < N; ++i) {
            cin >> names[i];
            addToTrie(root, names[i]);
        }

        int ans = 0;
        deque <TrieNode*> que;
        priority_queue< pair<int,TrieNode*> >  pq;

        que.push_back(root);

        while (!que.empty()) {
            TrieNode* now = que.front();
            que.pop_front();

            if (now->depth && now->wordCount >= K) {
                pq.push({now->depth, now});
            }

            for (int c = 0; c < MAXC; ++c) {
                if (now->children[c]) {
                    que.push_back(now->children[c]);
                }
            }
        }

        while (!pq.empty()) {
            TrieNode* node = pq.top().second;
            pq.pop();

            if (node->wordCount < K) {
                continue;
            }

            TrieNode* tmp = node;
            int tot = (node->wordCount / K) * K;
            ans += node->depth * (node->wordCount / K);

            while (tmp) {
                tmp->wordCount -= tot;
                tmp = tmp->parent;
            }
        }

        cout << "Case #" << t << ": " << ans << endl;

        freeTrie(root);
    }

    return 0;
}