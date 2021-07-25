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

const int MAXN = 100 + 15;

int n, ans, rt;
VEC <VEC <int> > gr;
int dp[MAXN];

int getAns (int v)
{
    if (dp[v])
        return dp[v];
    int first = 0, second = 1;
    for (int i = 0; i < gr[v].SZ; ++i){
        int to = gr[v][i];
        first += getAns(to);
        for (int j = 0; j < gr[to].SZ; ++j){
            second += getAns(gr[to][j]);
        }
    }
    return dp[v] = max(first, second);
}

void in()
{
    //ifstream cin("H.in");
    cin >> n;
    gr.resize(n+1);
    for (int i = 1; i <= n; ++i){
        int a;
        cin >> a;
        if (a)
            gr[a].PB(i);
        else
            rt = i;
    }
}

void solution()
{
    ans = getAns(rt);
}

void out()
{
    //ofstream cout("H.out");
    cout << ans << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
