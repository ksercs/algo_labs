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

int n;
int gr[MAXN][MAXN];

void in()
{
    //ifstream cin("A.in");
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> gr[i][j];
        }
    }
}

void solution()
{
    for (int k = 1; k <= n; ++k) {
        for (int v = 1; v <= n; ++v) {
            for (int u = 1; u <= n; ++u) {
                gr[u][v] = min(gr[u][v], gr[u][k] + gr[k][v]);
            }
        }
    }
}

void out()
{
    //ofstream cout("A.out");
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << gr[i][j] << " ";
        }
        cout << "\n";
    }
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
