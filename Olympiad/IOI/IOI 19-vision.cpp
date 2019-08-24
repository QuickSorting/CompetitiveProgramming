#include "vision.h"
#include <bits/stdc++.h>

using namespace std;

int add_not(int N);
int add_and(vector<int> Ns);
int add_or(vector<int> Ns);
int add_xor(vector<int> Ns);

vector<int> mv(int a, int b = -1, int c = -1){
	vector<int> v;

	v.push_back(a);
	if(b != -1){
		v.push_back(b);
	}
	if(c != -1){
		v.push_back(c);
	}

	return v;
}

vector<int> num;

void add(int x){
	for(int i = 0; i < (int)num.size(); ++i){
		int pr = num[i];

		num[i] = add_xor(mv(num[i], x));
		x = add_and(mv(pr, x));
	}
}

void construct_network(int H, int W, int K) {
	vector<int> row, col;
	int zero = add_and(mv(add_not(0), 0));

	for(int i = 0; i < H; ++i){
		vector<int> v;
		for(int j = 0; j < W; ++j){
			v.push_back(i * W + j);
		}

		row.push_back(add_xor(v));
	}

	for(int j = 0; j < W; ++j){
		vector<int> v;
		for(int i = 0; i < H; ++i){
			v.push_back(i * W + j);
		}

		col.push_back(add_xor(v));
	}

	for(int i = 0; i < 10; ++i){
		num.push_back(zero);
	}

	int curr = zero;
	for(int i = 0; i < H; ++i){
		curr = add_xor(mv(curr, row[i]));
		add(curr);
	}
	curr = zero;
	for(int i = 0; i < W; ++i){
		curr = add_xor(mv(curr, col[i]));
		add(curr);
	}

	vector<int> t;
	for(int i = 0; i < 10; ++i){
		if(K & (1 << i)){
			t.push_back(add_not(num[i]));
		}
		else{
			t.push_back(num[i]);
		}
	}

	int ans = add_not(add_or(t));
}
