#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<limits.h>

#include<conio.h>

#define fileIn "sparse.in"
#define fileOut "sparse.out"

#define uint unsigned int

using namespace std;

//constants
const uint n_MIN = 1;
const uint n_MAX = (uint)1e5;
const uint m_MIN = 1;
const uint m_MAX = (uint)1e7;
const uint a_MIN = 0;
const uint a_MAX = 16714589;

//variables
uint arr[n_MAX];
uint n, m;
uint u1, v1;
uint um, vm, ansm;

//generators
uint nextA(uint a) {
	return (23 * a + 21563) % a_MAX;
}

uint nextU(uint u, uint ans, uint i) {
	return (17 * u + 751 + ans + 2 * i) % n + 1;
}

uint nextV(uint v, uint ans, uint i) {
	return (13 * v + 593 + ans + 5 * i) % n + 1;
}

//functions
uint fl(uint len) {
	return (len == 1? 0:(fl(len / 2) + 1));
}

uint pow2(uint s) {
	return (uint)1 << s;
}

//filling array in
void fillingArrayIn() {
	for (uint i = 1; i < n; i++) {
		arr[i] = nextA(arr[i - 1]);
	}
}

//filling sparse in
uint sparse[n_MAX << 1][32 << 1];
uint sparseCounting(uint i, uint j) {
	if (sparse[i][j] < INT_MAX) {
		return sparse[i][j];
	}
	if (j == 0) {
		sparse[i][j] = arr[i];
	} else {
		uint res1 = j < 0? (INT_MAX - 1) : sparseCounting(i, j - 1);
		uint ind = i + pow2(j - 1);
		uint res2 = ind < n? sparseCounting(ind, j - 1) : (INT_MAX - 1);
		sparse[i][j] = min(res1, res2);
	}
	return sparse[i][j];
}

void fillingSparseIn() {
	for (uint i = 0; i < (n_MAX << 1); i++) {
		for (uint j = 0; j < (32 << 1); j++) {
			sparse[i][j] = INT_MAX;
		}
	}
	uint j = fl(n);
	for (uint i = 0; i < (n_MAX << 1); i++) {
		for (uint j = 0; j < (32 << 1); j++) {
			sparse[i][j] = sparseCounting(i, j);
		}
	}
}

//get answer from sparse
uint getAns(uint l, uint r) {
	if (l > r) {
		swap(l, r);
	}
	uint f = fl(r - l + 1);
	uint j = max(f, pow2(f));
	uint ind = r - pow2(j) + 1
	if (ind < 0) {
	}
	return min(sparse[l][j], sparse[r - pow2(j) + 1][j]);
}

void in(){
	freopen(fileIn, "r", stdin);
	cin >> n >> m >> arr[0];
	cin >> u1 >> v1;
}

void solution(){
	fillingArrayIn();
	fillingSparseIn();
	for (uint i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << "\n";
	for (uint i = 0; i < n; i++) {
		for (uint j = 0; j < fl(n) + 1; j++) {
			cout << sparse[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	uint u = u1;
	uint v = u1;
	uint ans;
	for (uint i = 0; i < m; i++) {
		cout << u << " " << v << "\n";
		ans = getAns(u - 1, v - 1);
		u = nextU(u, ans, i + 1);
		v = nextV(v, ans, i + 1);
	}
	um = u;
	vm = v;
	ansm = getAns(u - 1, v - 1);
}

void out(){
	freopen(fileOut, "w", stdout);
	cout << um << " " << vm << " " << ansm << "\n";
}

int main(){
	in();
	solution();
	out();
	getch();
	return 0;
}

