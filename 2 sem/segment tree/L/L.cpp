#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

#define NULLVAL 100000000
using namespace std;

struct Node {
    int val = NULLVAL;
    Node* Left = nullptr;
    Node* Right = nullptr;
    int Lt = 0;
    int Rt = 0;

    Node(int Lt_, int Rt_){
        if (Lt_ == Rt_) {
            val = Lt_;
        }
        Lt = Lt_;
        Rt = Rt_;
    }

    void makeTree(int n){
        if (Lt == Rt) {
            if (Lt <= n)
                val = Lt;
            return;
        }
        int mid = (Lt + Rt)/2;
        Left = new Node(Lt, mid);
        Left->makeTree(n);
        Right = new Node(mid + 1, Rt);
        Right->makeTree(n);
        val = min(Left->val, Right->val);
    }


    int enter (int L, int R) {
        //cout << Lt << " " << Rt << "\n";
        int mid = (Lt+Rt)/2;
        if (L == Lt && R == Rt) {
            return val;
        }
        if (R <= mid) {
            return Left->enter(L, R);
        }
        else if (L > mid) {
            return Right->enter(L, R);
        } else {
            return min(Left->enter(L, mid), Right->enter(mid+1, R));
        }
    }

    void set(int L, int d) {
        int mid = (Lt+Rt)/2;
        if (L == Lt && L == Rt) {
            val = d;
            return;
        }
        if (L <= mid){
            Left->set(L, d);
        }
        else {
            Right->set(L, d);
        }
        val = min(Left->val, Right->val);
    }
};

int main()
{
    FILE* in = fopen("parking.in", "r");
    FILE* out = fopen("parking.out", "w");
    int n, m;
    fscanf(in, "%d%d", &n, &m);
    char s[100];
    Node* root = new Node(1, (int)pow(2,((int)log2(n)+((int)pow(2,(int)log2(n)) != n))));
    root->makeTree(n);
    for (int i = 0; i < m; ++i) {
        int place;
        fscanf(in, "%s %d", &s, &place);
        //cout << s << " : " << place << "\n";
        if (s[1] == 'x') {
            root->set(place, place);
        } else {
            int res = root->enter(place, n);
            if (res == NULLVAL)
                res = root->enter(1, place-1);
            fprintf(out, "%d\n", res);
            root->set(res, NULLVAL);
        }
    }
    return 0;
}
