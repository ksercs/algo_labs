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
    Node() {}
};


int get_sz(Node *t);
void update(Node *t);

Node* merge(Node *t1, Node *t2)
{
    if (t1 == nullptr) { return t2; }
    if (t2 == nullptr) { return t1; }

    if (t1->y > t2->y)
    {
        t1->r = merge(t1->r, t2);
        update(t1);
        return t1;
    }
    else
    {
        t2->l = merge(t1, t2->l);
        update(t2);
        return t2;
    }
}

void split(Node *t, int x, Node *&t1, Node *&t2)
{
    if (t == nullptr)
    {
        t1 = t2 = nullptr;
        return;
    }
    if (t->x < x)
    {
        split(t->r, x, t->r, t2);
        t1 = t;
    }
    else
    {
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
    {
        t->sz = 1 + get_sz(t->l) + get_sz(t->r);
    }
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
    if (t != nullptr)
    {
        print(t->l);
        cout << t->x << " ";
        print(t->r);
    }
}

int get_k(Node *t, int k)
{
    if (k < get_sz(t->l))
    {
        return get_k(t->l, k);
    }
    else if (k == get_sz(t->l))
    {
        return t->x;
    }
    else
    {
        return get_k(t->r, k - get_sz(t->l) - 1);
    }
}

int n, cnt;
string s;

int main() {
    //ifstream cin("F.in");
    //ofstream cout("F.out");
    Node *treap = nullptr;
    int n;
    cin >> n;
    int cnt = 0;
    while (n--)
    {
        string s;
        int k;
        cin >> s >> k;
        if (s == "+1" || s == "1")
        {
            ++cnt;
            add(treap, k);
        }
        if (s == "-1")
        {
            --cnt;
            remove(treap, k);
        }
        if (s == "0")
        {
            cout << get_k(treap, cnt-k) << "\n";
        }
    }
    return 0;
}
