#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

#define NULLVAL 0
using namespace std;

struct Node {
    int val = 0;
    Node* Left = nullptr;
    Node* Right = nullptr;
    int Lt = 0;
    int Rt = 0;
    int setVal = NULLVAL;

    Node(int Lt_, int Rt_){
        Lt = Lt_;
        Rt = Rt_;
    }

    void makeTree(){
        if (Lt == Rt)
            return;
        int mid = (Lt + Rt)/2;
        Left = new Node(Lt, mid);
        Left->makeTree();
        Right = new Node(mid + 1, Rt);
        Right->makeTree();
    }

    void check () {
        if (Lt == Rt)
            return;
        int mid = (Lt+Rt)/2;
        if (Left == nullptr) {
            Left = new Node(Lt, mid);
        }
        if (Right == nullptr) {
            Right = new Node(mid+1, Rt);
        }
    }

    int get () {
        //cout << Lt << " " << Rt << " " <<val << "\n";
        if (Lt == Rt)
            return Lt;
        if (setVal != NULLVAL)
            propogate();
        //cout << "Left\n";
        if (Left->setVal != NULLVAL)
            Left->propogate();
        if (Left->val == val)
            return Left->get();
        //cout << "Right\n";
        if (Right->setVal != NULLVAL)
            Right->propogate();
        if (Right->val == val)
            return Right->get();
    }

    void propogate() {
       //cout << "PR : " << Lt << " " << Rt << "\n";
        if (Lt == Rt) {
            return;
        }
        Left->val += setVal;
        Right->val += setVal;
        Left->setVal += setVal;
        Right->setVal += setVal;
        setVal = NULLVAL;
    }

    void set(int L, int R, int d) {
        //cout << Lt << " " << Rt << "\n";
        int mid = (Lt+Rt)/2;
        if (L == Lt && R == Rt) {
            val += d;
            setVal += d;
            return;
        }
        if (setVal != NULLVAL)
            propogate();
        if (R <= mid){
            Left->set(L, R, d);
        }
        else if (L > mid) {
            Right->set(L, R, d);
        }
        else {
            Left->set(L, mid, d);
            Right->set(mid+1, R, d);
        }
        //cout << "return\n";
        val = max(Left->val, Right->val);
    }
};

bool comp (pair<pair <int, int>, pair <int, int>> a, pair<pair <int, int>, pair <int, int>> b) {
    if (a.first.first != b.first.first)
        return a.first.first < b.first.first;
    else
        return a.first.second > b.first.second;
}

int main()
{
    FILE* in = fopen("G.in", "r");
    FILE* out = fopen("G.out", "w");
    int n;
    scanf( "%d ", &n);
    char c;
    Node* root = new Node(1, 1048576);
    root->makeTree();
    vector <pair<pair <int, int>, pair <int, int>>> x;
    for (int i = 0; i < n; ++i) {
        int a, b, c, d;
        scanf( "%d%d%d%d", &a, &b, &c, &d);
        x.push_back(make_pair(make_pair(a, 1), make_pair(b, d)));
        x.push_back(make_pair(make_pair(c, -1), make_pair(b, d)));
    }
    sort(x.begin(), x.end(), comp);
    int cnt = 0;
    pair <int, int> ans;
    for (int i = 0; i < 2*n; ++i) {
        root->set(x[i].second.first+200005, x[i].second.second+200005, x[i].first.second);
        if (root->val > cnt) {
            cnt = root->val;
            ans.first = x[i].first.first;
            ans.second = root->get()-200005;
        }
    }
    printf( "%d\n%d %d\n", cnt, ans.first, ans.second);
    return 0;
}
