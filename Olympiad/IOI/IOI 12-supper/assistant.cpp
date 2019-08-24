/*
	Followed the editorial - http://www.ioi2012.org/hints-for-tasks-of-day-2/index.html
*/
#include <bits/stdc++.h>
#include "assistant.h"

using namespace std;

const int MAXN = 1e5 + 7;

vector<int> v2;
bool b[MAXN], ok[MAXN];

void Assist(unsigned char *A, int N, int K, int R) {
	for(int i = 0; i < K; ++i){
		if(!A[i]){
			ok[i] = true;
			v2.push_back(i);
		}
		b[i] = true;
	}

	for(int i = 0; i < N; ++i){
		int x = GetRequest();
		if(b[x]){
			ok[x] = !A[i + K];
			v2.push_back(x);
			continue;
		}

		while(true){
			if(b[v2.back()] && ok[v2.back()]){
				b[v2.back()] = false;
				ok[v2.back()] = false;
				PutBack(v2.back());
				ok[x] = !A[i + K];
				b[x] = true;
				v2.push_back(x);
				break;
			}
			v2.pop_back();
		}
	}
}
/*
4 2 100
2 0 3 2
*/
/*
g++ -DEVAL -Wall -static -std=c++11 -O2 -o supper grader.cpp assistant.cpp advisor.cpp
*/
