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

int n, m, ans, prevM;

void in()
{
    ifstream cin("nice.in");
    cin >> n >> m;
    if (n < m)
        swap(n, m);
}

void getAns (VEC <VEC <int> >& dp, int i, int j, int mask) {
  cout << i << " " << j << " " << mask << "\n";
  if (j == m){
    dp[i][mask] += dp[i-1][prevM];
    cout << "END\n\n";
  }
  else {
    int L = mask & (1 << (j-1)),
        up = prevM & (1 << j),
        diag = prevM & (1 << (j-1));
    cout << "S : " << L  << " " << up << " " << diag << "\n";
    if (!j || L || up || diag)
        getAns(dp, i, j+1, mask);
    if (!j || !L || !up || !diag)
        getAns(dp, i, j+1, (mask|(1<<j)));
  }
}

void solution()
{
    VEC < VEC <int> > dp (n);
    for (int i = 0; i < n; ++i)
        dp[i].resize(1<<m);
    for (int i = 0; i < dp[0].SZ; ++i)
        dp[0][i] = 1;
    for (int i = 1; i < n; ++i)
        for (int mask = 0; mask < (int)(1<<m); ++mask){
            prevM = mask;
            if (dp[i-1][prevM]){
                cout << "ST : " << mask << "\n";
                getAns(dp, i, 0, 0);
            }
        }
    for (int i = 0; i < dp[n-1].SZ; ++i)
        ans += dp[n-1][i];
}

void out()
{
    ofstream cout("nice.out");
    cout << ans << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
