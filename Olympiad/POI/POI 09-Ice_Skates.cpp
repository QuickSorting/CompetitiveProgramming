/*
	-The solution gets time limit on one of the initial tests, but gets 100 points
	-The polish system is strange

	-If the answer for a query is "NIE" then ther exists an interval of people
	-from size i - j, for which the inequality cnt(i) + cnt(i + 1) + ... + cnt(j) > (d + j - i + 1) * k
	-We can rearreange this to (cnt(i) - k) + (cnt(i + 1) - k) + ... + (cnt(j) - k) > d * k
	-So now we can maintain a segment tree which in turn maintains the maximum sum of an interval
	-Then if the answer is "NIE" the maximum sum will be large than d * k
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 7;

inline long long max(long long lvalue, long long rvalue){
	return ((lvalue > rvalue) ? lvalue : rvalue);
}

struct segment_tree{
	struct node{
		long long l, r, all, sum;

		node(){
			l = r = all = sum = 0;
		}

		node(long long val){
			if(val >= 0)
				l = r = all = val;
			else
				l = r = all = 0;
			sum = val;
		}

		friend node merge(node lvalue, node rvalue){
			node ret;
			ret.all = max(lvalue.all, max(rvalue.all, lvalue.r + rvalue.l));
			ret.l = max(lvalue.l, lvalue.sum + rvalue.l);
			ret.r = max(rvalue.r, rvalue.sum + lvalue.r);
			ret.sum = lvalue.sum + rvalue.sum;

			return ret;
		}
	};

	node arr[4 * MAXN];
	int n;

	segment_tree(int n = 0){
		this->n = n;
	}

	void update(int idx, int l, int r, int s, long long val){
		if(l > s || r < s)
			return;
		if(l == r){
			arr[idx] = node(val);
			return;
		}

		int mid = (l + r) >> 1;
		update(2 * idx, l, mid, s, val);
		update(2 * idx + 1, mid + 1, r, s, val);

		arr[idx] = merge(arr[2 * idx], arr[2 * idx + 1]);
	}

	void update(int s, long long val){
		update(1, 1, n, s, val);
	}

	long long query(){
		return arr[1].all;
	}
};

long long a[MAXN];
segment_tree st;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	long long n, m, k, d;
	cin >> n >> m >> k >> d;

	st.n = n;

	for(long long i = 0; i < n; ++i){
		a[i] = -k;
		st.update(i, a[i]);
	}

	for(long long i = 0; i < m; ++i){
		long long r, x;
		cin >> r >> x;

		a[r] += x;
		st.update(r, a[r]);

		cout << ((st.query() > d * k) ? "NIE" : "TAK") << "\n";
	}
}