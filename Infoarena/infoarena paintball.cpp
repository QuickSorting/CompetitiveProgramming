/*
	-Instead of finding the min and max deaths I find the min and max survivors.	
	-The min for a component is either 1 if it is just a cycle or the number of nodes with in-degree 0
	-The max for a components can be found by first removing an in-degree 0 node at each step, because it
	cannot be killed and when we reach a cycle we can just add len_cycle / 2
	-The time limit is really tight so we don't have to time to find all the distinct components so we 
	have to do everything at the same time
	O(n) 
*/
#include <bits/stdc++.h>

using namespace std;

const int kN = 1e6 + 7;

int edge[kN], in[kN], pr[kN];
int in0[kN], cnt0;
bool vis[kN];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("paintball.in", "r", stdin);
	freopen("paintball.out", "w", stdout);

	int n;
	cin >> n;

	for(int i = 1; i <= n; ++i){
		cin >> edge[i];
		++in[edge[i]];
	}

	for(int i = 1; i <= n; ++i){
		if(!in[i])
			in0[cnt0++] = i;
		pr[i] = in[i];
	}

	int min_ans = cnt0, max_ans = 0;
	while(cnt0){
		int u = in0[--cnt0];

		vis[u] = true;
		++max_ans;

		int to = edge[u];
		if(!vis[to]){
			vis[to] = true;
			if(!vis[edge[to]]){
				--in[edge[to]];
				if(!in[edge[to]])
					in0[cnt0++] = edge[to];
			}
		}
	}

	for(int i = 1; i <= n; ++i){
		if(!vis[i]){
			int u = i, cnt = 0;
			bool bigger = false;
			while(!vis[u]){
				vis[u] = true;
				++cnt;
				if(pr[u] > 1)
					bigger = true;
				u = edge[u];
			}

			max_ans += cnt >> 1;
			if(!bigger && cnt > 1)
				++min_ans;
		}
	}

	cout << n - max_ans << " " << n - min_ans << "\n";
}