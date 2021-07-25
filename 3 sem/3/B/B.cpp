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

string s;
VEC <int> pref;

void in()
{
//    ifstream cin("B.in");
    cin >> s;
}

void solution()
{
    pref.resize(s.SZ);
    for (int i = 1; i < s.SZ; ++i) {
        int ind = pref[i - 1];
        while (ind > 0 && s[i] != s[ind]) {
            ind = pref[ind - 1];
        }
        if (s[i] == s[ind]) {
            ++ind;
        }
        pref[i] = ind;
    }
}

void out()
{
//    ofstream cout("B.out");
    for (auto it : pref) {
        cout << it << " ";
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
