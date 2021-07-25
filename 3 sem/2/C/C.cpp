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

const int MAXN = 100 + 15;
const LL INF = (LL)1e18, NON = (LL)1e5;

struct edge {
    int a;
    int b;
    LL cost;

    edge() {}
    edge(int _a, int _b, LL _c) {
        a = _a;
        b = _b;
        cost = _c;
    }
};

int n, m;
VEC <edge> gr;
LL ans[MAXN];
int p[MAXN];
int fl;
VEC<int> cycle;

void in()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    //ifstream cin("C.in");
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            LL cost;
            cin >> cost;
            if (cost != NON) {
                gr.PB(edge(i, j, cost));
                //cout << m << '\n';// system("PAUSE");
                ++m;
            }
        }
    }
//    for (auto item: gr) {
//        cout << item.a << " " << item.b << " " << item.cost << "\n";
//    }
}

void solution()
{
    for (int i = 0; i <= 2 * n; ++i) {
        fl = -1;
        for (int j = 0; j < m; ++j) {
            int a = gr[j].a;
            int b = gr[j].b;
            LL cost = gr[j].cost;
            LL new_cost = max(-INF, ans[a] + cost);
            if (ans[b] > new_cost) {
                ans[b] = new_cost;
                p[b] = a;
                fl = b;
            }
        }
    }
    if (fl != -1) {
        int vertex = fl;
		for (int i = 0; i < 2 * n; ++i) {
			vertex = p[vertex];
		}
		int tmp = vertex;
		while (1) {
            cycle.PB(tmp);
            tmp = p[tmp];
            if (tmp == vertex) {
                break;
            }
		}
		reverse(cycle.begin(), cycle.end());
        fl = 1;
    } else {
        fl = 0;
    }
}

void out()
{
    //ofstream cout("C.out");
    if (fl) {
        cout << "YES\n";
        cout << cycle.SZ << "\n";
        for (auto item : cycle) {
            cout << item << " ";
        }
    } else {
        cout << "NO\n";
    }
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
