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

const int MAXN = (int)1e6 + 15;

int n;
int arr[MAXN];

void SiftDown (int v, int board)
{
    int MaxChild = 0,
        fl = 0;
    int L = 2*v+1, R = 2*v+2;
    while (L <= board && !fl){
        if (L == board)
            MaxChild = board;
        else
            if (arr[L] < arr[R])
                    MaxChild = L;
            else
                    MaxChild = R;
        if (arr[v] > arr[MaxChild]){
            swap(arr[v], arr[MaxChild]);
            v = MaxChild;
            L = 2*v+1, R = 2*v+2;
        }
        else    fl = 1;
    }
}

void HeapSort ()
{
    int LastLeave = n/2-1;
    for (int i = LastLeave; i >= 0; --i)
        SiftDown(i, n-1);
    for (int i = n - 1; i >= 1; i--) {
      for (int j = 0; j < n; ++j)
        cout << arr[j] << " ";
      cout << "\n";
      swap(arr[i], arr[0]);
      SiftDown(0, i-1);
    }
      for (int j = 0; j < n; ++j)
        cout << arr[j] << " ";
      cout << "\n";
}

void in()
{
    ifstream cin("input.txt");
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
}

void solution()
{
    HeapSort();
}

void out()
{
    ofstream cout("output.txt");
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
