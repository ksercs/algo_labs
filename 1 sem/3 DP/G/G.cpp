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

string s, ans;
int n;
string dp[MAXN][MAXN];
map <char, char> mp;

string getMax(string s1, string s2)
{
    if (s1.SZ < s2.SZ)
        return s2;
    return s1;
}

void iniz ()
{
    mp['('] = ')';
    mp['['] = ']';
    mp['{'] = '}';
    for (int i = 0; i <= n+5; ++i)
        for (int j = 0; j <= n+5; ++j)
            dp[i][j] = "#";
    for (int i = 0; i <= n; ++i)
        dp[i][i] = "";
}

string getAns(int L, int R)
{
    //cout << L << " " << R << "\n";
    if (R == L || dp[L][R] != "#")
        return dp[L][R];
    dp[L][R] = "";
    if (s[R] == mp[s[L]])
        dp[L][R] = getMax(dp[L][R], s.substr(L,1)+getAns(L+1, R-1)+s.substr(R,1));
    for (int i = L; i < R; ++i)
        dp[L][R] = getMax(dp[L][R], getAns(L, i)+getAns(i+1,R));
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
    cout << ans.SZ << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
