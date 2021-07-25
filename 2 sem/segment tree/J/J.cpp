#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

#define NULLVAL -100000000
using namespace std;

struct Node {
    long long val = 0;
    Node* Left = nullptr;
    Node* Right = nullptr;
    int Lt = 0;
    int Rt = 0;
    long long setVal = NULLVAL;

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
        int mid = (Lt+Rt)/2;
        if (Left == nullptr) {
            Left = new Node(Lt, mid);
        }
        if (Right == nullptr) {
            Right = new Node(mid+1, Rt);
        }
    }

    Node* get (int L, int R) {
        check();
        if (setVal != NULLVAL)
            propogate();
        int mid = (Lt+Rt)/2;
        if (L == Lt && R == Rt) {
            return this;
        };
        if (R <= mid) {
            return Left->get(L, R);
        }
        else if (L > mid) {
            return Right->get(L, R);
        }
        else {
            Node* left =  Left->get(L, mid);
            Node* right = Right->get(mid+1, R);
            if (left->val <= right->val)
                return left;
            else
                return right;
        }
    }

    void propogate() {
        Left->val = max(Left->val, setVal);
        Right->val = max(Right->val, setVal);
        Left->setVal = max(Left->setVal, setVal);
        Right->setVal = max(Right->setVal, setVal);
        setVal = NULLVAL;
    }

    void set(int L, int R, long long d) {
        //cout << Lt << " " << Rt << "\n";
        check();
        if (setVal != NULLVAL)
            propogate();
        int mid = (Lt+Rt)/2;
        if (L == Lt && R == Rt) {
            val = max(d, val);
            setVal = max(setVal, d);
            return;
        }
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
        val = min(Left->val, Right->val);
    }

    int getIndex () {
        if (Lt == Rt)
            return Lt;
        check();
        if (setVal != NULLVAL)
            propogate();
        if (Left->val == val)
            return Left->getIndex();
        else
            return Right->getIndex();
    }
};

int main()
{
    FILE* in = fopen("J.in", "r");
    FILE* out = fopen("J.out", "w");
    int n, m;
    scanf( "%d%d", &n, &m);
    char c;
    Node* root = new Node(1, (int)pow(2,((int)log2(n)+((int)pow(2,(int)log2(n)) != n))));
    //cout << root->Rt << "\n";
    //root->makeTree();
    char s[100];
    for (int i = 0; i < m; ++i) {
        int L, R;
        scanf( "%s%d%d ", &s, &L, &R);
        if (s[0] == 'a') {
            Node* res = root->get(L, R);
            int ans = res->getIndex();
            printf( "%lld %d\n", res->val, ans);
        } else {
            long long val;
            scanf( "%lld", &val);
            root->set(L, R, val);
        }
    }
    return 0;
}
