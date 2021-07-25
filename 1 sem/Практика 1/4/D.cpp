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

const int MAXN = 15;

int n, m, ans;
int a[MAXN], b[MAXN];

int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= m; ++i)
        cin >> b[i];
    int Ai = 1, Bi = 1;
    while ( Ai <= n && Bi <= m ){
        if (a[Ai] > b[Bi]) ++Bi;
        if (a[Ai] < b[Bi]) ++Ai;
        if (a[Ai] == b[Bi]){
            int ch = a[Ai];
            int cnt = 0;
            while (a[Ai] == b[Bi] && Bi <= m){
                ++cnt;
                ++Bi;
            }
            while (a[Ai] == ch && Ai <= n){
                ans += cnt;
                ++Ai;
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
