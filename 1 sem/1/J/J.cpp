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

const double EPS = 1e-6;

int n;
double A, B = 1e10;

bool check (double a1, double a2)
{
    double a3 = 0.0;
    for (int i = 2; i < n; i++){
        a3 = 2*(a2+1)-a1;
        a1 = a2;
        a2 = a3;
        if (a3 < EPS)
            return false;
    }
    B = a3;
    return true;
}

void bin()
{
    double L = 0, R = A, M;
    while (R - L > EPS) {
        M  = (L+R)/2;
        if (check(A, M))
            R = M;
        else
            L = M;
    }
}

int main()
{
    ifstream cin("garland.in");
    ofstream cout("garland.out");
    cin >> n >> A;
    bin();
    cout.precision(2);
    cout << fixed << B << "\n";
    return 0;
}
