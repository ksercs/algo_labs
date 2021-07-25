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

const int MAXN = 100 + 15, MOD = (int)1e9;

LL n, ans;
LL dp[15][MAXN];
VEC <VEC <int> > gr(15);

void in()
{
    //ifstream cin(".in");
    cin >> n;
}

LL getAns (int last, int v)
{
    if (dp[last][v] || v == 1 && (last == 0 || last == 8))
        return dp[last][v]%MOD;
    for (int j = 0; j < gr[last].SZ; ++j){
        int to = gr[last][j];
        dp[last][v] = (dp[last][v]+getAns(to, v-1)%MOD)%MOD;
    }
    return dp[last][v]%MOD;
}

void solution()
{
    gr[1].PB(6);
    gr[1].PB(8);
    gr[2].PB(7);
    gr[2].PB(9);
    gr[3].PB(4);
    gr[3].PB(8);
    gr[4].PB(3);
    gr[4].PB(9);
    gr[4].PB(0);
    gr[6].PB(1);
    gr[6].PB(7);
    gr[6].PB(0);
    gr[7].PB(2);
    gr[7].PB(6);
    gr[8].PB(1);
    gr[8].PB(3);
    gr[9].PB(4);
    gr[9].PB(2);
    gr[0].PB(4);
    gr[0].PB(6);
    for (int i = 1; i <= 9; ++i)
        if (i != 8)
            dp[i][1] = 1;
    for (int i = 0; i < 10; ++i)
        ans = (ans+getAns(i, n)%MOD)%MOD;
}

void out()
{
    //ofstream cout(".out");
    cout << ans << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
