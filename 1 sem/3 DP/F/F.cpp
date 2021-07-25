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

const int MAXN = 100 + 15, INF = (int)1e6;

string s;
int ans, n;
int dp[MAXN][MAXN];
set < char > op;
map <char, char> mp;

void iniz ()
{
    op.insert('(');
    op.insert('[');
    op.insert('{');
    mp['('] = ')';
    mp['['] = ']';
    mp['{'] = '}';
    for (int i = 0; i <= n+5; ++i)
        for (int j = 0; j <= n+5; ++j)
            dp[i][j] = INF;
    for (int i = 0; i <= n; ++i)
        dp[i][i] = 1;
}

int getAns(int L, int R)
{
    //cout << L << " " << R << "\n";
    if (L > R)
        return 0;
    if (R == L || dp[L][R] != INF)
        return dp[L][R];
    if (s[R] == mp[s[L]])
        dp[L][R] = min(dp[L][R], getAns(L+1, R-1));
    dp[L][R] = min(dp[L][R], getAns(L+1, R-1)+2);
    for (int i = L; i < R; ++i)
        dp[L][R] = min(dp[L][R], getAns(L, i)+getAns(i+1,R));
    //cout << L << " " << R << " : " << dp[L][R] << "\n";
    return dp[L][R];
}

void in()
{
    ifstream cin("A.in");
    cin >> s;
}

void solution()
{
    n = (int)s.SZ;
    iniz();
    getAns(0, n-1);
    ans = dp[0][n-1];
}

void out()
{
    ofstream cout("A.out");
    cout << n << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
