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

const int MAXN = 2000 + 15;

int n, m;
int a[MAXN], b[MAXN];
int dp[MAXN][MAXN];
VEC <int> ans;

void in()
{
    //ifstream cin("lcs.in");
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    cin >> m;
    for (int j = 1; j <= m; ++j)
        cin >> b[j];
}

void solution()
{
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            (a[i] == b[j]) ?
                dp[i][j] = dp[i-1][j-1]+1 : dp[i][j]= max(dp[i-1][j], dp[i][j-1]);
    int i = n, j = m;
    while (dp[i][j] != 0){
        while (dp[i][j-1] == dp[i][j])
            j--;
        while (dp[i-1][j] == dp[i][j])
            i--;
        ans.PB(a[i]);
        i--;
        j--;
    }
    reverse(ans.begin(), ans.end());
}

void out()
{
    //ofstream cout("lcs.out");
    //cout << ans.SZ << "\n";
    for (int i = 0; i < ans.SZ-1; ++i)
        cout << ans[i] << " ";
    cout << ans.back() << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
