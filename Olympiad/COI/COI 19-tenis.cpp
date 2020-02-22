/*
	-There exists a border where if the player is in left of it, he can win
	-Moreover, every player who can win is on the left of the border for all disciplines
	-So we can solve the problem using segment tree where we find the first place where all people that
	are on the left of the border don't have a discipline where they are on the right of it.
*/
#include <bits/stdc++.h>

using namespace std;

const int kNMax = 1e5 + 7;

struct segment_tree{
	pair<int, int> nodes[4 * kNMax];
	int lazy[4 * kNMax];

	segment_tree(){}

	void build(int idx, int l, int r){
		if(l == r){
			nodes[idx] = {l, l};
			return;
		}

		int mid = (l + r) >> 1;
		build(2 * idx, l, mid);
		build(2 * idx + 1, mid + 1, r);

		nodes[idx] = min(nodes[2 * idx], nodes[2 * idx + 1]);
	}

	void update(int idx, int l, int r, int sl, int sr, int val){
		if(lazy[idx]){
			nodes[idx].first += lazy[idx];
			if(l != r){
				lazy[2 * idx] += lazy[idx];
				lazy[2 * idx + 1] += lazy[idx];
			}
			lazy[idx] = 0;
		}

		if(sl > r || l > sr)
			return;
		if(sl <= l && r <= sr){
			nodes[idx].first += val;
			if(l != r){
				lazy[2 * idx] += val;
				lazy[2 * idx + 1] += val;
			}
			return;
		}

		int mid = (l + r) >> 1;
		update(2 * idx, l, mid, sl, sr, val);
		update(2 * idx + 1, mid + 1, r, sl, sr, val);

		nodes[idx] = min(nodes[2 * idx], nodes[2 * idx + 1]);
	}

	int query(){
		return nodes[1].second;
	}
};

int n, q;
int a[3][kNMax], mx[kNMax], pos[3][kNMax];
int cnt[kNMax];
segment_tree seg_tr;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;
	for(int i = 0; i < 3; ++i){
		for(int j = 1; j <= n; ++j){
			cin >> a[i][j];
			pos[i][a[i][j]] = j;
		}
	}

	for(int i = 1; i <= n; ++i){
		mx[i] = 0;
		for(int j = 0; j < 3; ++j)
			mx[i] = max(mx[i], pos[j][i]);
		++cnt[mx[i]];
	}

	seg_tr.build(1, 1, n);
	for(int i = 1; i <= n; ++i){
		seg_tr.update(1, 1, n, i, n, -cnt[i]);
	}

	int border = seg_tr.query();
	for(int i = 0; i < q; ++i){
		int type;
		cin >> type;

		if(type == 1){
			int x;
			cin >> x;

			if(mx[x] <= border)
				cout << "DA\n";
			else
				cout << "NE\n";
		}
		else{
			int p, a, b;
			cin >> p >> a >> b;
			--p;
			swap(pos[p][a], pos[p][b]);

			int pr_mx_a = mx[a], pr_mx_b = mx[b];

			mx[a] = 0;
			mx[b] = 0;
			for(int j = 0; j < 3; ++j){
				mx[a] = max(mx[a], pos[j][a]);
				mx[b] = max(mx[b], pos[j][b]);
			}

			array<int, 4> changed = {pr_mx_a, pr_mx_b, mx[a], mx[b]};
			sort(changed.begin(), changed.end());

			for(int i = 0; i < 4; ++i){
				if(i == 0 || changed[i] != changed[i - 1])
					seg_tr.update(1, 1, n, changed[i], n, cnt[changed[i]]);
			}

			--cnt[pr_mx_a];
			--cnt[pr_mx_b];
			++cnt[mx[a]];
			++cnt[mx[b]];

			for(int i = 0; i < 4; ++i){
				if(i == 0 || changed[i] != changed[i - 1])
					seg_tr.update(1, 1, n, changed[i], n, -cnt[changed[i]]);
			}

			border = seg_tr.query();
		}
	}
}
/*
4 2
1 2 3 4
2 1 3 4
2 4 3 1
1 1
1 4
*/