/*
	Followed the editorial - http://www.ioi2012.org/hints-for-tasks-of-day-2/index.html
*/
#include <bits/stdc++.h>
#include "advisor.h"

using namespace std;

const int MAXN = 1e5 + 7;

int nxt[MAXN];

struct cmp{
	bool operator()(pair<int, int> lvalue, pair<int, int> rvalue){
		if(lvalue.second != rvalue.second){
			return lvalue.second > rvalue.second;
		}

		return lvalue.first > rvalue.first;
	}
};

set<pair<int, int>, cmp> pq;
int cnt[MAXN];
vector<int> v[MAXN];

int pos[MAXN];
vector<bool> ans;

void ComputeAdvice(int *C, int N, int K, int M) {
	for(int i = 0; i < N; ++i){
		v[C[i]].push_back(i);
	}
	for(int i = 0; i < N; ++i){
		v[i].push_back(N);
		nxt[i] = v[i][0];
		cnt[i] = 0;
	}

	for(int i = 0; i < N + K; ++i){
		ans.push_back(false);
	}

	for(int i = 0; i < K; ++i){
		pos[i] = i;
		pq.insert({i, nxt[i]});
	}

	for(int i = 0; i < N; ++i){
		if(pq.find({C[i], nxt[C[i]]}) == pq.end()){
			pair<int, int> p = *pq.begin();
			int x = p.first;

			ans[pos[x]] = false;

			pq.erase(p);
			nxt[C[i]] = v[C[i]][++cnt[C[i]]];
			pq.insert({C[i], nxt[C[i]]});

			pos[C[i]] = K + i;
		}
		else{
			ans[pos[C[i]]] = true;

			pq.erase({C[i], nxt[C[i]]});
			nxt[C[i]] = v[C[i]][++cnt[C[i]]];
			pq.insert({C[i], nxt[C[i]]});

			pos[C[i]] = K + i;
		}
	}

	while(!pq.empty()){
		pair<int, int> p = *pq.begin();
		int x = p.first;

		ans[pos[x]] = true;

		pq.erase(p);
	}

	for(bool b: ans){
		WriteAdvice(b);
		//cout << b << " ";
	}
	//cout << endl;
}
