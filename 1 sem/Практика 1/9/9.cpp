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

const int MAXN = 20;

int a[MAXN], b[MAXN];
int n;

void mergesort()
{
    int M, wid, R;
    int i, j, ind;

    for (int k = 2; k < n; k *= 2 ) {
        for (int L = 0; L < n - k; L += k*2 ) {
            M = L + k;
            R = min(M + k, n);
            ind = L;
            i = L;
            j = M;
            //cout << L << " " << M << " " << R << " " << ind << "\n";
            while (i < M && j < R) {
                if (a[i] <= a[j]) {
                    b[ind] = a[i];
                    i++;
                } else {
                    b[ind] = a[j];
                    j++;
                }
                ind++;
            }
            while (i < M) {
                b[ind] = a[i];
                i++;
                ind++;
            }
            while (j < R) {
                b[ind] = a[j];
                j++;
                ind++;
            }
            for (ind = L; ind < R; ind++)
                a[ind] = b[ind];
        }
    }
}

void in()
{
    ifstream cin("input.txt");
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
}

void solution()
{
    mergesort();
}

void out()
{
    ofstream cout("output.txt");
    for (int i = 0; i < n-1; ++i)
        cout << a[i] << " ";
    cout << a[n-1] << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
