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

const int MAXN = 600;

int n, m;
VEC <VEC <int> > gr;
VEC < PII > ans;
int u[MAXN], num[MAXN];

int DFS (int v)
{
    if (u[v])
        return 0;
    u[v] = 1;
    for (int i = 0; i < gr[v].SZ; ++i){
        int to = gr[v][i];
        if (!num[to] || DFS(num[to])){
            num[to] = v;
            return 1;
        }
    }
    return 0;
}

void in()
{
    //ifstream cin("I.in");
    cin >> n >> m;
    gr.resize(n+m+1);
    for (int i = 1; i <= n; ++i){
        int a = 1;
        while (1){
            cin >> a;
            if (!a)
                break;
            //cout << a << "\n";
            gr[i].PB(n+a);
            gr[n+a].PB(i);
        }
    }
}

void solution()
{
    for (int i = 1; i <= n+m; ++i){
        DFS(i);
        memset(u, 0, sizeof(u));
    }
    for (int i = 1; i <= n; ++i)
        if (num[i])
            ans.PB(MP(i, num[i]-n));
}

void out()
{
    //ofstream cout("I.out");
    cout << ans.SZ << "\n";
    for (int i = 0; i < ans.SZ; ++i)
        cout << ans[i].FF << " " << ans[i].SS << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
