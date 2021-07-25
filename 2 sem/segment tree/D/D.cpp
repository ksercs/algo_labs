#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

#define NULLVAL -1
using namespace std;

struct Node {
    int val = 0;
    Node* Left = nullptr;
    Node* Right = nullptr;
    int Lt = 0;
    int Rt = 0;
    int num = 0;
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
        int mid = (Lt+Rt)/2;
        if (Left == nullptr) {
            Left = new Node(Lt, mid);
        }
        if (Right == nullptr) {
            Right = new Node(mid+1, Rt);
        }
    }

    int get (int L, int R) {
        int mid = (Lt+Rt)/2;
        if (L == Lt && R == Rt) {
            return val;
        }
        check();
        if (setVal != NULLVAL)
            propogate();
        if (R <= mid) {
            return Left->get(L, R);
        }
        else if (L > mid) {
            return Right->get(L, R);
        }
        else {
            return Left->get(L, mid) + get(mid+1, R);
        }
    }

    void propogate() {
        Left->val = Right->val = val/2;
        Left->num = Right->num = Left->setVal = Right->setVal = (val != 0);
        setVal = NULLVAL;
    }

    void set(int L, int R, int d) {
        //cout << Lt << " " << Rt << "\n";
        int mid = (Lt+Rt)/2;
        if (L == Lt && R == Rt) {
            val = d*(Rt-Lt+1);
            setVal = d;
            num = d;
            return;
        }
        check();
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
        val = Left->val + Right->val;
        int left = Left->Rt;
        num = Left->num + Right->num - Left->get(left, left)*Right->get(left+1, left+1);
    }
};

int main()
{
    FILE* in = fopen("painter.in", "r");
    FILE* out = fopen("painter.out", "w");
    int n;
    fscanf(in, "%d ", &n);
    char c;
    Node* root = new Node(1, 1048576);
    //root->makeTree();
    for (int i = 0; i < n; ++i) {
        int L, R;
        fscanf(in, "%c %d %d ", &c, &L, &R);
        root->set(L+500001, L+R-1+500001, c=='B');
        fprintf(out, "%d %d\n", root->num, root->val);
    }
    return 0;
}
