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

int arr[] = {6, 5, 4, 3, 2, 1};
int n = 6;

void qsort (int b, int e)
{
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";

  int l = b, r = e;
  int piv = arr[l];
  while (l <= r)
  {
      cout << "MAIN : " << l << " " << r << "\n";
    while (arr[l] < piv){
      l++;
    cout <<"I\n";
    }
    while (arr[r] > piv){
      r--;
    cout <<"J\n";
    }
    if (l <= r)
      swap (arr[l++], arr[r--]);
  }
  if (b < r)
    qsort (b, r);
  if (e > l)
    qsort (l, e);
}

void in()
{
    //ifstream cin("input.txt");
}

void solution()
{
    qsort(0, n-1);
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
