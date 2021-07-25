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

LL n, len;
VEC <LL> ans, v;
LL gr[MAXN][MAXN], dp[MAXN][1<<MAXN];

VEC <LL> getAns (LL ind, LL mask, VEC <LL>& vec){
    /*if(dp[ind][mask] != INT_MAX)
        return dp[ind][mask];*/
    int indx = -1;
    for(LL j = 0; j < n; j++)
        if(gr[ind][j] && (mask & (1<<j)) ){

            LL newLen = getAns(j, mask-(1<<j), vec) + gr[ind][j];
            if (newLen  < dp[ind][mask]){
                dp[ind][mask] = newLen;
                indx = ((mask-(1<<j))^mask);
            }
            vec.PB(indx);
        }
    return vec;
}

void in()
{
    ifstream cin("A.in");
    cin >> n;
    for (LL i = 0; i < n; ++i)
        for (LL j = 0; j < n; ++j)
            cin >> gr[i][j];
}

void solution()
{
    for(LL i = 0; i < n; ++i)
        for(LL j = 0; j < ((LL)1 << n); ++j)
            dp[i][j] = INT_MAX;
    for(LL i = 0; i < n; ++i)
        dp[i][0] = 0;
    len = INT_MAX;
    for(LL i = 0; i < n; ++i){
        LL newLen = dp[i][(1<<n) - 1 - (1<<i)];
        v = getAns(i, (1<<n) - 1 - (1<<i));
        if (newLen < len){
            len = newLen;
            ans = v;
        }
        v.clear();
    }
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
