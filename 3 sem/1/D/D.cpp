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

const int MAXN = 2 * (int)1e4 + 15;

int n, m, tim = 1, ans;
VEC<VEC<PII>> gr;
int u[MAXN];
int tin[MAXN], tin_for_subtree[MAXN], p[MAXN];
set<int> br;

void DFS_2(int v) {
    u[v] = ans;
    for (int i = 0; i < gr[v].SZ; ++i) {
        int to = gr[v][i].FF;
        int ind = gr[v][i].SS;
        if ((!u[to]) && (!br.count(ind))) {
            DFS_2(to);
        }
    }
}

void DFS(int v) {
    u[v] = 1;
    tin[v] = tim;
    tin_for_subtree[v] = tim++;
    for (int i = 0; i < gr[v].SZ; ++i) {
        int to = gr[v][i].FF;
        int ind = gr[v][i].SS;
        if (!u[to]) {
            p[to] = v;
            DFS(to);
            tin_for_subtree[v] = min(tin_for_subtree[v], tin_for_subtree[to]);
            if (tin_for_subtree[to] > tin[v]) {
                br.insert(ind);
            }
        } else if (to != p[v]){
            tin_for_subtree[v] = min(tin_for_subtree[v], tin[to]);
        }
    }
}

void in()
{
    ifstream cin("D.in");
    cin >> n >> m;
    gr.resize(n + 5);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        gr[a].PB({b, i});
        gr[b].PB({a, i});
    }
}

void solution()
{
    for (int i = 1; i <= n; ++i) {
        if (!u[i]) {
            DFS(i);
        }
    }

    for (int i = 0; i <= n; ++i) {
        u[i] = 0;
    }

    for (int i = 1; i <= n; ++i) {
        if (!u[i]) {
            ++ans;
            DFS_2(i);
        }
    }
}

void out()
{
    ofstream cout("D.out");
    cout << ans << "\n";
    for (int i = 1; i <= n; ++i) {
        cout << u[i] << " ";
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
