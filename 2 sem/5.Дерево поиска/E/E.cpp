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

const int INF = (int)1e9;

struct Node
{
    int x; 
    int y; 
    int sz;
    long long sum;
    Node *l, *r;

    Node(int _x) {
        x = _x;
        y = rand();
        sz = 1;
        sum = _x;
        l = r = nullptr;
    }
    Node() {
        x = 0;
        y = rand();
        sz = 1;
        sum = 0;
        l = r = nullptr;
    }
};

int get_sz(Node *t);
long long get_sum(Node *t);
void update(Node *t);

Node* merge(Node *t1, Node *t2)
{
    if (t1 == nullptr) {
        update(t2);
        return t2;
    }
    if (t2 == nullptr) {
        update(t1);
        return t1;
    }

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
    update(t);

    if (t->x < x) {
        split(t->r, x, t->r, t2);
        t1 = t;
    } else {
        split(t->l, x, t1, t->l);
        t2 = t;
    }
    update(t);
}

int get_sz(Node *t) {
    if (t == nullptr) return 0;
    return t->sz;
}

long long get_sum(Node *t) {
    if (t == nullptr) return 0;
    return t->sum;
}

void update(Node *t)
{
    if (t != nullptr) {
        t->sz = 1 + get_sz(t->l) + get_sz(t->r);
        t->sum = get_sum(t->l) + get_sum(t->r) + t->x;
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
        cout << t->x << ' ' << t->sum << '\n';
        print(t->r);
    }
}

int n, cnt;
string s;

int main() {
    //ifstream cin("E.in");
    //ofstream cout("E.out");
    Node *treap = nullptr;
    int n, l, r;
    long long last = 0;
    cin >> n;
    set<int> st;
    for (int i = 0; i < n; ++i)
    {
        cin >> s >> l;
        if (s == "+") {
            r = (last + l) % INF;
            last = 0;
            if (!st.count(r)) {
                st.insert(r);
                add(treap, r);
            }
        }
        else if (s == "?") {
            cin >> r;
            Node *t1, *t2, *t3, *t4;
            split(treap, l, t1, t2);
            split(t2, r + 1, t3, t4);
            last = get_sum(t3);
            cout << last << '\n';
            treap = merge(t1, merge(t3, t4));
        }
    }
    return 0;
}
