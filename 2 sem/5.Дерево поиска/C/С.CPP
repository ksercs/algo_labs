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

const int MAXN = 3*(int)1e5 + 15;

struct content {
	int L, R, p;
	content(int p_, int L_, int R_) {
        p = p_;
	    L = L_;
	    R = R_;
	}
	content() {
        L = 0;
        R = 0;
        p = 0;
	}
};

struct Node {
	int x;
	int y;
	int ind;
	Node *L = nullptr;
	Node *R = nullptr;
	Node(int _x, int _y, int _ind) {
		x = _x, y = _y, ind = _ind;
	}
	Node(content a)
	{
	    x = a.p;
	    y = a.L;
	    ind = a.R;
	}
};

bool operator< (content a, content b)
{
    if (a.p != b.p) return a.p < b.p;
    if (a.L != b.L) return a.L < b.L;
    return a.R < b.R;
}

content ans[MAXN], a[MAXN];

void dfs(Node* v) {
	if (v->L != nullptr) {
		ans[v->ind].L = v->L->ind;
		ans[v->L->ind].p = v->ind;
		dfs(v->L);
	}
	if (v->R != nullptr) {
		ans[v->ind].R = v->R->ind;
		ans[v->R->ind].p = v->ind;
		dfs(v->R);
	}
}

int main() {
    //ifstream cin("C.in");
    //ofstream cout("C.out");
	int n, L, R;
	Node* root = nullptr;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> L >> R;
		a[i] = content(L, R, i);
    }
	sort(a + 1, a + 1 + n);
	root = new Node(a[1]);
	//cout << root->x << " " << root->y << " " << root->ind << "\n";
	VEC <Node*> q;
	q.PB(root);
	for (int i = 2; i <= n; i++) {
		Node* vertex = new Node(a[i]);
		//cout << vertex->x << " " << vertex->y << " " << vertex->ind << "\n";
		while (!q.empty() && q.back()->y > vertex->y) {
			q.pop_back();
		}
		if (q.empty()) {
            //cout << "Q : " << vertex->ind << "\n";
            vertex->L = root;
			root = vertex;
			q.PB(root);
        } else {
            vertex->L = q.back()->R;
            q.back()->R = vertex;
            q.PB(vertex);
		}
	}
	//cout << root->x << " " << root->y << " " << root->ind << "\n";
	dfs(root);
	cout << "YES\n";
	for (int i = 1; i <= n; i++)
		cout << ans[i].p << " " << ans[i].L << " " << ans[i].R << "\n";
    return 0;
}
