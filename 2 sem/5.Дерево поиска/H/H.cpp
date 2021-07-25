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

struct Node {
    int y;
    int sz;
    char c;
    int indx;
    int dif;
    Node *L, *R;

    Node (int indx_, int cnt_, char c_) {
        y = rand();
        sz = cnt_;
        c = c_;
        dif = 1;
        indx = indx_;
        L = R = nullptr;
    }
};
Node *root;

int getSize(Node *t)
{
    if (t == nullptr)
        return 0;
    return t->sz;
}

int getIndex(Node *t)
{
    if (t == nullptr)
        return 0;
    return t->indx;
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
    //cout << t1->c << " " << t2->c << "\n";
    if (t1->y > t2->y) {
        t1->R = merge(t1->R, t2);
        update(t1);
        return t1;
    }
    t2->L = merge(t1, t2->L);
    update(t2);
    return t2;
}

void merge (Node *L, Node *R, Node *&v)
{
    if (!L || !R) {
        if (!L)
            v = R;
        else
            v = L;
        return;
    }
    if (L->y > R->y) {
        v = L;
        merge(L->R, R, v->R);
    }
    else {
        v = R;
        merge(L, R->L, v->L);
    }
    update(v);
}


void erase (Node *&v, int x)
{
    int pos = v->indx;
    if (pos == x) {
        merge(v->L, v->R, v);
    } else if (x < pos) {
        erase(v->L, x);
    } else {
        erase(v->R, x - pos);
    }
    update(v);
}

void insert(Node* &v, int a, int b, char c);

void splitVertex (Node* t, int x, Node *t1, Node *t2, int cnt)
{
    Node v = *t;
    //erase(root, v.indx);
    if (t == 0) {
        cout << "ROT EBAL\n";
    }
    int L = v.indx;
    int R = v.indx + v.sz - 1;
    if (x > L) {
        cout << "L : " << L << " " << x-1-L+1 << "\n";
        //insert(root, L, x-1-L+1, v.c);
    }
    if (R > x+cnt-1) {
        cout << "R : " << x+cnt << " " << R-x-cnt+1 << "\n";
        insert(root, x+cnt, R-x-cnt+1, v.c);
    }
}

void split(Node* &t, int x, Node* &t1, Node* &t2, int cnt)
{
    if (t == nullptr) {
        t1 = t2 = nullptr;
        return;
    }
    cout << "SPLIT : " << t->indx << " " << t->sz << "\n";
    int mid = t->indx + t->sz - 1;

    if (mid < x) {
        split(t->R, x - mid, t->R, t2, cnt);
        t1 = t;
    }
    else {
        if (x >= t->indx && x <= mid) {
            cout << "SPLITVVVVV \n";
            splitVertex(t, x, t1, t2, cnt);
        }//else {
            split(t->L, x, t1, t->L, cnt);
       // }
        t2 = t;
    }
    update(t);
}

void getAns (Node* v);

void insert (Node *&v, int ind, int cnt, char c)
{
    Node *t1, *t2;
    split(v, ind, t1, t2, cnt);
    v = merge(merge(t1, new Node(ind, cnt, c)), t2);
    getAns(v);
    cout << "\n";
}

void getAns(Node *t)
{
    if (t == nullptr)
        return;
    getAns(t->L);
    if (t->sz > 1 && t->L == 0 && t->R == 0)
        for (int i = 0; i < t->sz; ++i) {
            cout << t->indx << " " << t->sz << " " << t->c << "\n";
    }
    else cout << t->indx << " " << t->sz << " " << t->c << "\n";
    getAns(t->R);
}

void out ()
{
    ofstream cout("log.out");
    for (int i = 0; i < ans.SZ; ++i) {
        cout << ans[i] << " ";
    }
    cout << "\n";
}

int main()
{
    ifstream cin("log.in");
    int q;
    cin >> q;
    root = nullptr;
    for (int i = 0; i < q; ++i) {
        char t, letter;
        int index, number;
        cin >> t;
        if (t == '+') {
            cin >> index >> number >> letter;
            cout << " + " << index << " " << number << " " << letter << "\n";
            if (root == 0) {
                root = new Node(1, number, letter);
                getAns(root);
                cout << "\n";
            } else
                insert(root, index, number, letter);
        }
        if (t == '-') {
            cin >> index >> number;
        }
        if (t == '?') {
            int L, R;
            cin >> L >> R;
        }
    }
    getAns(root);
    out();
    return 0;
}
