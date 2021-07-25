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
      tree[i].val = tree[l_p].val + tree[r_p].val;
      tree[i].Left = tree[l_p].Left;
      tree[i].Right = tree[r_p].Right;
  }
}

LL Search(LL v, LL sL, LL sR)
{
    //cout << v << " " <<sL << " " <<sR << "\n";
    if( (tree[v].Left != sL) || (tree[v].Right != sR) )
    {
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

void in()
{
    ifstream cin("rsq.in");
    cin >> n;
    ln_count(n);
    LL l_count = (ln+1)>>1;
    for (LL i = l_count; i < l_count+n; ++i)
    {
        LL a;
        cin >> a;
        tree[i].val = a;
        tree[i].Left =  tree[i].Right = i-l_count+1;
    }
    for (LL i = l_count+n; i <= ln; ++i)
    {
        tree[i].Left = tree[i].Right = i-l_count+1;
    }
    iniz_t();
    LL L, R;
    string t;
    while (cin  >> t >> L >> R)
    {
        //cout << t << " " << L << " " << R << "\n";
        if (t == "set") {
            tree[l_count+L-1].val = R;
            int ind = (l_count+L-1)/2;
            while (ind) {
                tree[ind].val = tree[potom(ind, 0)].val + tree[potom(ind, 1)].val;
                ind /= 2;
            }
        }
        else {
            ans.push_back(Search(1, L, R));
        }
    }
}

void out()
{
    ofstream cout("rsq.out");
    /*for (LL i = 1; i <= ln; ++i)
    {
        if (tree[i].Tagged && (tree[i].Left != tree[i].Right) ) push(i);
        //cout << tree[i].val << " " << tree[i].Left << " " << tree[i].Right << " " << tree[i].Tagged << "\n";
    }*/
    //cout << "\n";
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
