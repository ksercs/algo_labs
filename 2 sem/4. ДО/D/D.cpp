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
#include <climits>

#define SZ size()
#define VEC vector
#define PB push_back
#define MP make_pair
#define SS second
#define FF first
#define PII pair <int,int>
#define LL int

using namespace std;

const LL MAX_LVL = 23;

int n = INT_MAX, lvl, ln, q, sum, maxi = INT_MIN, dop;

struct vertex
{
    LL cnt;
    LL val;
    LL Tagged;
    LL Left;
    LL Right;
};

vertex tree[(1<<MAX_LVL)-1];
vector <LL> ans;

vertex pred(LL x)
{
  return tree[(x/2)];
}

void push(LL v);

LL potom(LL x, LL lr)
{
  return (2*x + lr);
}

LL lvl_count(LL x)
{
    LL level=1, ch=1;
    while(ch<x)
    {
     ch*=2;
     level++;
    }
    return level;
}

void ln_count(LL b)
{
  lvl = lvl_count(b);
  ln = (1<<(lvl))-1;
}

LL Search(LL v, LL sL, LL sR)
{
    //cout << v << " " <<sL << " " <<sR << "\n";
    if( (tree[v].Left != sL) || (tree[v].Right != sR) )
    {
        if (tree[v].Tagged) push(v);
        LL l_pot = potom(v,0);
        LL M = tree[l_pot].Right;
        if(sR <= M) return Search(l_pot, sL, sR);
        else if(M < sL)return Search(l_pot + 1, sL, sR);
        else return Search(l_pot, sL, M) + Search(l_pot + 1, M + 1, sR);
    }
    else{
        //cout << tree[v].val << "\n\n";
        return tree[v].val;
    }
}

void push(LL v)
{
    //cout  <<"P " <<v <<"\n";
    LL l_p = v << 1;
    tree[v].Tagged = 0;
    tree[l_p].Tagged = 1;
    tree[l_p+1].Tagged = 1;
    tree[l_p].val = tree[l_p+1].val = tree[v].val/2;
    if (tree[l_p].val != 0) {
        tree[l_p].cnt = 1;
    } else {
        tree[l_p].cnt = 0;
    }
    if (tree[l_p+1].val != 0) {
        tree[l_p+1].cnt = 1;
    } else {
        tree[l_p+1].cnt = 0;
    }
    //tree[v].cnt = tree[l_p].cnt + tree[l_p+1].cnt - (Search(1, tree[l_p].Right, tree[l_p].Right) * Search(1, tree[l_p+1].Left, tree[l_p+1].Left));
    //if (tree[8].cnt == 0) {
        //cout << "PUSH : " << v << "  " << tree[v].Left << " " << tree[v].Right << " " << "\n";
    //}
    //cout << potom(v,0).val << " " << potom(v,1).val <<  " " << tree[v].val/2 <<"\n";
}

void assign(LL v, LL new_val, LL sL, LL sR)
{
    //cout << "ASS : " << tree[v].Left << " " << tree[v].Right << "\n";
    if( (tree[v].Left != sL) || (tree[v].Right != sR) )
    {
        if (tree[v].Tagged) push(v);
        LL pot = (v << 1);
        LL M = tree[pot].Right;
        if(sR <= M)  assign(pot, new_val, sL, sR);
        else if(M < sL) assign(pot + 1, new_val, sL, sR);
        else  {assign(pot, new_val, sL, M); assign(pot + 1, new_val, M + 1, sR);}
        tree[v].val = tree[potom(v,0)].val + tree[potom(v,1)].val;
        //cout << "//pot : "<< tree[pot].Left << " "  << tree[pot].Right << " " << tree[pot].cnt << "\n";
        tree[v].cnt = tree[pot].cnt + tree[pot+1].cnt - (Search(1, tree[pot].Right, tree[pot].Right) * Search(1, tree[pot+1].Left, tree[pot+1].Left));
        //cout << "V = " << tree[v].Left << " "  << tree[v].Right << " " << tree[v].cnt << "\n";
        //cout << "pot : "<< tree[pot].Left << " "  << tree[pot].Right << " " << tree[pot].cnt << "\n";
    }
    else{
        //cout << tree[v].val << "\n\n";
        //if (tree[v].Tagged) {cout << "ST PUSH " << v  << "\n"; push(v);}
        tree[v].Tagged = 1;
        tree[v].val = new_val*(sR-sL+1);
        //cout << tree[v].Left << " " << tree[v].Right << " TO "  << new_val << "\n";
        if (new_val)
            tree[v].cnt = 1;
        else
            tree[v].cnt = 0;
    }
}

void iniz_t()
{
  for (LL i = ((ln+1)>>1)-1; i >=1; --i)
  {
      LL l_p = potom(i,0), r_p = potom(i,1);
      tree[i].Left = tree[l_p].Left;
      tree[i].Right = tree[r_p].Right;
  }
}

struct segment
{
    int c;
    int L;
    int R;
    segment (int a, int l, int r)
    {
        c = a;
        L = l;
        R = r;
    }
    segment (){}
};

int main()
{
    ios_base:: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ifstream cin("painter.in");
    ofstream cout("painter.out");
    cin >> q;
    VEC <segment> seg;
    seg.resize(q);
    for (int i = 0; i < q; ++i) {
        char c;
        int L, tm;
        cin >> c >> L >> tm;
        n = min(n, L);
        maxi = max (maxi, L+tm);
        seg[i] = segment((c == 'B'), L, L + tm);
    }
    if (n < 1) {
        maxi += (1 - n);
        dop = (1 - n);
    }
    ln_count(maxi);
    LL l_count = (ln+1)>>1;
    for (LL i = l_count; i <= ln; ++i)
    {
        tree[i].Left =  tree[i].Right = i-l_count+1;
        tree[i].val = 0;
    }
    iniz_t();
    LL L, R;
    int c;
    for (int i = 0; i < seg.SZ; ++i)
    {
        L = seg[i].L + dop;
        R = seg[i].R + dop - 1;
        c = seg[i].c;
        //cout << "ST : " << c << " " << L << " " << R << "\n";
        assign(1, c, L, R);
        cout << tree[1].cnt << " " << tree[1].val << "\n";
    }
    return 0;
}
