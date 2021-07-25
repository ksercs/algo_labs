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
#include <climits>

#define SZ size()
#define VEC vector
#define PB push_back
#define MP make_pair
#define SS second
#define FF first
#define PII pair <int,int>
#define LL int

using namespace std;

const int MAXN = 15;

LL n, len;
VEC <LL> ans;
LL gr[MAXN][MAXN], dp[MAXN][1<<MAXN];

LL getAns (LL ind, LL mask){
    if(dp[ind][mask] == INT_MAX)
        for(LL j = 1; j <= n; j++)
            if( (mask & (1<<j)) ){
                cout << "MASK = " << mask << " " << ind << " " << j << "\n";
                dp[ind][mask] = min(dp[ind][mask], getAns(j, mask-(1<<j) ) + gr[ind][j] );
            }
    return dp[ind][mask];
}

void findWay (LL ind, LL mask)
{
    ans.PB(ind);
    while (mask > 1)
        for (int j = 1; j <= n; ++j)
            if ((mask & (1<<j)) && dp[ind][mask] == dp[j][mask-(1<<j)]+gr[ind][j]){
                ans.PB(j);
                ind = j;
                mask -= (1<<j);
            }
}

void in()
{
    ifstream cin("A.in");
    cin >> n;
    for (LL i = 1; i <= n; ++i)
        for (LL j = 1; j <= n; ++j)
            cin >> gr[i][j];
}

void solution()
{
    for(LL i = 0; i <= n; ++i)
        for(LL j = 0; j <= ((LL)1 << (n+1)); ++j)
            dp[i][j] = INT_MAX;
    for(LL i = 0; i <= n; ++i)
        dp[i][1] = 0;
    len = INT_MAX;
    LL ind = 0;
    for(LL i = 1; i <= n; ++i){
            cout << "ST = " << (1<<(n+1)) - 1 - (1<<i) << "\n";
        LL newLen = getAns(i, (1<<(n+1)) - 1 - (1<<i));
        cout << newLen << "\n";
        if (newLen < len){
            len = newLen;
            ind = i;
            //ans.resize(0);
            //findWay(ind, (1<<(n+1))-1-(1<<ind));
        }
    }
    //findWay(ind, (1<<n)-1-(1<<ind));
}

void out()
{
    ofstream cout("A.out");
    cout << len << "\n";
    for (LL i = ans.SZ-1; i >= 0; --i)
        cout << ans[i]+1 << " ";
    cout << "\n";
}

int main()
{
    in();
    solution();
    //out();
    return 0;
}
