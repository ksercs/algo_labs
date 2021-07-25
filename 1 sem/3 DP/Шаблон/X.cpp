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

const int MAXN = 10000 + 15;

int ans, n, m;
string tmp, s;
int dp[MAXN][MAXN];

int getAns (int i, int j)
{
    if(dp[i][j] == -1){
        if(tmp[i] == s[j] || tmp[i] == '?'){
            dp[i][j] = getAns(i+1, j+1);
            return dp[i][j];
        }
        if(tmp[i] == '*'){
            dp[i][j] = getAns(i+1, j);
            if(dp[i][j])
                return 1;
            dp[i][j] = getAns(i+1, j+1);
            if(dp[i][j])
                return 1;
            dp[i][j] = getAns(i, j+1);
            return dp[i][j];
        }
        else if(tmp[i] != s[j])
                 return dp[i][j] = 0;
    }
    return dp[i][j];
}

void check ()
{
    if (!n && !m){
        ans = 1;
        return;
    }
    if (!n)
        return;
    if (!m)
        if (tmp[0] != '*')
            return;
        else{
            for (int i = 0; i < n; ++i)
                if (tmp[i] != '*')
                    return;
            ans = 1;
            return;
        }
    ans = getAns(0, 0);
}

void iniz_DP ()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            dp[i][j] = -1;
    dp[n][m] = 1;
}

void in()
{
    ifstream cin("A.in");
    cin >> tmp >> s;
}

void solution()
{
    n = (int)tmp.SZ,
    m = (int)s.SZ;
    iniz_DP();
    check();
}

void out()
{
    ofstream cout("A.out");
    ans ? cout << "YES\n" : cout << "NO\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
