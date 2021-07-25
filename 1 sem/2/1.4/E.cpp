#include<iostream>
#include<limits.h>
#include<string>
#include<algorithm>
#include<stdio.h>
  
#define name_in "matrix.in"
#define name_out "matrix.out"
#define ll long long
  
using namespace std;
  
//structs_and_functions
  
  
//constant
const int n_MIN = 1;
const int n_MAX = 400;
const int a_MIN = 1;
const int a_MAX = 100;
const int b_MIN = 1;
const int b_MAX = 100;
const ll inf = LLONG_MAX;
  
//global
int n;
ll a[n_MAX + 1];
ll b[n_MAX + 1];
ll dp[n_MAX + 1][n_MAX + 1];
int mind[n_MAX + 1][n_MAX + 1];
int op[n_MAX + 1];
int cl[n_MAX + 1];
string ans;
  
ll MCM(int l, int r){
    //cout << l << " " << r << "\n";
    if(dp[l][r] == -1){
        if(l == r - 1)dp[l][r] = 0;
        else{
            dp[l][r] = inf;
            for(int i = l + 1; i < r; i++){
                ll val = a[l]*a[i]*b[r-1] + MCM(l, i) + MCM(i, r);
                if( val < dp[l][r] ){
                    dp[l][r] = val;
                    mind[l][r] = i;
                }
                //cout << l << " " << r << " " << i << " " << val << "\n";
            }
            //cout << l << " " << r << " " << dp[l][r] << "\n";
        }
    }
    //cout << l << " " << r << " " << dp[l][r] << "\n";
    return dp[l][r];
}
  
int answer(int l, int r){
    if(l == r - 1){
        ans.erase(ans.size() - 1, 1);
        ans += 'A';
        return 1;
    }
    else if(l == r - 2)ans += "AA";
    else{
        ans += '(';
        if( !answer( l, mind[l][r] ) )ans += ')';
        ans += '(';
        if( !answer( mind[l][r], r ) )ans += ')';
    }
    return 0;
}
  
void in(){
    FILE* FIN = fopen(name_in, "r");
    fscanf(FIN, "%d", &n);
    for(int i = 0; i < n; i++)
        fscanf(FIN, "%lld%lld\n", &a[i], &b[i]);
}
  
void solution(){
    if(n > 1){
        for(int i = 0; i <= n; i++)
            for(int j = 0; j <= n; j++)
                dp[i][j] = -1;
    MCM(0, n);
    answer(0, n);
    }
}
  
void out(){
    FILE* FOUT = fopen(name_out, "w");
    if(n > 1){
        fprintf(FOUT, "(");
        for(unsigned int i = 0; i < ans.size(); i++)
            fprintf(FOUT, "%c", ans[i]);
        fprintf(FOUT, ")\n");
    }
    else fprintf(FOUT, "A\n");
}
  
int main(){
    in();
    solution();
    out();
    return 0;
}