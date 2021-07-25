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

int n, m, S, ansI, ansJ, fl;
int a[MAXN], b[MAXN];

int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    cin >> S >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= m; ++i)
        cin >> b[i];
    int Ai = 1, Bi = m;
    while (!fl && Ai <= n && Bi >= 1 ){
        int s = a[Ai] + b[Bi];
        if (s == S){
            fl = 1;
            ansI = Ai;
            ansJ = Bi;
        }
        else if (s > S) --Bi;
             else       ++Ai;
    }
    fl ? cout << ansI << " " << ansJ << "\n" : cout << "NO\n";
    return 0;
}
