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

const int MAXN = (int)1e5 + 15;

int n, m;
int sq[MAXN];
VEC <int> Lans, Rans;

int Lbin_R (int x)
{
    int L = 1, R = n, M;
    while (R-L > 0){
        M = L + (R-L)/2;
        if (sq[M] < x) L = M+1;
        else           R = M;
    }
    if (sq[L] == x) return L;
    if (sq[R] == x) return R;
    return -1;
}

int Rbin_R (int x)
{
    int L = 1, R = n, M;
    while (R-L > 1){
        M = L + (R-L)/2;
        if (sq[M] > x) R = M-1;
        else           L = M;
    }
    if (sq[R] == x)   return R;
    if (sq[L] == x)   return L;
    return -1;
}

void in()
{
    ifstream cin("binsearch.in");
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> sq[i];
    cin >> m;
    Lans.resize(m);
    Rans.resize(m);
    for (int i = 0; i < m; ++i){
        int num;
        cin >> num;
        Lans[i] = Lbin_R(num);
        Rans[i] = Rbin_R(num);
    }
}

void out()
{
    ofstream cout("binsearch.out");
    for (int i = 0; i < m; ++i)
       cout << Lans[i] << " " << Rans[i] << "\n";
}

int main()
{
    in();
    out();
    return 0;
}
