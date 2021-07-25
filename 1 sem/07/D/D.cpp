#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
#include<stdio.h>

#define fileIn "rmq.in"
#define fileOut "rmq.out"

using namespace std;

//RMQ
struct RMQ {
	int* tree;
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
		tree[ind] = min(tree[left(ind)], tree[right(ind)]);
	}
	
	int middle(int l, int r) {
		return l + (r - l) / 2;
	}
	
	RMQ(int* begin, int* end) {
		height = heightCounting(end - begin);
		size = 1 << height;
		firstLeaf = size >> 1;
		tree = new int[size + 1];
		int i;
		for (i = 0; begin + i != end ; i++) {
			tree[i + firstLeaf] = *(begin + i);
		}
		while (i + firstLeaf < size) {
			tree[i + firstLeaf] = 0;
			i++;
		}
		for (i = firstLeaf - 1; i > 0; i--) {
			update(i);
		}
	}
	
	void set(int ind, int value) {
		int i = ind + firstLeaf;
		tree[ind + firstLeaf] = value;
		while (i > 1) {
			i /= 2;
			update(i);
		}
	}
	
	int minSearch(int ind, int ls, int rs, int l, int r) {
		if (ls == l && rs == r) {
			return tree[ind];
		}
		int m = middle(l, r);
		if (rs <= m) {
			return minSearch(left(ind), ls, rs, l, m);
		} else if (ls > m) {
			return minSearch(right(ind), ls, rs, m + 1, r);
		} else {
			return min(
				minSearch(left(ind), ls, m, l, m),
				minSearch(right(ind), m + 1, rs, m + 1, r)
			);
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
const char operations[][5] = {"set", "min"};
#define setKey operations[0]
#define minKey operations[1]

//variables
int n, m;
int a[n_MAX + 1];
char qName[m_MAX + 1][5];
int qFirst[m_MAX + 1];
int qSecond[m_MAX + 1];
vector <int> answer;

void in(){
	freopen(fileIn, "r", stdin);
	scanf("%d\n", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	scanf("\n");
	while(scanf("%3s %d %d \n", &qName[m], &qFirst[m], &qSecond[m]) != -1) {
		m++;
	}
}

void solution(){
	RMQ rmq(a, a + n);
	for (int i = 0; i < m; i++) {
		if (strcmp(setKey, qName[i]) == 0) {
			rmq.set(qFirst[i] - 1, qSecond[i]);
		} else if (strcmp(minKey, qName[i]) == 0) {
			answer.push_back(rmq.minSearch(1, qFirst[i] - 1, qSecond[i] - 1, 0, rmq.firstLeaf - 1));
		}
	}
}

void out(){
	freopen(fileOut, "w", stdout);
	for (unsigned int i = 0; i < answer.size(); i++) {
		printf("%d\n", answer[i]);
	}
}

int main(){
	in();
	solution();
	out();
	return 0;
}

