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
#include <climits>
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

const int MAXN = (int) 1e4 + 15;
double INF = 1e9+15;

struct point {
    int x;
    int y;

    point() {}
    point(int _x, int _y) : x(_x), y(_y) {}
};
/*
struct edge {
    point a;
    point b;
    double cost;

    edge() {}
    edge(point _a, point _b) : a(_a), b(_b) {
        double dx = (_b.x - _a.x);
        double dy = (_b.y - _a.y);
        cost = sqrt(dx * dx + dy * dy);
    }
};*/

/*int n, m;
double ans;
point vert[MAXN];
int p[MAXN], r[MAXN];
VEC<edge> ed;
*/


/*void make_set(int a)
{
    p[a] = a;
    r[a] = 1;
}

int find_set(int a)
{
    if (a == p[a]) {
        return a;
    }
	int res = find_set(p[a]);
    p[a] = res;

	return res;
}

void union_sets(int a, int b)
{
	a = find_set(a);
	b = find_set(b);
	if (r[a] > r[b]) {
        swap(a,b);
    }
	p[a] = b;
	if (r[a] == r[b]) {
        ++r[b];
    }
}

bool comp(edge a, edge b) {
    return a.cost < b.cost;
}

void kruskal ()
{
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        int a = find_set(ed[i].a.num);
        int b = find_set(ed[i].b.num);

        if (a != b) {
            union_sets(a, b);
            //cout << ed[i].cost << "\n";
            ans += ed[i].cost;
            ++ cnt;
            if (cnt == n - 1) {
                break;
            }
        }
    }
}
*/
int n;
double ans;
double w[MAXN];
pair<double, int> mini[MAXN];
int p[MAXN], inTree[MAXN];
point vert[MAXN];

double get_S(point a, point b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);
}

void in()
{
    //ifstream cin("I.in");
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        vert[i] = point(a, b);
    }
}

void solution()
{
    VEC<int> tree;
    for (int i = 1; i <= n; ++i) {
        mini[i] = MP(INF, 0);
    }
    inTree[1] = 1;
    tree.PB(1);

    while ((int)tree.SZ != n) {
        for (int j = 1; j <= n; ++j) {
            if (inTree[j]) {
                continue;
            }
            int last = tree.back();
            double cost = get_S(vert[j], vert[last]);
            if (cost < mini[j].FF) {
                mini[j].FF = cost;
                mini[j].SS = last;
            }
        }

        int ind = 0, from = 0;
        double cost = INF;
        for (int i = 1; i <= n; ++i) {
            if (inTree[i]) {
                continue;
            }
            int it = i;
            if (mini[it].FF < cost) {
                cost = mini[it].FF;
                ind = mini[it].SS;
                from = it;
            }
        }
        inTree[from] = 1;
        tree.PB(from);
        ans += cost;
    }
}

void out()
{
    //ofstream cout("I.out");
    cout.tie(0);
    cout.precision(12);
    cout << ans << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
