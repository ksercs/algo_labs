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

string str;
VEC <int> z;

void in()
{
//    ifstream cin("Ñ.in");
    cin >> str;
}

void solution()
{
    z.resize(str.SZ);

    int L = 0,
        R = 0;

    for (int i = 1; i < str.SZ; ++i) {
//        cout << i << " : " << L << " " << R << "\n";
        if (i <= R) {
            z[i] = min(z[i - L], R - i + 1);
        }
        while (i + z[i] < str.SZ && str[z[i]] == str[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > R) {
            L = i;
            R = i + z[i] - 1;
        }
    }
}

void out()
{
//    ofstream cout("Ñ.out");
    for (int i = 1; i < str.SZ; ++i) {
        cout << z[i] << " ";
    }
    cout << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
