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
#define LL long long

using namespace std;

const int MAXN = 100 + 50, INF = (int)1e6;

int n, sum, used;
int c[MAXN], dp[MAXN][MAXN];
VEC <int> ans;

void iniz ()
{
    for (int i = 0; i <= n+15; ++i)
        for (int j = 0; j <= n+15; ++j)
            dp[i][j] = INF;
    dp[0][0] = 0;
}

void DP ()
{
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            if (c[i] > 100)
                if (j)
                    dp[i][j] = min(dp[i-1][j-1] + c[i], dp[i-1][j+1]);
                else
                    dp[i][j] = dp[i-1][j+1];
            else
                dp[i][j] = min(dp[i-1][j] + c[i], dp[i-1][j+1]);
    for (int i = 0; i <= n; ++i){
        for (int j = 0; j <= n; ++j)
            cout << dp[i][j] << " ";
        cout << "\n";
    }
}

void in()
{
    //ifstream cin("A.in");
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> c[i];
    /*for (int i = 1; i <= n; ++i)
        cout << c[i] << " ";
    cout << "\n";*/
}

void solution()
{
    iniz();
    DP();
    sum = INF;
    for (int j = 0; j <= n; ++j){
        //cout << sum << "\n";
        sum = min(sum, dp[n][j]);
    }
    for (int j = 0; j <= n; ++j)
        if (dp[n][j] == sum)
            used = j;
    int j = used;
    for (int i = n; i >= 1; --i){
        if (dp[i][j] == dp[i-1][j+1]){
            ans.PB(i);
            j++;
        }
        else if (c[i] > 100 && dp[i][j] == dp[i-1][j-1]+c[i])
            --j;
    }
}

void out()
{
    //ofstream cout("A.out");
    cout << sum << "\n";
    cout << used << " " << ans.SZ << "\n";
    for (int i = ans.SZ-1; i >= 0; --i)
        cout << ans[i] << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
