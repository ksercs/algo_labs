#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int LeftChild;
    int RightChild;
    int left;
    int right;
    long long sum1;
    long long sum2;

    Node (int a, int b) {
        left = a;
        right = b;
        sum1 = 0;
        sum2 = 0;
        LeftChild = -1;
        RightChild = -1;
    }
};

vector <Node> t;

void propogate(int i)
{
    if (t[i].left == t[i].right) {
        return;
    }
    if (t[i].LeftChild == -1) {
        t[i].LeftChild = t.size();
        t.push_back(Node(t[i].left, (t[i].left+t[i].right)/2));
    }
    if (t[i].RightChild == -1) {
        t[i].RightChild = t.size();
        t.push_back(Node((t[i].left+t[i].right)/2+1, t[i].right));
    }
}

void update(int i, vector <long long> &a)
{
    if (t[i].left != t[i].right) {
        propogate(i);
        update(t[i].RightChild, a);
        update(t[i].LeftChild, a);
        t[i].sum1 = t[t[i].LeftChild].sum1 +  t[t[i].RightChild].sum1;
        t[i].sum2 = t[t[i].LeftChild].sum2 +  t[t[i].RightChild].sum2;
    } else {
        if (a.size() > t[i].left) {
            t[i].sum1 = a[t[i].left];
            t[i].sum2 = a[t[i].left]*a[t[i].left];
        }
    }
}

pair <long long, long long> search (int i, int l, int r)
{
    if (l > t[i].right || r < t[i].left){
        return make_pair(0,0);
    }
    if (t[i].left < l || t[i].right > r) {
        propogate(i);
        pair <long long, long long> p1 = search(t[i].LeftChild, l, r),
                                    p2 = search(t[i].RightChild, l, r);
        return make_pair(p1.first+p2.first, p1.second+p2.second);
    }
    return make_pair(t[i].sum1, t[i].sum2);
}

void Set(int i, int l, int r, long long x)
{
    if (l > t[i].right || r < t[i].left){
        return;
    }
    if (t[i].left < l || t[i].right > r) {
        propogate(i);
        Set(t[i].LeftChild, l, r, x);
        Set(t[i].RightChild, l, r, x);
        t[i].sum1 = t[t[i].LeftChild].sum1 +  t[t[i].RightChild].sum1;
        t[i].sum2 = t[t[i].LeftChild].sum2 +  t[t[i].RightChild].sum2;
        return;
    }
    t[i].sum1 = x;
    t[i].sum2 = x*x;
}

int Log(long long n)
{
    int res = 0;
    while (n > 0) {
        res += 1;
        n /= 2;
    }
    return res;
}

int main()
{
    ios_base:: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
    int n, m;
    cin >> n;
    t.push_back(Node(1, 1<<Log(n)));
    vector <long long> a(n+1);
    for (int i = 1; i <= n; i += 1) {
        cin >> a[i];
    }
    vector <pair <long long, long long> > dp(n+1);
    for (long long i = 1; i <= n; i += 1) {
        dp[i].first = dp[i-1].first + i;
        dp[i].second = dp[i-1].second + i*i;
    }
    update(0, a);
    cin >> m;
    for (int i = 0; i < m; i += 1) {
        int t, left, right;
        cin >> t >> left >> right;
        if (t == 1) {
            Set(0, left, left, right);
        } else{
            pair <long long, long long> p = search(0, left, right);
            if (p.first == dp[right-left+1].first && p.second == dp[right-left+1].second)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }
    return 0;
}
