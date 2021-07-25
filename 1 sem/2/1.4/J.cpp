#include<iostream>
#include<cstring>
#include<algorithm>
#include<stdio.h>
  
using namespace std;
  
//constant
const int len_MIN = 0;
const int len_MAX = 10000;
const char ans[2][4] = {"NO", "YES"};
  
//global
char fstr[len_MAX + 5];
int f_len;
char sstr[len_MAX + 5];
int s_len;
char dp[len_MAX + 5][len_MAX + 5];
char ans_ind;
  
char rec_check(int i, int j){
    if(dp[i][j] == 2){
        if( (fstr[i] == sstr[j]) || (fstr[i] == '?') )dp[i][j] = rec_check(i + 1, j + 1);
        else if(fstr[i] == '*'){
            dp[i][j] = rec_check(i + 1, j);
            if(dp[i][j])return 1;
            dp[i][j] = rec_check(i + 1, j + 1);
            if(dp[i][j])return 1;
            dp[i][j] = rec_check(i, j + 1);
        }
        else if( fstr[i] != sstr[j] )dp[i][j] = 0;
    }
    return dp[i][j];
}
  
char check(){
    if((f_len == 0)&&(s_len == 0))return 1;
    if(f_len == 0)return 0;
    if(s_len == 0){
        if(fstr[0]!='*')return 0;
        else{
            for(int i = 0; i < f_len; i++)
                if(fstr[i]!='*')
                    return 0;
            return 1;
        }
    }
    return rec_check(0, 0);
}
  
void in(){
    cin >> fstr >> sstr;
}
  
void solution(){
    f_len = strlen(fstr);
    s_len = strlen(sstr);
    for(int i = 0; i <= f_len; i++)
        for(int j = 0; j <= s_len; j++)
            dp[i][j] = 2;
    for(int i = 0; i < f_len; i++)dp[i][s_len + 1] = 0;
    for(int j = 0; j < s_len; j++)dp[f_len + 1][j] = 0;
    dp[f_len][s_len] = 1;
    ans_ind = check();
    /*
    cout << " " << sstr << "\n";
    for(int i = 0; i <= f_len + 1; i++){
        cout << fstr[i];
        for(int j = 0; j <= s_len + 1; j++){
            cout << (int)dp[i][j];
        }
        cout << "\n";
    }
    */
}
  
void out(){
    cout << ans[(int)ans_ind] << "\n";
}
  
int main(){
    in();
    solution();
    out();
    return 0;
}