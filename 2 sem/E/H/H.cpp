#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int LeftChild;
    int RightChild;
    int left;
    int right;
    long long Max;
    long long Min;

    Node (int a, int b) {
        left = a;
        right = b;
        Max = -1000000000000000000;
        Min = 1000000000000000000;
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
    t[t[i].LeftChild].Max = max(t[i].Max,t[t[i].LeftChild].Max) ;
    t[t[i].RightChild].Max = max(t[i].Max,t[t[i].RightChild].Max);
}

long long search(int i, int l, int r)
{
    if (l > t[i].right || r < t[i].left){
        return 1000000000000000000;
    }
    if (t[i].left < l || t[i].right > r) {
        return min(search(t[i].LeftChild, l, r), search(t[i].RightChild, l, r));
    }
    return t[i].Min;
}

void Set(int i, int l, int r, long long x)
{
    if (l > t[i].right || r < t[i].left){
        return;
    }
    if (t[i].left < l || t[i].right > r) {
        Set(t[i].LeftChild, l, r, x);
        Set(t[i].RightChild, l, r, x);
        return;
    }
    t[i].Max = max(x, t[i].Max);
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

vector <long long> ans;

void update(int i)
{
    propogate(i);
    if (t[i].left != t[i].right) {
        update(t[i].LeftChild);
        update(t[i].RightChild);
        t[i].Min = min(t[t[i].LeftChild].Min, t[t[i].RightChild].Min);
    } else {
        if (t[i].Max == -1000000000000000000)
            t[i].Min = (1LL<<31)-1;
        else
            t[i].Min = t[i].Max;
        if (t[i].left < ans.size())
            ans[t[i].left] = t[i].Min;
    }
}

void upd (int i)
{
    if (t[i].left == t[i].right)
        return;
    if (t[i].LeftChild == -1) {
        t[i].LeftChild = t.size();
        t.push_back(Node(t[i].left, (t[i].left+t[i].right)/2));
        upd(t[i].LeftChild);
    }
    if (t[i].RightChild == -1) {
        t[i].RightChild = t.size();
        t.push_back(Node((t[i].left+t[i].right)/2+1, t[i].right));
        upd(t[i].RightChild);
    }

}

struct tpl
{
    int a;
    int b;
    int c;
    tpl (int d, int e, int f) {
        a = d;
        b = e;
        c = f;
    }

    tpl(){}
};

int main()
{
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    ans.resize(n+1);
    t.push_back(Node(1, 1<<Log(n)));
    vector <tpl> q(m);
    upd(0);
    for (int i = 0; i < m; i += 1) {
        int left, right, answer;
        cin >> left >> right >> answer;
        q[i] = tpl(left, right, answer);
        Set(0, left, right, answer);
    }
    update(0);
    int fl = 1;
    for (int i = 0; i < m; i += 1) {
        if (search(0, q[i].a, q[i].b) != q[i].c)
            fl = 0;
    }
    if (fl == 0)
        cout << "inconsistent\n";
    else{
        cout << "consistent\n";
        for (int i = 1; i <= n; i += 1)
            cout << ans[i] << " ";
        cout << "\n";
    }
    return 0;
}
