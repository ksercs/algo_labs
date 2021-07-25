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

int n, k;
int arr[MAXN];

void in()
{
    ifstream cin("input.txt");
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
}

void solution()
{
    for (int i = 2; i <= n; ++i){
        for (int k = 1; k <= n; ++k)
            cout << arr[k] << " ";
        cout << "\n";
        if (arr[i] < arr[i-1]){
            int ind = i-1;
            while (arr[i] < arr[ind] && ind > 1){
                swap(arr[i], arr[ind]);
                --ind;
            }
        }
    }
        for (int k = 1; k <= n; ++k)
            cout << arr[k] << " ";
        cout << "\n";
}

void out()
{
    ofstream cout("output.txt");
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
