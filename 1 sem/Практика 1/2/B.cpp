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

const int MAXN = 15;

int n, m, ans = INT_MAX, ansI, ansJ;
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
    int fl = 0;
    while (!fl && Ai <= n && Bi <= m ){
        int dif = abs(a[Ai]-b[Bi]);
        if (dif < ans){
            ans = dif;
            ansI = Ai;
            ansJ = Bi;
        }
        if (a[Ai] == b[Bi]) break;
        else if (a[Ai] > b[Bi]) ++Bi;
             else               ++Ai;
    }
    cout << ansI << " " << ansJ << "\n";
    return 0;
}
