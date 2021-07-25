#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int LeftChild;
    int RightChild;
    int left;
    int right;
    long long Max;
    long long sum;
    bool isSet;
    long long set;

    Node (int a, int b) {
        left = a;
        right = b;
        Max = 0;
        isSet = 0;
        sum = 0;
        set = 0;
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
        t[t[i].LeftChild].Max = t[i].set*(t[t[i].LeftChild].right - t[t[i].LeftChild].left + 1);
        t[t[i].RightChild].Max = t[i].set*(t[t[i].RightChild].right-t[t[i].RightChild].left+1);
        t[t[i].LeftChild].sum = t[i].set*(t[t[i].LeftChild].right - t[t[i].LeftChild].left + 1);
        t[t[i].RightChild].sum = t[i].set*(t[t[i].RightChild].right-t[t[i].RightChild].left+1);
    }
}


long long search (int i, long long h)
{
    if (t[i].left == t[i].right) {
        if (t[i].Max > h)
            return t[i].left-1;
        return t[i].left;
    }
    propogate(i);
    propogate(t[i].LeftChild);
    propogate(t[i].RightChild);
    if (t[t[i].LeftChild].Max > h)
        return search(t[i].LeftChild, h);
    else
        return search(t[i].RightChild, h-t[t[i].LeftChild].sum);
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
        t[i].Max = max(t[t[i].LeftChild].Max, t[t[i].LeftChild].sum + t[t[i].RightChild].Max);
        t[i].sum = t[t[i].LeftChild].sum + t[t[i].RightChild].sum;
        return;
    }
    t[i].Max = x*(t[i].right-t[i].left+1);
    t[i].sum = x*(t[i].right-t[i].left+1);
    t[i].isSet = 1;
    t[i].set = x;
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
    //freopen("I.in", "r", stdin);
    //freopen("I.out", "w", stdout);
    int n;
    cin >> n;
    t.push_back(Node(1, 1<<Log(n)));
    string s;
    while (cin >> s) {
        if (s == "E")
            return 0;
        if (s == "I") {
            int left, right, x;
            cin >> left >> right >> x;
            Set(0, left, right, x);
        } else {
            int x;
            cin >> x;
            int ans = search(0, x);
            cout << min(ans, n) << "\n";
        }
    }
    return 0;
}
