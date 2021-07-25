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

int n, ind;
deque <int> d[2];

void in()
{
    ifstream cin("kenobi.in");
    cin >> n;
    for (int i = 0; i < n; ++i){
        string str;
        int a;
        cin >> str;
        if (str == "add"){
            cin >> a;
            d[ind].push_front(a);
            int to = (ind+1)%2;
            if (d[ind].SZ == d[to].SZ+2){
                d[to].push_front(d[ind].back());
                d[ind].pop_back();
            }
        }
        if (str == "take"){
            if (d[ind].empty()) continue;
            int to = (ind+1)%2;
            d[ind].pop_front();
            if (d[ind].SZ < d[to].SZ) {
                d[ind].PB(d[to].front());
                d[to].pop_front();
            }
        }
        if (str == "mum!"){
            if (d[ind].empty()) continue;
            ind = (ind+1)%2;
            int to = (ind+1)%2;
            if (d[ind].SZ < d[to].SZ) {
                d[ind].PB(d[to].front());
                d[to].pop_front();
            }
        }
    }
}

void out()
{
    ofstream cout("kenobi.out");
    cout << d[0].SZ+d[1].SZ << "\n";
    int to = (ind+1)%2;
    while (!d[to].empty()){
        cout << d[to].back() << " ";
        d[to].pop_back();
    }
    //cout << "\n";
    while (!d[ind].SZ != 1){
        cout << d[ind].back() << " ";
        d[ind].pop_back();
    }
    if (!d[ind].empty()) cout << d[ind].back();
    cout << "\n";
}

int main()
{
    in();
    out();
    return 0;
}
