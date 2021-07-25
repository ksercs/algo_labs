#include <stdio.h>
#include <string.h>
#include <algorithm>
 
#define f_in "palindrome.in"
#define f_out "palindrome.out"
 
using namespace std;
 
//constants
const int   len_MIN = 1,
            len_MAX = 2000;
 
//global
int len;
char str[len_MAX], answer[len_MAX];
int dp[len_MAX][len_MAX];
int answer_length;
 
void in() {
    freopen(f_in, "r", stdin);
    scanf("%2000s", str);
}
 
int palindrom(int i, int j) {
    if (i > j) {
        return 0;
    }
    if (dp[i][j] == 0) {
        if (i == j) {
            dp[i][j] = 1;
        } else {
            if (str[i] == str[j]) {
                dp[i][j] = palindrom(i + 1, j - 1) + 2;
            } else {
                dp[i][j] = max(palindrom(i, j - 1), palindrom(i + 1, j));
            }
        }
    }
    return dp[i][j];
}
 
void solution() {
    len = strlen(str);
    answer_length = palindrom(0, len - 1);
    int ind = 0;
    int i = 0, j = len - 1;
    while (dp[i][j] > 0) {
        printf("%d %c %d %c\n", i, str[i], j, str[j]);
        if (str[i] == str[j]) {
            answer[ind++] = str[i];
            i++;
            j--;
        } else {
            if (dp[i + 1][j] > dp[i][j - 1]) {
                i++;
            } else {
                j--;
            }
        }
    }
    int parity = answer_length & 1;
    for(int i = strlen(answer) - parity - 1; i >= 0; i--) {
        answer[ind++] = answer[i];
    }
    printf("  ");
    for (int i = 0; i < len; i++) {
        printf("%c ", str[i]);
    }
    printf("\n");
    for (int i = 0; i < len; i++) {
        printf("%c ", str[i]);
        for (int j = 0; j < len; j++) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }
}
 
void out() {
    freopen(f_out, "w", stdout);
    printf("%d\n%s\n", answer_length, answer);
}
 
int main() {
    in();
    solution();
    out();
    return 0;
}