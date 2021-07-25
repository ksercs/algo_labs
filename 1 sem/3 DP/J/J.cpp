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

const int MAXN = 15;

LL n, len = INT_MAX;
VEC <LL> ans, v;
LL gr[MAXN][MAXN], u[MAXN];

void dfs_R(int ind, int newLen)
{
    if (ind == n){
        if (newLen < len){
            len = newLen;
            ans = v;
        }
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (!u[i]) {
            u[i] = 1;
            v[ind] = i;
            dfs_R(ind+1, newLen + ind?gr[v[ind-1]][i]:0);
            u[i] = 0;
        }
    }
}

void in()
{
    ifstream cin("A.in");
    ios_base:: sync_with_stdio(false);
    cin >> n;
    for (LL i = 1; i <= n; ++i)
        for (LL j = 1; j <= n; ++j)
            cin >> gr[i][j];
}

void solution()
{
    v.resize(n);
    dfs_R(0, 0);
    //reverse(ans.begin(), ans.end());
}

void out()
{
    ofstream cout("A.out");
    cout << len << "\n";
    for (LL i = 0; i < ans.SZ; ++i)
        cout << ans[i] << " ";
    cout << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
