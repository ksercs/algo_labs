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
#define LL int

using namespace std;

const LL MAX_LVL = 23;

LL n, lvl, ln, ansX, ansY, ansCnt, l_count;

struct vertex
{
    LL val;
    LL Tagged;
    LL Left;
    LL Right;
};

vertex tree[(1<<MAX_LVL)-1];

struct xBorder
{
    int x;
    int t;
    int yL;
    int yH;
    xBorder (int a, int type, int y1, int y2)
    {
        x = a;
        t = type;
        yL = y1;
        yH = y2;
    }
    xBorder () {}
};

struct rec
{
    int x1;
    int x2;
    int y1;
    int y2;
    rec (int a, int b, int c ,int d)
    {
        x1 = a;
        y1 = b;
        x2 = c;
        y2 = d;
    }
    rec () {}
};

VEC <rec> xKoor;

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
      tree[i].Left = tree[l_p].Left;
      tree[i].Right = tree[r_p].Right;
  }
}

void push(LL v)
{
    //cout << v <<" " <<tree[v].val <<"\n";
    LL l_p = v<<1;
    int pl = tree[v].Tagged;
    tree[v].Tagged = 0;
    tree[l_p].Tagged += pl;
    tree[l_p+1].Tagged += pl;
    tree[l_p].val += pl;
    tree[l_p+1].val += pl;
    //cout << potom(v,0).val << " " << potom(v,1).val <<  " " << tree[v].val/2 <<"\n";
}

void add(LL v, LL new_val, LL sL, LL sR)
{
    if( (tree[v].Left != sL) || (tree[v].Right != sR) )
    {
        if (tree[v].Tagged) push(v);
        LL pot = (v << 1);
        LL M = tree[pot].Right;
        if(sR <= M)  add(pot, new_val, sL, sR);
        else if(M < sL) add(pot + 1, new_val, sL, sR);
        else  {add(pot, new_val, sL, M); add(pot + 1, new_val, M + 1, sR);}
        tree[v].val = max(tree[potom(v,0)].val, tree[potom(v,1)].val);
    }
    else{
        //cout << tree[v].val << "\n\n";
        tree[v].Tagged += new_val;
        tree[v].val += new_val;
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

PII Search(LL v, LL sL, LL sR)
{
    //cout << v << " " <<sL << " " <<sR << "\n";
    if( (tree[v].Left != sL) || (tree[v].Right != sR) )
    {
        if (tree[v].Tagged) push(v);
        LL l_pot = potom(v,0);
        LL M = tree[l_pot].Right;
        if(sR <= M) return Search(l_pot, sL, sR);
        else if(M < sL)return Search(l_pot + 1, sL, sR);
        else  {
            PII left = Search(l_pot, sL, M);
            PII right = Search(l_pot + 1, M + 1, sR);
            if (left.FF > right.FF) {
                return left;
            }
            else
                return right;
        }
    }
    else{
        //cout << tree[v].val << "\n\n";
        return MP(tree[v].val, S(v, tree[v].val));
    }
}

bool comp (xBorder x1, xBorder x2)
{
    if (x1.x == x2.x) {
        return x1.t > x2.t;
    }
    return x1.x < x2.x;
}

void in()
{
    ios_base:: sync_with_stdio(false);
    cin.tie(0);
    //ifstream cin("G.in");
    cin >> n;
    VEC <rec> window;
    window.resize(n);
    int dy = 0, maxi = 0;
    for (int i = 0; i < n; ++i) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        window[i] = rec(x1, y1, x2, y2);
        dy = max(dy, (1-y1)*(y1 < 1) );
        dy = max(dy, (1-y2)*(y2 < 1) );
        maxi = max(maxi, y1);
        maxi = max(maxi, y2);
    }

    ln_count(maxi + dy);
    l_count = (ln+1) >> 1;
    for (LL i = l_count; i <= ln; ++i)
    {
        tree[i].val = 0;
        tree[i].Left =  tree[i].Right = i-l_count+1;
    }
    iniz_t();
    VEC <xBorder> xB;
    for (int i = 0; i < window.SZ; ++i) {
        xB.PB(xBorder(window[i].x1, 1, window[i].y1 + dy, window[i].y2 + dy));
        xB.PB(xBorder(window[i].x2, -1, window[i].y1 + dy, window[i].y2 + dy));
    }
    sort(xB.begin(), xB.end(), comp);
    //cout << "SZ : " << (ln+1)/2 << "\n";
    for (int i = 0; i < xB.SZ; ++i) {
        //cout << "NEW : " << xB[i].x << " " << xB[i].t << " " << xB[i].yL << " " <<xB[i].yH << "\n";
        add(1, xB[i].t, xB[i].yL, xB[i].yH);
        PII p = Search(1, 1, (ln+1)/2);
        if (p.FF > ansCnt) {
            ansCnt = p.FF;
            ansX = xB[i].x;
            ansY = p.SS-dy;
        }
    }
}

void out()
{
    cout.tie(0);
    //ofstream cout("G.out");
    cout << ansCnt << "\n" << ansX << " " << ansY << "\n";
}

int main()
{
    in();
    out();
    return 0;
}
