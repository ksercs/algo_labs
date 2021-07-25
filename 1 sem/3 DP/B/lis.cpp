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
#include <climits>

#define SZ size()
#define VEC vector
#define PB push_back
#define MP make_pair
#define SS second
#define FF first
#define PII pair <int,int>
#define LL long long

using namespace std;

const int MAXN = 2000 + 15;

LL n;
LL dp[MAXN], sq[MAXN], ind[MAXN], p[MAXN];
VEC <LL> ans;

void in()
{
    //ifstream cin("lis.in");
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> sq[i];
}

void solution()
{
    dp[0] = INT_MIN;
    ind[0] = -1;
    for (int i = 1; i <= n; i++)
        dp[i] = INT_MAX;
    for (int i = 0; i < n; i++) {
        int j = upper_bound(dp, dp+n+1, sq[i]) - dp;
        if (dp[j-1] < sq[i] && sq[i] < dp[j]) {
            dp[j] = sq[i];
            ind[j] = i;
            p[i] = ind[j-1];
        }
    }
    int indx = ind[upper_bound(dp, dp+n+1, INT_MAX-1)-dp-1];
    while (indx != -1) {
        ans.PB(sq[indx]);
        indx = p[indx];
    }
}

void out()
{
    //ofstream cout("lis.out");
    cout << ans.SZ << "\n";
    for (int i = ans.SZ-1; i >= 0; --i)
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
