#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int LeftChild;
    int RightChild;
    int left;
    int right;
    int sum;
    int seg;
    int set;

    Node (int a, int b) {
        left = a;
        right = b;
        sum = 0;
        seg = 0;
        set = -1;
        LeftChild = -1;
        RightChild = -1;
    }
};

vector <Node> t;

void propogate(int i)
{
    if (t[i].LeftChild == -1) {
        t[i].LeftChild = t.size();
        t.push_back(Node(t[i].left, (t[i].left+t[i].right)/2));
    }
    if (t[i].RightChild == -1) {
        t[i].RightChild = t.size();
        t.push_back(Node((t[i].left+t[i].right)/2+1, t[i].right));
    }
    if (t[i].set != -1) {
        t[t[i].LeftChild].set = t[i].set;
        t[t[i].RightChild].set = t[i].set;
        t[t[i].LeftChild].sum = t[i].sum/2;
        t[t[i].RightChild].sum = t[i].sum/2;
        t[t[i].LeftChild].seg = t[i].set;
        t[t[i].RightChild].seg = t[i].set;
        t[i].set = -1;
    }
}

int search (int i, int l)
{
    if (t[i].right == t[i].left){
        return t[i].sum;
    }
    if (t[i].set != -1 || t[i].LeftChild == -1) propogate(i);
    int m = (t[i].left + t[i].right)/2;
    if (l > m)
        return search(t[i].RightChild, l);
    else
        return search(t[i].LeftChild, l);
}

void Set(int i, int l, int r, int x)
{
    if (l > t[i].right || r < t[i].left){
        return;
    }
    if (t[i].left < l || t[i].right > r) {
        if (t[i].set != -1 || t[i].LeftChild == -1) propogate(i);
        Set(t[i].LeftChild, l, r, x);
        Set(t[i].RightChild, l, r, x);
        t[i].sum = t[t[i].LeftChild].sum + t[t[i].RightChild].sum;
        t[i].seg = t[t[i].LeftChild].seg + t[t[i].RightChild].seg;
        if (search(0, t[t[i].LeftChild].right) == 1 && search(0, t[t[i].RightChild].left) == 1)
            t[i].seg -= 1;
        return;
    }
    t[i].sum = x*(t[i].right-t[i].left+1);
    t[i].seg = x;
    t[i].set = x;
}

int main()
{
    ios_base:: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("painter.in", "r", stdin);
    freopen("painter.out", "w", stdout);
    int n;
    cin >> n;
    t.push_back(Node(1, 1048576));
    string s;
    while (cin >> s) {
        if (s == "W") {
            int left, right;
            cin >> left >> right;
            left += 500001;
            Set(0, left, left+right-1, 0);
            cout << t[0].seg << " " << t[0].sum << "\n";
        }
        if (s == "B") {
            int left, right;
            cin >> left >> right;
            left += 500001;
            Set(0, left, left+right-1, 1);
            cout << t[0].seg << " " << t[0].sum << "\n";
        }
    }
    return 0;
}
