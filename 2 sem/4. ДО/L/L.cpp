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

LL n, lvl, ln, q;

struct vertex
{
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
    tree[v].Tagged = 0;
    tree[l_p].Tagged = 1;
    tree[l_p+1].Tagged = 1;
    tree[l_p].val = tree[l_p+1].val = (tree[v].val)>>1;
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
        tree[v].val = tree[potom(v,0)].val + tree[potom(v,1)].val;
    }
    else{
        //cout << tree[v].val << "\n\n";
        tree[v].Tagged = 1;
        tree[v].val = new_val*(sR-sL+1);
    }
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
        else return min(Search(l_pot, sL, M),Search(l_pot + 1, M + 1, sR));
    }
    else{
        //cout << tree[v].val << "\n\n";
        return tree[v].val;
    }
}

void in()
{
    ifstream cin("parking.in");
    cin >> n >> q;
    ln_count(n);
    LL l_count = (ln+1)>>1;
    for (LL i = l_count; i < l_count+n; ++i)
    {
        LL a;
        tree[i].val = i - l_count + 1;
        tree[i].Left =  tree[i].Right = i-l_count+1;
    }
    for (LL i = l_count+n; i <= ln; ++i)
    {
        tree[i].val = INT_MAX;
        tree[i].Left = tree[i].Right = i-l_count+1;
    }
    iniz_t();
    LL x;
    string t;
    for (int i = 0; i < q; ++i) {
        cin >> t >> x;
        if (t == "enter") {
            int res = 0;
            res = Search(1, x, n);
            if (res == INT_MAX) {
                res = Search(1, 1, x-1);
            }
            ans.PB(res);
            int ind = l_count+res-1;
            tree[ind].val = INT_MAX;
            while (ind) {
                ind /= 2;
                tree[ind].val = min(tree[potom(ind, 0)].val, tree[potom(ind, 1)].val);
            }
        } else {
            tree[l_count + x - 1].val = x;
            int ind = (l_count + x - 1)/2;
            while (ind) {
                tree[ind].val = min(tree[potom(ind, 0)].val, tree[potom(ind, 1)].val);
                ind /= 2;
            }
        }
    }
}

void out()
{
    ofstream cout("parking.out");
    for (LL i = 0; i < ans.size(); ++i)
    {
        cout << ans[i] << "\n";
    }
}

int main()
{
    in();
    out();
    return 0;
}
