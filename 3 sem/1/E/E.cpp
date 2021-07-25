#include <iostream>
#include <fstream>
#include <unordered_map>
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

const int MAXN = 2 * (int)1e4 + 15, MAXM = 2 * (int) 1e5 + 15;

int n, m, tim, ans;
VEC<VEC<PII>> gr;
int u[MAXN], c[MAXM];
int tin[MAXN], tin_for_subtree[MAXN], p[MAXN];
set<int> jp;

void DFS(int v) {
    //cout << "---> " << v << "\n";
    u[v] = 1;
    tin[v] = tim;
    tin_for_subtree[v] = tim++;
    int ch = 0;
    for (int i = 0; i < gr[v].SZ; ++i) {
        int to = gr[v][i].FF;
        int ind = gr[v][i].SS;
        if (!u[to]) {
            p[to] = ind;
            DFS(to);
            tin_for_subtree[v] = min(tin_for_subtree[v], tin_for_subtree[to]);
            if (p[v] && tin_for_subtree[to] >= tin[v]) {
                jp.insert(v);
            }
            ++ch;
        } else if (to != p[v]){
            tin_for_subtree[v] = min(tin_for_subtree[v], tin[to]);
        }
    }
    if (ch > 1 && !p[v]) {
        jp.insert(v);
    }
    //cout << "<--- " << v  << "\n";
}

void DFS_2(int v, int col) {
    u[v] = 1;
    for (int i = 0; i < gr[v].SZ; ++i) {
        int to = gr[v][i].FF;
        int ind = gr[v][i].SS;
        if (ind == p[v]) {
            continue;
        }
        if (!u[to]) {
            if (tin_for_subtree[to] >= tin[v]) {
                //cout << v << " " << to << "\n";
                ++ans;
                c[ind] = ans;
                DFS_2(to, ans);
            } else {
                c[ind] = col;
                DFS_2(to, col);
            }
        } else if (tin[to] < tin[v]) {
            c[ind] = col;
        }
    }
}

void in()
{
    ifstream cin("E.in");
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
            DFS_2(i, ans);
        }
    }
}

void out()
{
    ofstream cout("E.out");
    cout << ans << "\n";
    for (int i = 1; i <= m; ++i) {
        cout << c[i] << " ";
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
