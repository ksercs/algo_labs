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

const int MAXN = 2 * (int) 1e5 + 15, INF = int(1e9)+15;

struct edge {
    int a;
    int b;
    LL cost;

    edge() {}
    edge(int _a, int _b, LL _c) : a(_a), b(_b), cost(_c) {
    }
};

int n, m;
LL ans;
int p[MAXN], r[MAXN];
VEC<edge> ed;

void make_set(int a)
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
        int a = find_set(ed[i].a);
        int b = find_set(ed[i].b);

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

void in()
{
    //ifstream cin("J.in");
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b;
        LL c;
        cin >> a >> b >> c;
        ed.PB(edge(a, b, c));
    }
}

void solution()
{
    sort(ed.begin(), ed.end(), comp);
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
    }
    kruskal();
}

void out()
{
   // ofstream cout("J.out");
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
