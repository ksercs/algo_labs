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

const int MAXN = 131072 + 15;

LL n, m, answer, nodes;
VEC <LL> ans, num;

struct Node
{
    int y, sz, val;
    Node *L, *R;
    Node (int v_) {
        y = rand();
        val = v_;
        L = R = 0;
        sz = 1;
    }

    int getSize (Node *v)
    {
        return v ? v->sz : 0;
    }

    void update (Node *v)
    {
        if (!v) return;
        v->sz = getSize(v->L) + getSize(v->R) + 1;
    }

    int getInd ()
    {
        return getSize(L) + 1;
    }

    void Print (Node *v)
    {
        if (!v) return;
        Print(v->L);
        ans.PB(v->val);
        Print(v->R);
    }
};

Node *root;

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
    root->update(v);
}

void split (Node *v, int x, Node *&L, Node *&R)
{
    if (!v) {
        L = R = 0;
        return;
    }
    int ind = v->getInd();
    if (ind <= x) {
        L = v;
        split(v->R, x - ind, L->R, R);
        root->update(L);
    }
    else {
        R = v;
        split(v->L, x, L, R->L);
        root->update(R);
    }
}

void insert (Node *&R, Node *v, int x)
{
    if (!R) {
        R = v;
        return;
    }
    int pos = R->getInd();
    if (v->y > R->y) {
        split(R, x - 1, v->L, v->R);
        R = v;
    }
    else if (x <= pos) {
        insert(R->L, v, x);
    }
    else {
        insert(R->R, v, pos - x + 2);
    }
    root->update(R);
}

void insert (Node *v, int x)
{
    Node *L = 0, *R = 0;
    split(root, x - 1, L, R);
    merge(L, v, L);
    merge(L, R, root);
}

void erase (Node *&v, int x)
{
    int pos = v->getInd();
    if (pos == x) {
        merge(v->L, v->R, v);
    } else if (x < pos) {
        erase(v->L, x);
    } else {
        erase(v->R, x - pos);
    }
    root->update(v);
}

void in()
{
    //ifstream cin("D.in");
    cin >> n >> m;
    num.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> num[i];
    }
}

void solution ()
{
	set <int> zer;
	for (int i = 1; i <= m; ++i) {
		insert(new Node(0), i);
		zer.insert(i);
	}
	for (int i = 0; i < n; ++i) {
		auto it = zer.lower_bound(num[i]);
		if (it == zer.end() || *it > answer)
			++answer;
		if (it != zer.end()) {
			erase(root, *it);
			zer.erase(it);
		}
		answer = max(answer, num[i]);
		insert(new Node(i + 1), num[i]);
	}
    Node *L = 0, *mid = 0, *R = 0;
    split(root, 0, L, R);
    split(R, answer, mid, R);
    root->Print(mid);
}

void out()
{
    //ofstream cout("D.out");
    cout << answer << "\n";
    for (int i = 0; i < ans.SZ; ++i) {
        cout << ans[i] << " ";
    }
    cout << "\n";
}

int main()
{
	in();
	solution();
    out();
	return 0;
}
