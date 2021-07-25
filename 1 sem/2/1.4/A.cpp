#include <stdio.h>
#include <vector>
#include <algorithm>
 
#define f_in "lis.in"
#define f_out "lis.out"
 
using namespace std;
 
//constants
const int   n_MIN = 1,
            n_MAX = 5000,
            a_MIN = -1e9,
            a_MAX = 1e9,
            infinity = a_MAX << 1;
 
//global
int n, a[n_MAX + 1];
int dp[n_MAX + 1];
int ind_in_a[n_MAX + 1];
int p[n_MAX + 1];
vector <int> answer;
 
void in() {
    freopen(f_in, "r", stdin);
    scanf("%d\n", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
}
 
void dp_reset() {
    dp[0] = -infinity;
    ind_in_a[0] = -1;
    for (int i = 1; i <= n; i++) {
        dp[i] = infinity;
    }
}
 
void lis() {
    for (int i = 0; i < n; i++) {
        int j = (int)( upper_bound(dp, dp + n + 1, a[i]) - dp );
        if (dp[j - 1] < a[i] && a[i] < dp[j]) {
            dp[j] = a[i];
            ind_in_a[j] = i;
            p[i] = ind_in_a[j - 1];
        }
    }
}
 
void solution() {
    dp_reset();
    lis();
    int ind = ind_in_a[(int)(upper_bound(dp, dp + n + 1, infinity - 1) - dp) - 1];
    int i = 0;
    while (ind != -1) {
        answer.push_back(a[ind]);
        ind = p[ind];
        i++;
    }
    reverse(answer.begin(), answer.end());
}
 
void out() {
    freopen(f_out, "w", stdout);
    printf("%d\n", (int)answer.size());
    for (int i = 0; i < answer.size(); i++) {
        printf("%d ", answer[i]);
    }
}
 
int main() {
    in();
    solution();
    out();
    return 0;
}