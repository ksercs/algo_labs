#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <set>
#include <map>
#include <utility>
#include <queue>
#include <string.h>

#define SZ size()
#define VEC vector
#define PB push_back
#define MP make_pair
#define SS second
#define FF first
#define PII pair <int,int>
#define LL long long

using namespace std;

const int MAXN = (int)1e5 + 15;

VEC <int> ans;
int n, m;

struct Node {
    int y;
    int sz;
    int val;
    Node *L, *R;

    Node (int val_) {
        y = rand();
        sz = 1;
        val = val_;
        L = R = nullptr;
    }
};

int getSize(Node *t)
{
    if (t == nullptr)
        return 0;
    return t->sz;
}

void update(Node *t)
{
    if (t != nullptr) {
        t->sz = 1 + getSize(t->L) + getSize(t->R);
    }
}

Node* merge(Node* t1, Node* t2)
{
    if (t1 == nullptr)
        return t2;
    if (t2 == nullptr)
        return t1;
    if (t1->y > t2->y) {
        t1->R = merge(t1->R, t2);
        update(t1);
        return t1;
    }
    t2->L = merge(t1, t2->L);
    update(t2);
    return t2;
}

void split(Node* t, int x, Node* &t1, Node* &t2)
{
    if (t == nullptr) {
        t1 = t2 = nullptr;
        return;
    }
    if (getSize(t->L) < x) {
        split(t->R, x - getSize(t->L) - 1, t->R, t2);
        t1 = t;
    }
    else {
        split(t->L, x, t1, t->L);
        t2 = t;
    }
    update(t);
}

Node* to_front(Node *t, int L, int R)
{
    Node *t1, *t2, *t3, *t4;
    split(t, R, t1, t2);
    split(t1, L - 1, t3, t4);
    return merge(merge(t4, t3), t2);
}

void getAns(Node *t)
{
    if (t == nullptr)
        return;
    getAns(t->L);
    ans.PB(t->val);
    getAns(t->R);
}

int main()
{
    //ifstream cin("G.in");
    //ofstream cout("G.out");
    int L, R;
    cin >> n >> m;
    Node* root = nullptr;
    for (int i = 1; i <= n; ++i)
        root = merge(root, new Node(i));
    for (int i = 0; i < m; ++i) {
        cin >> L >> R;
        root = to_front(root, L, R);
    }
    getAns(root);
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << "\n";
    return 0;

}
