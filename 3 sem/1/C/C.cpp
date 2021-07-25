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

const int MAXN = 2 * (int)1e4 + 15;

int n, m, tim;
VEC<VEC<int>> gr;
bool u[MAXN];
int tin[MAXN], tin_for_subtree[MAXN], p[MAXN];
set<int> ans;

void DFS(int v) {
    //cout << "---> " << v << "\n";
    u[v] = 1;
    tin[v] = tim;
    tin_for_subtree[v] = tim++;
    int ch = 0;
    for (int i = 0; i < gr[v].SZ; ++i) {
        int to = gr[v][i];
        if (!u[to]) {
            p[to] = v;
            DFS(to);
            tin_for_subtree[v] = min(tin_for_subtree[v], tin_for_subtree[to]);
            if (p[v] && tin_for_subtree[to] >= tin[v]) {
                ans.insert(v);
            }
            ++ch;
        } else if (to != p[v]){
            tin_for_subtree[v] = min(tin_for_subtree[v], tin[to]);
        }
    }
    if (ch > 1 && !p[v]) {
        ans.insert(v);
    }
    //cout << "<--- " << v  << "\n";
}

void in()
{
    //ifstream cin("C.in");
    cin >> n >> m;
    gr.resize(n + 5);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        gr[a].PB(b);
        gr[b].PB(a);
    }
}

void solution()
{
    for (int i = 1; i <= n; ++i) {
        if (!u[i]) {
            DFS(i);
        }
    }
}

void out()
{
    //ofstream cout("Ñ.out");
    cout << ans.SZ << "\n";
    if (ans.SZ) {
        for (auto it : ans) {
            cout << it << " ";
        }
        cout << "\n";
    }
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
