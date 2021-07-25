#include<iostream>
#include<stdio.h>
#include<utility>

#define fileIn "fastadd.in"
#define fileOut "fastadd.out"

#define uint unsigned int

using namespace std;

//constants
const uint array_size = (1 << 24);
const uint m_MIN = 1;
const uint m_MAX = (1 << 24);
const uint q_MIN = 1;
const uint q_MAX = (1 << 24);
const uint a_MIN = 1;
const uint a_MAX = (int)1e9;

//variables
uint m, q;
uint a, b;
uint array[array_size + 10];
uint answer;

//functions
void add(uint l, uint r, uint x) {
	array[l + 1] += x;
	array[r + 2] -= x;
}

uint sum(uint l, uint r) {
	return array[r + 1] - array[l];
}

//rand-gen
uint cur = 0;
uint nextRand() {
	cur = cur * a + b;
	return cur >> 8;
}

void addToSegment() {
	uint toAdd = nextRand();
	uint l = nextRand();
	uint r = nextRand();
	if (l > r) {
		swap(l, r);
	}
	add(l, r, toAdd);
}

uint sumOfSegment() {
	uint l = nextRand();
	uint r = nextRand();
	if (l > r) {
		swap(l, r);
	}
	return sum(l, r);
}

void in(){
	freopen(fileIn, "r", stdin);
	cin >> m >> q;
	cin >> a >> b;
}

void solution(){
	for (uint i = 0; i < m; i++) {
		addToSegment();
	}
	uint current = array[0];
	for (uint i = 1; i <= array_size; i++) {
		uint cur_save = current;
		current += array[i];
		array[i] += array[i - 1] + cur_save;
	}
	for (uint i = 0; i < q; i++) {
		answer += sumOfSegment();
	}
}

void out(){
	freopen(fileOut, "w", stdout);
	cout << answer << "\n";
}

int main(){
	in();
	solution();
	out();
	return 0;
}

