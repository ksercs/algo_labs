#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <set>
#include <stack>
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

int ans;
stack <int> num;

void in()
{
    ifstream cin("postfix.in");
    char c;
    while (cin >> c){
        if (c >= '0' && c <= '9'){
           num.push(c-'0');
        }
        else{
            int b = num.top();
            num.pop();
            int a = num.top();
            num.pop();
            int ch = 0;
            if (c == '+'){
                ch = a+b;
            }
            if (c == '-'){
                ch = a-b;
            }
            if (c == '*'){
                ch = a*b;
            }
            //cout << a << " " <<b << " " <<ch << "\n";
            num.push(ch);
        }
    }
    ans = num.top();
}

void out()
{
    ofstream cout("postfix.out");
    cout << ans << "\n";
}

int main()
{
    in();
    out();
    return 0;
}
