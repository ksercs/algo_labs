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

const int MAXN = 5000 + 15;

string s1, s2;
int ans;
int dp[MAXN][MAXN];

void in()
{
    ifstream cin("input.txt");
    cin >> s1;
    cin >> s2;
}

void solution()
{
    int n = s1.SZ,
        m = s2.SZ;
    for (int i = 1; i <= m; ++i)
        dp[0][i] = i;
    for (int i = 1; i <= n; ++i)
        dp[i][0] = i;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            dp[i][j] = min( min( dp[i][j-1]+1, dp[i-1][j]+1 ),
                            dp[i-1][j-1] + (int)(s1[i-1] != s2[j-1]) );
    ans = dp[n][m];
}

void out()
{
    ofstream cout("output.txt");
    cout << ans << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
