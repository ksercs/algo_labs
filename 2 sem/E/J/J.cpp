#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int LeftChild;
    int RightChild;
    int left;
    int right;
    int Min;
    bool isSet;
    int set;

    Node (int a, int b) {
        left = a;
        right = b;
        isSet = 0;
        set = 0;
        Min = 0;
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
        t[t[i].LeftChild].set = max(t[i].set, t[t[i].LeftChild].set);
        t[t[i].RightChild].set = max(t[i].set, t[t[i].RightChild].set);
        t[t[i].LeftChild].Min = max(t[t[i].LeftChild].Min, t[i].set);
        t[t[i].RightChild].Min = max(t[t[i].RightChild].Min, t[i].set);
    }
}

int search (int i, int l, int r)
{
    if (l > t[i].right || r < t[i].left){
        return -1;
    }
    if (t[i].left < l || t[i].right > r) {
        propogate(i);
        int i1 = search(t[i].LeftChild, l, r),
            i2 =  search(t[i].RightChild, l, r);
        if (i1 > i2)
            swap(i1, i2);
        if (i1 != -1 && t[i1].Min < t[i2].Min)
            return i1;
        else
            return i2;
    }
    return i;
}

void Set(int i, int l, int r, int x)
{
    if (l > t[i].right || r < t[i].left){
        return;
    }
    if (t[i].left < l || t[i].right > r) {
        propogate(i);
        Set(t[i].LeftChild, l, r, x);
        Set(t[i].RightChild, l, r, x);
        t[i].Min = min(t[t[i].LeftChild].Min, t[t[i].RightChild].Min);
        return;
    }
    t[i].Min = max(t[i].Min, x);
    t[i].isSet = 1;
    t[i].set = max(x, t[i].set);
}

int Search (int i)
{
    if (t[i].left == t[i].right)
        return t[i].left;
    propogate(i);
    if (t[i].Min == t[t[i].LeftChild].Min)
        return Search(t[i].LeftChild);
    return Search(t[i].RightChild);
}

int Log(int n)
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
    //freopen("J.in", "r", stdin);
    //freopen("J.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    t.push_back(Node(1, 1<<Log(n)));
    string s;
    for (int i = 0; i < m; i += 1) {
        cin >> s;
        if (s == "defend") {
            int left, right, x;
            cin >> left >> right >> x;
            Set(0, left, right, x);
        }
        if (s == "attack") {
            int left, right;
            cin >> left >> right;
            int v = search(0, left, right);
            cout << t[v].Min << " " << Search(v) << "\n";
        }
    }
    return 0;
}
