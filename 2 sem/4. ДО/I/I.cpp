#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <set>
#include <map>
#include <utility>
#include <queue>
#include <string.h>

#define SZ size()
#define VEC vector
#define PB push_back
#define MP make_pair
#define SS second
#define FF first
#define PII pair <int,int>
#define LL long long

using namespace std;

int n;
VEC <int> ans;

struct node
{
    int sum;
    int maxi;
    int Left;
    int Right;
    int Tagged;
    int sonL;
    int sonR;
    int new_val;
    node (int s, int m, int L, int R)
    {
        sum = s;
        maxi = m;
        Left = L;
        Right = R;
        Tagged = 0;
        sonL = 0;
    }
    node () {}
};

VEC <node> tree;

void push (int v)
{
    //cout << "PUSH: " << v << "\n";
    if (tree[v].sonL == 0 && tree[v].Left != tree[v].Right) {
        int M = (tree[v].Left + tree[v].Right)/2;
        tree.PB(node(0, 0, tree[v].Left, M));
        tree[v].sonL = tree.SZ - 1;
        tree.PB(node(0, 0, M + 1, tree[v].Right));
        tree[v].sonR = tree.SZ - 1;
    }
    if (tree[v].Tagged) {
        if (tree[v].Left != tree[v].Right) {
            tree[tree[v].sonL].Tagged = tree[v].Tagged;
            tree[tree[v].sonL].new_val = tree[v].new_val;
            tree[tree[v].sonR].Tagged = tree[v].Tagged;
            tree[tree[v].sonR].new_val = tree[v].new_val;
        }
        tree[v].sum = tree[v].new_val*(tree[v].Right - tree[v].Left + 1);
        tree[v].maxi = tree[v].new_val*(tree[v].Right - tree[v].Left + 1);
        tree[v].Tagged = 0;
    }
}

void assign (int v, int new_val, int L, int R)
{
    push(v);
    //cout << "assign : " << v << " " << new_val << " " << L << " " << R << "\n";
    if (tree[v].Left >= L && tree[v].Right <= R) {
        tree[v].Tagged = 1;
        tree[v].new_val = new_val;
        //cout << "ASSIGN Last " << v << " " << new_val << "\n";
        push(v);
        return;
    }

    int M = (tree[v].Left + tree[v].Right)/2;
    push(tree[v].sonL);
    if (L <= tree[tree[v].sonL].Right && R >= tree[tree[v].sonL].Left)
        assign(tree[v].sonL, new_val, L, R);
    push(tree[v].sonR);
    if (L <= tree[tree[v].sonR].Right && R >= tree[tree[v].sonR].Left)
        assign(tree[v].sonR, new_val, L, R);

    tree[v].sum = tree[tree[v].sonL].sum + tree[tree[v].sonR].sum;
    tree[v].maxi = max(tree[tree[v].sonL].maxi, tree[tree[v].sonL].sum + tree[tree[v].sonR].maxi);
}

int Search (int v, int h)
{
    //cout << "v, h: " << v << " " << h << "\n";
    push(v);
    if (tree[v].Left == tree[v].Right) {
        //cout << "Last : " << tree[v].maxi << "\n";
        if (tree[v].maxi <= h)
            return tree[v].Left;
        else
            return tree[v].Left - 1;
    }
    push(tree[v].sonL);
    //cout << "Left maxi : " << tree[tree[v].sonL].maxi << "\n";
    if(tree[tree[v].sonL].maxi > h)
        return Search(tree[v].sonL, h);
    else
        return Search(tree[v].sonR, h - tree[tree[v].sonL].sum);
}

void in()
{
    ios_base:: sync_with_stdio(false);
    cin.tie();
    //ifstream cin("I.in");
    cin >> n;
    tree.PB(node(0, 0, 1, n));
    //cout << "HERE : " << tree[0].sum << " " << tree[0].maxi << "\n";
    char c;
    int L, R, x;
    while (cin >> c) {
        if (c == 'E') {
            break;
        }
        if (c == 'Q') {
            cin >> x;
            //cout << "NEW --> Q " << x << "\n";
            ans.PB(Search(0, x));
            //cout << "\n";
        } else {
            cin >> L >> R >> x;
            //cout << "NEW --> I " << L << " " << R << " " << x << "\n";
            assign(0, x, L, R);
            //cout << "\n";
            //cout << "TREE : ";
            /*for (int i = 0; i < tree.SZ; ++i) {
                cout << i<<":("; cout << tree[i].Left << "," <<tree[i].Right << ") ";
            }*/
            //cout << "\n\n";
        }
    }
}

void out()
{
    cout.tie();
    //ofstream cout("I.out");
    for (int i = 0; i < ans.SZ; ++i) {
        cout << ans[i] << "\n";
    }
}

int main()
{
    in();
    out();
    return 0;
}
