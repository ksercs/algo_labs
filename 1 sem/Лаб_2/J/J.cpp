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

int n, m, num, maxi;
LL sum;
queue <int> q;

void in()
{
    ifstream cin("bureaucracy.in");
    cin >> n >> m;
    for (int i = 0; i < n; ++i){
        int a;
        cin >> a;
        q.push(a);
        sum += a;
        maxi = max(maxi, a);
    }
}

void solution()
{
    /*if (m >= sum || maxi <= m/n){
        while (!q.empty())
            q.pop();
        return;
    }*/
    int cnt = 0;
    num = m/n;
    m = m%n;
    int c = q.SZ;
    while (cnt != c){
        ++cnt;
        if (q.front() < num)
            m += num-q.front();
        q.push(q.front());
        q.pop();
    }
    //cout << num << " " << m << "\n";
    cnt = 0;
    while (cnt < m && !q.empty()){
        if (q.front() > num){
            ++cnt;
        }
        if (q.front() > num+1){
            q.push(q.front()-1);
        }
        q.pop();
    }
    cnt = 0;
    c = q.SZ;
    while (cnt != c){
        ++cnt;
        if (q.front() - num > 0){
            q.push(q.front()-num);
        }
        q.pop();
    }
}

void out()
{
    ofstream cout("bureaucracy.out");
    if (q.SZ == 0)
        cout << "-1\n";
    else{
            cout << q.SZ << "\n";
        while (q.SZ != 1){
            cout << q.front()<< " ";
            q.pop();
        }
        cout << q.front() << "\n";
    }
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
