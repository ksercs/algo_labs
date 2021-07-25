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
#define PLL pair <LL,LL>


using namespace std;

const LL MAX_LVL = 23;

LL n, lvl, ln, q, l_count;

struct vertex
{
    LL val;
    LL Tagged;
    LL Left;
    LL Right;
};

vertex tree[(1<<MAX_LVL)-1];
vector < PLL > ans;

vertex pred(LL x)
{
  return tree[(x/2)];
}

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

void iniz_t()
{
  for (LL i = ((ln+1)>>1)-1; i >=1; --i)
  {
      LL l_p = potom(i,0), r_p = potom(i,1);
      tree[i].val = min(tree[l_p].val, tree[r_p].val);
      tree[i].Left = tree[l_p].Left;
      tree[i].Right = tree[r_p].Right;
  }
}

void push(LL v)
{
    //cout << v <<" " <<tree[v].val <<"\n";
    LL l_p = v<<1;
    tree[l_p].Tagged = max(tree[v].Tagged, tree[l_p].Tagged);
    tree[l_p+1].Tagged = max(tree[v].Tagged, tree[l_p+1].Tagged);
    tree[v].Tagged = 0;
    int new_val = tree[l_p].Tagged;
    LL cur = tree[l_p].val;
    if (cur < new_val) {
        tree[l_p].val = new_val;
    }
    new_val = tree[l_p+1].Tagged;
    cur = tree[l_p+1].val;
    if (cur < new_val) {
        tree[l_p+1].val = new_val;
    }
    //cout << potom(v,0).val << " " << potom(v,1).val <<  " " << tree[v].val/2 <<"\n";
}

void assign(LL v, LL new_val, LL sL, LL sR)
{
    if( (tree[v].Left != sL) || (tree[v].Right != sR) )
    {
        if (tree[v].Tagged) push(v);
        LL pot = (v << 1);
        LL M = tree[pot].Right;
        if(sR <= M)  assign(pot, new_val, sL, sR);
        else if(M < sL) assign(pot + 1, new_val, sL, sR);
        else  {assign(pot, new_val, sL, M); assign(pot + 1, new_val, M + 1, sR);}
        tree[v].val = min(tree[potom(v,0)].val, tree[potom(v,1)].val);
    }
    else{
        //cout << tree[v].val << "\n\n";
        if (tree[v].Tagged) push(v);
        tree[v].Tagged = max(tree[v].Tagged, new_val);
        LL cur = tree[v].val;
        if (cur < tree[v].Tagged) {
            tree[v].val = tree[v].Tagged;
        }
    }
}

LL S(LL v, LL x)
{
    //cout << v << " " << x << " " << tree[v].val      << "\n";
    if(v < l_count)
    {
        if (tree[v].Tagged) push(v);
        LL l_pot = potom(v,0);
        if (tree[l_pot].Tagged) {
            push(l_pot);
        }
        if(tree[l_pot].val == x) return S(l_pot, x );
        else {
            if (tree[l_pot+1].Tagged) {
                push(l_pot+1);
            }
            if(tree[l_pot+1].val == x)return S(l_pot + 1, x);
        }
    }
    else{
        //cout << tree[v].val << "\n\n";
        return v-l_count+1;
    }
}

PLL Search(LL v, LL sL, LL sR)
{
    //cout << v << " " <<sL << " " <<sR << "\n";
    if( (tree[v].Left != sL) || (tree[v].Right != sR) )
    {
        if (tree[v].Tagged) push(v);
        LL l_pot = potom(v,0);
        LL M = tree[l_pot].Right;
        if(sR <= M) return Search(l_pot, sL, sR);
        else if(M < sL)return Search(l_pot + 1, sL, sR);
        else {
            PLL left = Search(l_pot, sL, M);
            PLL right = Search(l_pot + 1, M + 1, sR);
            return left.FF < right.FF ? left : right;
        }
    }
    else{
       // cout << v << " " << tree[v].val << "\n";
        return MP(tree[v].val, v);
    }
}

void in()
{
    //ifstream cin("J.in");
    cin >> n >> q;
    ln_count(n);
    l_count = (ln+1)>>1;
    for (LL i = l_count; i < l_count+n; ++i)
    {
        tree[i].Left =  tree[i].Right = i-l_count+1;
    }
    for (LL i = l_count+n; i <= ln; ++i)
    {
        tree[i].Left = tree[i].Right = i-l_count+1;
    }
    iniz_t();
    LL x, L, R;
    string t;
    for (int i = 0; i < q; ++i) {
        cin >> t >> L >> R;
        if (t == "defend") {
            cin >> x;
            assign(1, x, L, R);
        } else {
            //cout << "NEW : " << L << " " << R << "\n";
            PLL res = Search(1, L, R);
            //cout << "S : " << res.SS << " " << res.FF << "\n";
            ans.PB(MP(res.FF, S(res.SS, res.FF)));
        }
    }
}

void out()
{
    //ofstream cout("J.out");
    for (LL i = 0; i < ans.size(); i ++)
    {
        cout << ans[i].FF << " " << ans[i].SS << "\n";
    }
}

int main()
{
    in();
    out();
    return 0;
}
