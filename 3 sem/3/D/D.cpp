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

string s, t;
VEC <int> ans;
VEC <int> pref;

void in()
{
//    ifstream cin("D.in");
    cin >> s >> t;
}

void solution()
{
    string str = s + '$' + t;
    int n = str.SZ;
    pref.resize(n);

    for (int i = 1; i < n; ++i) {
        int ind = pref[i - 1];
        while (ind > 0 && str[i] != str[ind]) {
            ind = pref[ind - 1];
        }
        if (str[i] == str[ind]) {
            ++ind;
        }
        pref[i] = ind;
    }

    int st = 2 * s.SZ;
    for (int i = 0; st + i < n; ++i) {
        if (pref[st + i] == s.SZ) {
            ans.PB(i + 1);
        }
    }
}

void out()
{
//    ofstream cout("D.out");
    cout << ans.SZ << "\n";
    for (auto it : ans) {
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
