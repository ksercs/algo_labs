#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
#include<stdio.h>

#define fileIn "rsq.in"
#define fileOut "rsq.out"

#define ll long long

using namespace std;

//RMQ
struct RSQ {
	ll* tree;
	int height;
	int size;
	int firstLeaf;
	
	int heightCounting(int len) {
		len--;
		int res = 1;
		while (len > 0) {
			len /= 2;
			res++;
		}
		return res;
	}
	
	int left(int ind) {
		return ind << 1;
	}
	
	int right(int ind) {
		return left(ind) + 1;
	}
	
	void update(int ind) {
		tree[ind] = tree[left(ind)] + tree[right(ind)];
	}
	
	int middle(int l, int r) {
		return l + (r - l) / 2;
	}
	
	RSQ(ll* begin, ll* end) {
		height = heightCounting(end - begin);
		size = 1 << height;
		firstLeaf = size >> 1;
		tree = new ll[size + 1];
		ll i;
		for (i = 0; begin + i != end ; i++) {
			tree[i + firstLeaf] = *(begin + i);
		}
		while (i + firstLeaf < size) {
			tree[i + firstLeaf] = 0;
			i++;
		}
		for (i = firstLeaf - 1; i > 0; i--) {
			update((int)i);
		}
	}
	
	void set(ll ind, ll value) {
		int i = (int)ind + firstLeaf;
		tree[(int)ind + firstLeaf] = value;
		while (i > 1) {
			i /= 2;
			update(i);
		}
	}
	
	ll sum(int ind, int ls, int rs, int l, int r) {
		if (ls == l && rs == r) {
			return tree[ind];
		}
		int m = middle(l, r);
		if (rs <= m) {
			return sum(left(ind), ls, rs, l, m);
		} else if (ls > m) {
			return sum(right(ind), ls, rs, m + 1, r);
		} else {
			return sum(left(ind), ls, m, l, m) + sum(right(ind), m + 1, rs, m + 1, r);
		}
	}
	/*
	void look() {
		for (int i = 1; i < size; i++) {
			cout << i << ". " << tree[i] << " \n";
		}
	}
	*/
};

//constants
const int n_MIN = 1;
const int n_MAX = 500000;
const int m_MAX = 1000000;
const int a_MIN = (int)-1e9;
const int a_MAX = (int)1e9;
const char operations[][5] = {"set", "sum"};
#define setKey operations[0]
#define sumOfKeys operations[1]

//variables
int n, m;
ll a[n_MAX + 1];
char qName[m_MAX + 1][5];
ll qFirst[m_MAX + 1];
ll qSecond[m_MAX + 1];
vector <ll> answer;

void in(){
	freopen(fileIn, "r", stdin);
	scanf("%d\n", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &a[i]);
	}
	scanf("\n");
	char forRead[5];
	while(scanf("%3s %lld %lld \n", &forRead, &qFirst[m], &qSecond[m]) != -1) {
		strcpy(qName[m], forRead);
		m++;
	}
}

void solution(){
	RSQ rsq(a, a + n);
	for (int i = 0; i < m; i++) {
		if (strcmp(setKey, qName[i]) == 0) {
			rsq.set(qFirst[i] - 1ll, qSecond[i]);
		} else if (strcmp(sumOfKeys, qName[i]) == 0) {
			answer.push_back(rsq.sum(1, (int)qFirst[i] - 1, (int)qSecond[i] - 1, 0, rsq.firstLeaf - 1));
		}
	}
}

void out(){
	freopen(fileOut, "w", stdout);
	for (unsigned int i = 0; i < answer.size(); i++) {
		printf("%lld\n", answer[i]);
	}
}

int main(){
	in();
	solution();
	out();
	return 0;
}

