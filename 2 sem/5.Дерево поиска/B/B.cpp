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

const int INF = 1e9 + 7;

struct Node
{
    int x;
    int y;
    int sz;
    Node *l, *r;

    Node(int _x)
    {
        x = _x;
        y = rand();
        sz = 1;
        l = r = nullptr;
    }
    Node()
    {
        x = 0;
        y = rand();
        sz = 1;
        l = r = nullptr;
    }
};


int get_sz(Node *t);
void update(Node *t);

Node* merge(Node *t1, Node *t2)
{
    if (t1 == nullptr) return t2;
    if (t2 == nullptr) return t1;

    if (t1->y > t2->y) {
        t1->r = merge(t1->r, t2);
        update(t1);
        return t1;
    } else {
        t2->l = merge(t1, t2->l);
        update(t2);
        return t2;
    }
}

void split(Node *t, int x, Node *&t1, Node *&t2)
{
    if (t == nullptr) {
        t1 = t2 = nullptr;
        return;
    }

    if (t->x < x) {
        split(t->r, x, t->r, t2);
        t1 = t;
    } else {
        split(t->l, x, t1, t->l);
        t2 = t;
    }
    update(t);
}

int get_sz(Node *t)
{
    if (t == nullptr) { return 0; }
    return t->sz;
}

void update(Node *t)
{
    if (t != nullptr)
        t->sz = 1 + get_sz(t->l) + get_sz(t->r);
}


void add(Node *&t, int x)
{
    Node *t1, *t2;
    split(t, x, t1, t2);
    Node* new_tree = new Node(x);
    t = merge(merge(t1, new_tree), t2);
}

void remove(Node *&t, int x)
{
    Node *t1, *t2, *t3, *t4;
    split(t, x, t1, t2);
    split(t2, x + 1, t3, t4);
    t = merge(t1, t4);
    delete t3;
}

void print(Node *t)
{
    if (t != nullptr) {
        print(t->l);
        cout << t->x << " ";
        print(t->r);
    }
}

int get_k(Node *t, int k)
{
    if (k < get_sz(t->l))
        return get_k(t->l, k);
    else if (k == get_sz(t->l))
        return t->x;
    else
        return get_k(t->r, k - get_sz(t->l) - 1);
}

int dfs(Node *t, int type)
{
    if (t != nullptr) {
        if (type == 1) {
            if (t->l == nullptr)
                return t->x;
            dfs(t->l, 1);
        } else {
            if (t->r == nullptr)
                return t->x;
            dfs(t->r, 0);
        }
    }
}

int main() {
    //ifstream cin("B.in");
    //ofstream cout("B.out");
    Node *treap = nullptr;
    int n, cnt;
    string s;
    while (cin >> s >> n) {
        if (s == "insert") {
            Node *tmp = new Node(n);
            Node *t1, *t2;
            split(treap, n, t1, t2);
            treap = merge(merge(t1, tmp), t2);
        }
        else if (s == "delete")
        {
            Node *t1, *t2, *t3, *t4;
            split(treap, n, t1, t2);
            split(t2, n + 1, t3, t4);
            treap = merge(t1, t4);
        }
        else if (s == "exists") {
            Node *t1, *t2, *t3, *t4;
            split(treap, n, t1, t2);
            split(t2, n + 1, t3, t4);
            if (t3 == nullptr) cout << "false\n";
            else cout << "true\n";
            treap = merge(t1, merge(t3, t4));
        }
        else if (s == "next") {
            Node *t1, *t2;
            split(treap, n + 1, t1, t2);
            if (t2 == nullptr) cout << "none\n";
            else cout << dfs(t2, 1) << "\n";
            treap = merge(t1, t2);
        }
        else if (s == "prev") {
            Node *t1, *t2;
            split(treap, n, t1, t2);
            if (t1 == nullptr) cout << "none\n";
            else cout << dfs(t1, 0) << "\n";
            treap = merge(t1, t2);
        }
    }
    return 0;
}
