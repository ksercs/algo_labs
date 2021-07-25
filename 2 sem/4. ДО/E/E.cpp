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

const LL MAX_LVL = 23;

LL n, lvl, ln, q, r;

struct vertex
{
    LL a, b, c, d;
    LL Left;
    LL Right;
};

struct matrix
{
    LL a, b, c, d;
    matrix (LL A, LL B, LL C, LL D)
    {
        a = A;
        b = B;
        c = C;
        d = D;
    }
    matrix ()
    {
        a = 1;
        b = 0;
        c = 0;
        d = 1;
    }
};

vertex tree[(1<<MAX_LVL)-1];

void ln_count(LL b)
{
  lvl = (LL)log2(b)+2;
  ln = (1<<(lvl))-1;
}

void getRes (int i, int A, int B)
{
    tree[i].Left = tree[A].Left;
    tree[i].Right = tree[B].Right;
    tree[i].a = ((tree[A].a*tree[B].a) + (tree[A].b*tree[B].c))%r;
    tree[i].b = ((tree[A].a*tree[B].b) + (tree[A].b*tree[B].d))%r;
    tree[i].c = ((tree[A].c*tree[B].a) + (tree[A].d*tree[B].c))%r;
    tree[i].d = ((tree[A].c*tree[B].b) + (tree[A].d*tree[B].d))%r;
}

matrix mult (matrix A, matrix B)
{
    matrix v;
    v.a = ((A.a*B.a) + (A.b*B.c))%r;
    v.b = ((A.a*B.b) + (A.b*B.d))%r;
    v.c = ((A.c*B.a) + (A.d*B.c))%r;
    v.d = ((A.c*B.b) + (A.d*B.d))%r;
    return v;
}

void iniz_t()
{
  for (LL i = ((ln+1)>>1)-1; i >=1; --i)
  {
      LL l_p = 2*i, r_p = 2*i + 1;
      getRes(i, l_p, r_p);
      //cout << tree[i].a << " " << tree[i].b << " " << tree[i].c << " " << tree[i].d << "\n";
  }
}


matrix Search(LL v, LL sL, LL sR)
{
    //cout << v << " " <<sL << " " <<sR << "\n";
    if( (tree[v].Left != sL) || (tree[v].Right != sR) )
    {
        LL l_pot = 2*v;
        LL M = tree[l_pot].Right;
        if(sR <= M) return Search(l_pot, sL, sR);
        else if(M < sL)return Search(l_pot + 1, sL, sR);
        else return mult(Search(l_pot, sL, M), Search(l_pot + 1, M + 1, sR));
    }
    else{
        //cout << tree[v].val << "\n\n";
        return matrix(tree[v].a, tree[v].b, tree[v].c, tree[v].d);
    }
}

int main()
{
    ios_base:: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ifstream cin("crypto.in");
    ofstream cout("crypto.out");
    cin >> r >> n >> q;
    ln_count(n);
    LL l_count = (ln+1)>>1;
    for (LL i = l_count; i < l_count+n; ++i)
    {
        cin >> tree[i].a >> tree[i].b >> tree[i].c >> tree[i].d;
        tree[i].Left =  tree[i].Right = i-l_count+1;
    }
    for (LL i = l_count+n; i <= ln; ++i)
    {
        tree[i].Left = tree[i].Right = i-l_count+1;
        tree[i].a = 1;
        tree[i].b = 0;
        tree[i].c = 0;
        tree[i].d = 1;
    }
    iniz_t();
    LL L, R;
    for (int i = 0; i < q; ++i) {
        cin >> L >> R;
        matrix ans = (Search(1, L, R));
        cout << ans.a << " " << ans.b << "\n" << ans.c << " " << ans.d << "\n\n";
    }
    return 0;
}
