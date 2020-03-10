#include "friend.h"
#include <bits/stdc++.h>

using namespace std;

const int kN = 1007;

set<int> adj[kN];

int findSample(int n, int confidence[], int host[], int protocol[]){
	for(int i = 1; i < n; ++i){
		if(protocol[i] == 0){
			adj[i].insert(host[i]);
			adj[host[i]].insert(i);
		}
		else if(protocol[i] == 1){
			adj[i] = adj[host[i]];
			for(int to: adj[host[i]])
				adj[to].insert(i);
		}
		else if(protocol[i] == 2){
			adj[i] = adj[host[i]];
			for(int to: adj[host[i]])
				adj[to].insert(i);

			adj[i].insert(host[i]);
			adj[host[i]].insert(i);
		}
	}

	int ans = 0;
	for(int state = 0; state < (1 << n); ++state){
		int curr_ans = 0;
		for(int i = 0; i < n; ++i)
			if((1 << i) & state)
				curr_ans += confidence[i];

		if(curr_ans <= ans)
			continue;

		bool ok = true;
		for(int i = 0; i < n && ok; ++i){
			if(!(state & (1 << i)))
				continue;

			for(int j = i + 1; j < n && ok; ++j){
				if(!(state & (1 << j)))
					continue;

				if(adj[i].count(j))
					ok = false;
			}
		}

		if(ok)
			ans = curr_ans;
	}

	return ans;
}
