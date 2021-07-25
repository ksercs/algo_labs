#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

#define NULLVAL 0
using namespace std;

struct Node {
    long long val = 0;
    Node* Left = nullptr;
    Node* Right = nullptr;
    long long Lt = 0;
    long long Rt = 0;
    long long num = 0;
    long long isSet = 0;
    long long setVal = NULLVAL;

    Node(long long Lt_, long long Rt_){
        Lt = Lt_;
        Rt = Rt_;
    }

    void makeTree(){
        if (Lt == Rt)
            return;
        long long mid = (Lt + Rt)/2;
        Left = new Node(Lt, mid);
        Left->makeTree();
        Right = new Node(mid + 1, Rt);
        Right->makeTree();
    }

    void check () {
        long long mid = (Lt+Rt)/2;
        if (Left == nullptr) {
            Left = new Node(Lt, mid);
        }
        if (Right == nullptr) {
            Right = new Node(mid+1, Rt);
        }
    }

    long long get (long long L, long long R, long long h){
        if (isSet)
            propogate();
        if (Lt == Rt) {
            if (num <= h)
                return Lt;
            else
                return Lt-1;
        }
        check();
        if (Left->isSet) {
            Left->propogate();
        }
        if (Left->num > h) {
            return Left->get(L, R, h);
        }
        else
            if (R > (Lt+Rt)/2)
                return Right->get(L, R, h - Left->val);
            else
                return Left->get(L, R, h);
    }

    long long getV (long long L, long long R, long long h) {
        //cout << L << " " << R << " "  << Lt << " " << Rt << " " << h << "\n";
        if (isSet)
            propogate();
        long long mid = (Lt+Rt)/2;
        if (Lt == L && Rt == R) {
            return get(L, R, h);
        }
        check();
        if (R <= mid)
            Left->getV(L, R, h);
        else if (L > mid)
            Right->getV(L, R, h);
        else {
            return min(Left->getV(L, mid, h),
            Right->getV(mid+1, R, h));
            //val = Left->val + Right->val;
            //num = max(Left->num, Left->val+Right->num);
        }
        //cout << Lt << " " << Rt << " " << val << " " << num << " " << h << "\n";
    }

    void propogate() {
        check();
        Left->val = Right->val = val/2;
        Left->num = Right->num =  (Right->Rt - Right->Lt + 1)*setVal;
        Left->setVal = Right->setVal = setVal;
        Left->isSet = Right->isSet = 1;
        setVal = NULLVAL;
        isSet = 0;
    }

    void set(long long L, long long R, long long d) {
        //cout << Lt << " " << Rt << "\n";
        long long mid = (Lt+Rt)/2;
        if (L == Lt && R == Rt) {
            val = d*(Rt-Lt+1);
            num = d*(Rt-Lt+1);
            setVal = d;
            isSet = 1;
            return;
        }
        check();
        if (isSet)
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
        num = max(Left->num, Left->val+Right->num);
    }
};

int main()
{
    //FILE* in = fopen("I.in", "r");
    //FILE* out = fopen("I.out", "w");
    long long n;
    scanf( "%lld ", &n);
    Node* root = new Node(1, (int)pow(2,((int)log2(n)+((int)pow(2,(int)log2(n)) != n))));
    //root->makeTree();
    char c = 'I';
    while (c != 'E') {
        scanf("%c", &c);
        if (c == 'I') {
            long long a, b, d;
            scanf(  "%lld%lld%lld", &a, &b, &d );
            root->set(a, b, d);
        } else if (c == 'Q') {
            long long h;
            scanf( "%lld", &h);
            printf( "%lld\n", root->get(1, n, h));
            //cout << "\n\n";
        }
    }
    return 0;
}
