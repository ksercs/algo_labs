#include <bits/stdc++.h>

using namespace std;

struct point
{
    pair <int,int> x;
    pair <int,int> y;
    point(int a, int b, int c, int d) {
        x.first = a;
        x.second = b;
        y.first = c;
        y.second = d;
    }
};

struct Node
{
    int LeftChild;
    int RightChild;
    int left;
    int right;
    int max;
    bool isAdd;
    int add;

    Node (int a, int b) {
        left = a;
        right = b;
        max = 0;
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
    if (t[i].isAdd) {
        t[i].isAdd = 0;
        t[t[i].LeftChild].isAdd = 1;
        t[t[i].RightChild].isAdd = 1;
        t[t[i].LeftChild].add += t[i].add;
        t[t[i].RightChild].add += t[i].add;
        t[t[i].LeftChild].max += t[i].add;
        t[t[i].RightChild].max += t[i].add;
        t[i].add = 0;
    }
}

void Add(int i, int l, int r, int x)
{
    if (l > t[i].right || r < t[i].left){
        return;
    }
    if (t[i].left < l || t[i].right > r) {
        propogate(i);
        Add(t[i].LeftChild, l, r, x);
        Add(t[i].RightChild, l, r, x);
        t[i].max = max(t[t[i].LeftChild].max, t[t[i].RightChild].max);
        return;
    }
    t[i].max += x;
    t[i].isAdd = 1;
    t[i].add += x;
}

bool f(point a, point b)
{
    if (a.x.first == b.x.first)
        return a.x.second > b.x.second;
    else
        return a.x.first < b.x.first;
}

int Search (int i)
{
    if (t[i].left == t[i].right)
        return t[i].left;
    propogate(i);
    if (t[t[i].LeftChild].max == t[i].max)
        return Search(t[i].LeftChild);
    if (t[t[i].RightChild].max == t[i].max)
        return Search(t[i].RightChild);
}

int main()
{
    //freopen("G.in", "r", stdin);
    //freopen("G.out", "w", stdout);
    int n;
    cin >> n;
    vector <point> p;
    t.push_back(Node(1, 524288));
    int mod1 = 200001;
    for (int i = 0; i < n; i += 1){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += mod1;
        x2 += mod1;
        y1 += mod1;
        y2 += mod1;
        p.push_back(point(x1, 1, y1, y2));
        p.push_back(point(x2, -1, y1, y2));
    }
    sort(p.begin(), p.end(), f);
    int answer = 0;
    pair <int, int> xy;
    for (int i = 0; i < p.size(); i += 1) {
        Add(0, p[i].y.first, p[i].y.second, p[i].x.second);
        if (p[i].x.second == 1) {
            if (t[0].max > answer) {
                answer = t[0].max;
                xy.first = p[i].x.first-mod1;
                xy.second = Search(0)-mod1;
            }
        }
    }
    cout << answer << "\n" << xy.first << " " << xy.second << "\n";
    return 0;
}
