#include<iostream>
#include<vector>
#include<limits.h>
#include<fstream>
  
#define name_in "knapsack.in"
#define name_out "knapsack.out"
  
using namespace std;
  
//structs_and_functions
  
  
//constant
const int n_MIN = 1;
const int n_MAX = 1000;
const int m_MIN = 1;
const int m_MAX = 10000;
const int w_MIN = 1;
const int w_MAX = 100;
const int c_MIN = 1;
const int c_MAX = 100;
const int inf = -1;
  
//global
int n, m;
int w[n_MAX + 1];
int c[n_MAX + 1];
int dp[n_MAX + 1][m_MAX + 1];
int pred[n_MAX + 1][m_MAX + 1];
vector <int> ans;
  
void in(){
    ifstream cin(name_in);
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> w[i];
    for(int i = 1; i <= n; i++)
        cin >> c[i];
}
  
void solution(){
    for(int i = 0; i <= n; i++){
        for(int j = 1; j <= m; j++){
            dp[i][j] = inf;
            pred[i][j] = -1;
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= m; j++){
            if(j - w[i] >= 0){
                if(dp[i - 1][j - w[i]] != inf){
                    if( dp[i - 1][j - w[i]] + c[i] > dp[i][j] ){
                        dp[i][j] = dp[i - 1][j - w[i]] + c[i];
                        pred[i][j] = i - 1;
                    }
                }
            }
            if(dp[i - 1][j] != inf){
                if(dp[i - 1][j] > dp[i][j]){
                    dp[i][j] = dp[i - 1][j];
                    pred[i][j] = pred[i - 1][j];
                }
            }
        }
    }
    int ind = 0;
    for(int i = 0; i <= m; i++){
        if(dp[n][ind] < dp[n][i])ind = i;
    }
    int lev = n;
    while((ind > 0)&&(lev > 0)){
        if( pred[lev][ind] != pred[lev - 1][ind] ){
            ans.push_back(lev);
            ind -= w[lev];
        }
        lev--;
    }
}
  
void out(){
    ofstream cout(name_out);
    cout << ans.size() << "\n";
    for(int i = (int)ans.size() - 1; i >= 0; i--){
        cout << ans[i] << " ";
    }
    cout << "\n";
}
  
int main(){
    in();
    solution();
    out();
    return 0;
}