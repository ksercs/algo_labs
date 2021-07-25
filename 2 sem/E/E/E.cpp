#include <bits/stdc++.h>

using namespace std;

struct matrix
{
    int a;
    int b;
    int c;
    int d;

    matrix(int e, int f, int g, int h) {
        a = e;
        b = f;
        c = g;
        d = h;
    }

    matrix() {
        a = 1;
        b = 0;
        c = 0;
        d = 1;
    }
};

struct Node
{
    int LeftChild;
    int RightChild;
    int left;
    int right;
    matrix m;

    Node (int a, int b) {
        left = a;
        right = b;
        LeftChild = -1;
        RightChild = -1;
        m = matrix();
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

matrix Plus (matrix m1, matrix m2, int r)
{
    matrix ans;
    ans.a = (1LL*m1.a*m2.a + 1LL*m1.b*m2.c)%r;
    ans.b = (1LL*m1.a*m2.b + 1LL*m1.b*m2.d)%r;
    ans.c = (1LL*m1.c*m2.a + 1LL*m1.d*m2.c)%r;
    ans.d = (1LL*m1.c*m2.b + 1LL*m1.d*m2.d)%r;
    return ans;
}

void update(int i, vector <matrix> &a, int r)
{
    if (t[i].left != t[i].right) {
        propogate(i);
        update(t[i].RightChild, a, r);
        update(t[i].LeftChild, a, r);
        t[i].m = Plus(t[t[i].LeftChild].m, t[t[i].RightChild].m, r);
    } else {
        if (a.size() > t[i].left) {
            t[i].m = a[t[i].left];
        }
    }
}

matrix search (int i, int l, int r, int mod)
{
    if (l > t[i].right || r < t[i].left){
        return matrix();
    }
    if (t[i].left < l || t[i].right > r) {
        propogate(i);
        return Plus(search(t[i].LeftChild, l, r, mod), search(t[i].RightChild, l, r, mod), mod);
    }
    return t[i].m;
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
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);
    int r, n, m;
    cin >> r >> n >> m;
    vector <matrix> a(n+1);
    t.push_back(Node(1, 1<<Log(n)));
    for (int i = 1; i <= n; i += 1) {
        int a1, b, c, d;
        cin >> a1 >> b >> c >> d;
        a[i] = matrix(a1,b,c,d);
    }
    update(0, a, r);
    for (int i = 0; i < m; i += 1) {
        int left, right;
        cin >> left >> right;
        matrix ans = search(0, left, right, r);
        cout << ans.a << " " << ans.b << "\n" << ans.c << " " << ans.d << "\n";
    }
    return 0;
}
