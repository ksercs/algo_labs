#include<iostream>
#include<limits.h>
#include<fstream>
  
#define name_in "salesman.in"
#define name_out "salesman.out"
#define uint unsigned int
  
using namespace std;
  
//constant
const uint n_MIN = 1;
const uint n_MAX = 18;
const uint m_MIN = 0;
const uint m_MAX = n_MAX * (n_MAX - 1) / 2;
const uint a_MIN = n_MIN;
const uint a_MAX = n_MAX;
const uint b_MIN = n_MIN;
const uint b_MAX = n_MAX;
const uint w_MIN = 1;
const uint w_MAX = 100000000; 
const uint inf = INT_MAX;
  
//global
uint n, m;
uint w[n_MAX + 1][n_MAX + 1];
uint ans;
  
uint dp[n_MAX + 1][1 << (n_MAX + 1)];
uint find_cheapest(uint i, uint mask){
    if(dp[i][mask] == inf)
        for(uint j = 0; j < n; j++)
            if(w[i][j] && ( mask & (1 << j) ))
                dp[i][mask] = min(dp[i][mask], find_cheapest(j, mask - (1 << j) ) + w[i][j] ); 
    return dp[i][mask];
}
  
uint salesman(){
    for(uint i = 0; i < n; i++)
        for(uint j = 0; j < ((uint)1 << n); j++)
            dp[i][j] = inf;
    for(uint i = 0; i < n; i++)dp[i][0] = 0;
    uint res = inf;
    for(uint i = 0; i < n; i++){
        res = min(res, find_cheapest(i, (1 << n) - 1 - (1 << i)));
    }
    return res;
}
  
void in(){
    ifstream cin(name_in);
    cin >> n >> m;
    for(uint i = 0; i < m; i++){
        uint a, b, _w;
        cin >> a >> b >> _w;
        w[a - 1][b - 1] = _w;
        w[b - 1][a - 1] = _w;
    }
}
  
void solution(){
    ans = salesman();
    /*
    for(uint i = 0; i < n; i++){
        for(uint j = 0; j < ((uint)1 << n); j++){
            if(dp[i][j] != INT_MAX)cout << dp[i][j] << " ";
            else cout << "i ";
        }
        cout << "\n";
    }
    */
}
  
void out(){
    ofstream cout(name_out);
    if(ans == inf)cout << "-1\n";
    else cout << ans << "\n";
}
  
int main(){
    in();
    solution();
    out();
    return 0;
}