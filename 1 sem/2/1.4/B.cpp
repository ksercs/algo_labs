#include <stdio.h>
#include <vector>
#include <algorithm>
 
#define f_in "lcs.in"
#define f_out "lcs.out"
 
using namespace std;
 
//functions
void read_sequence(int *len, vector<int> *s) {
    scanf("%d\n", len);
    for (int i = 0; i < (*len); i++) {
        int num;
        scanf("%d", &num);
        s->push_back(num);
    }
}
 
vector<int> *LCS(vector <int> &a, vector <int> &b) {
    int dp[a.size() + 1][b.size() + 1];
    pair <int, int> p[a.size() + 1][b.size() + 1];
    for (int i = 0; i <= a.size(); i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= b.size(); j++) {
        dp[0][j] = 0;
    }
    for (int i = 1; i <= a.size(); i++) {
        for (int j = 1; j <= b.size(); j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                p[i][j] = make_pair(i - 1, j - 1);
            } else {
                if (dp[i - 1][j] >= dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                    p[i][j] = make_pair(i - 1, j);
                } else {
                    dp[i][j] = dp[i][j - 1];
                    p[i][j] = make_pair(i, j - 1);
                }
            }
        }
    }
    int i = a.size(), j = b.size();
    vector <int> *answer = new vector <int>();
    while (i != 0 && j != 0) {
        if ( p[i][j] == make_pair(i - 1, j - 1) ) {
            answer->push_back(a[i - 1]);
            i--; j--;
        } else {
            if (p[i][j] == make_pair(i - 1, j)) {
                i--;
            } else {
                j--;
            }
        }
    }
    reverse(answer->begin(), answer->end());
    return answer;
}
 
//constants
const int   n_MIN = 1,
            n_MAX = 2000,
            a_MIN = -1e9,
            a_MAX = 1e9,
            m_MIN = 1,
            m_MAX = 2000,
            b_MIN = -1e9,
            b_MAX = 1e9;
 
//global
int n, m;
vector <int> a, b;
vector <int> *answer;
 
void in() {
    freopen(f_in, "r", stdin);
    read_sequence(&n, &a);
    read_sequence(&m, &b);
}
 
void solution() {
    answer = LCS(a, b);
}
 
void out() {
    freopen(f_out, "w", stdout);
    printf("%d\n", (int)answer->size());
    for (int i = 0; i < answer->size(); i++) {
        printf("%d ", (*answer)[i]);
    }
    printf("\n");
}
 
int main() {
    in();
    solution();
    out();
    return 0;
}