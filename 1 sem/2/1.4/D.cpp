#include<iostream>
#include<string.h>
#include<algorithm>
#include<fstream>
  
#define name_in "levenshtein.in"
#define name_out "levenshtein.out"
  
using namespace std;
  
//structs_and_functions
int min3(int a, int b, int c){
    return min( min(a, b), c);
}
  
//constant
const int len_MIN = 0;
const int len_MAX = 5000;
const int inf = 1000000000; 
  
//global
char f_str[len_MAX + 10];
char s_str[len_MAX + 10];
int ans;
  
int dp[len_MAX + 10][len_MAX + 10];
int levenshtein(){
    int n = strlen(f_str);
    int m = strlen(s_str);
    for(int i = 1; i <= n; i++)
        dp[i][0] = dp[i - 1][0] + 1;
    for(int j = 1; j <= m; j++)
        dp[0][j] = dp[0][j - 1] + 1;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            dp[i][j] = min3(
                dp[i - 1][j] + 1,
                dp[i][j - 1] + 1,
                dp[i - 1][j - 1] + (f_str[i - 1] == s_str[j - 1]? 0:1)
            );
        }
    }
    /*
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }
    */
    return dp[n][m];
}
  
void in(){
    ifstream cin(name_in);
    cin >> f_str >> s_str;
}
  
void solution(){
    ans = levenshtein();
}
  
void out(){
    ofstream cout(name_out);
    cout << ans << "\n";
}
  
int main(){
    in();
    solution();
    out();
    return 0;
}