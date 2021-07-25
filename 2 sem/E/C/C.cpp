#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int LeftChild;
    int RightChild;
    int left;
    int right;
    long long min;
    bool isSet;
    bool isAdd;
    long long set;
    long long add;

    Node (int a, int b) {
        left = a;
        right = b;
        min = 1000000000000000000;
        isSet = 0;
        isAdd = 0;
        add = 0;
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
    if (t[i].isSet) {
        t[i].isSet = 0;
        t[t[i].LeftChild].isSet = 1;
        t[t[i].RightChild].isSet = 1;
        t[t[i].LeftChild].set = t[i].set;
        t[t[i].RightChild].set = t[i].set;
        t[t[i].LeftChild].isAdd = 0;
        t[t[i].RightChild].isAdd = 0;
        t[t[i].LeftChild].add = 0;
        t[t[i].RightChild].add = 0;
        t[t[i].LeftChild].min = t[i].set;
        t[t[i].RightChild].min = t[i].set;
    }
    if (t[i].isAdd) {
        t[i].isAdd = 0;
        t[t[i].LeftChild].isAdd = 1;
        t[t[i].RightChild].isAdd = 1;
        t[t[i].LeftChild].add += t[i].add;
        t[t[i].RightChild].add += t[i].add;
        t[t[i].LeftChild].min += t[i].add;
        t[t[i].RightChild].min += t[i].add;
        t[i].add = 0;
    }
}

void update(int i, vector <long long> &a)
{
    if (t[i].left != t[i].right) {
        propogate(i);
        update(t[i].RightChild, a);
        update(t[i].LeftChild, a);
        t[i].min = min(t[t[i].LeftChild].min, t[t[i].RightChild].min);
    } else {
        if (a.size() > t[i].left) {
            t[i].min = a[t[i].left];
        }
    }
}

long long search (int i, int l, int r)
{
    if (l > t[i].right || r < t[i].left){
        return 1000000000000000000;
    }
    if (t[i].left < l || t[i].right > r) {
        propogate(i);
        return min(search(t[i].LeftChild, l, r), search(t[i].RightChild, l, r));
    }
    return t[i].min;
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
        t[i].min = min(t[t[i].LeftChild].min, t[t[i].RightChild].min);
        return;
    }
    t[i].min = x;
    t[i].isSet = 1;
    t[i].isAdd = 0;
    t[i].set = x;
    t[i].add = 0;
}

void Add(int i, int l, int r, long long x)
{
    if (l > t[i].right || r < t[i].left){
        return;
    }
    if (t[i].left < l || t[i].right > r) {
        propogate(i);
        Add(t[i].LeftChild, l, r, x);
        Add(t[i].RightChild, l, r, x);
        t[i].min = min(t[t[i].LeftChild].min, t[t[i].RightChild].min);
        return;
    }
    t[i].min += x;
    t[i].isAdd = 1;
    t[i].add += x;
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
    freopen("rmq2.in", "r", stdin);
    freopen("rmq2.out", "w", stdout);
    int n;
    cin >> n;
    t.push_back(Node(1, 1<<Log(n)));
    vector <long long> a(n+1);
    for (int i = 1; i <= n; i += 1) {
        cin >> a[i];
    }
    update(0, a);
    string s;
    while (cin >> s) {
        if (s == "min") {
            int left, right;
            cin >> left >> right;
            cout << search(0, left, right) << "\n";
        }
        if (s == "set") {
            int left, right;
            long long num;
            cin >> left >> right >> num;
            Set(0, left, right, num);
        }
        if (s == "add") {
            int left, right;
            long long num;
            cin >> left >> right >> num;
            Add(0, left, right, num);
        }
    }
    return 0;
}
