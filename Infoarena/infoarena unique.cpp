/*
	*Solved the problem using divide & conquer

	*Let's say we have solved (l, mid) and (mid + 1, r). Then to solve (l, r) we need
	to solve for the cases where the subset goes through the middle - so it includes mid and mid + 1.

	*We can do that by looking at our current range (sl, sr) which in the beginning is (mid, mid + 1)
	and check the next element on which side is smaller. Then we add this element and check if the current
	subset is ok and update the answer accordingly
	
	*How to check if a subset satisfies the property? We keep in a boolean array vis which elements we have, 
	cnt - the count of consecutive elements from 1 upwards we have, mx - the maximum element of the subset.
	
	*If we add element (cnt + 1) then we check how much we have to extend cnt. Then the check is simple -
	if cnt == mx, then we have all elements, and the subset is ok

	*The solution, however, is for some reason too slow and some optimizations are needed:
		-In the divide and conquer function if we have already found an answer that is better than what
		we could possibly get from the range (l, r), that means ans >= r - l + 1, then we can not look at
		this case
		-In the while loop for the subset, which is going through the middle, we can check whether the maximum
		element is too big to be able to reach it within this range

	Complexity: O(nlogn)
*/
#include <bits/stdc++.h>

using namespace std;

const int k_N = 1e5 + 7;

inline int max(const int &a, const int &b){
	return (a > b ? a : b);
}

int a[k_N], n, mx, cnt;
bool vis[k_N];

void add(int idx){
	if(!vis[a[idx]]){
		vis[a[idx]] = true;
		if(a[idx] == cnt + 1){
			while(vis[cnt + 1])
				++cnt;
		}
	}
}

inline void erase(int idx){
	vis[a[idx]] = false;
}

int ans;

void divide_and_conquer(int l, int r){
	if(ans >= r - l + 1)
		return;
	if(l == r){
		ans = max(ans, a[l] == 1);
		return;
	}

	int mid = (l + r) >> 1;
	divide_and_conquer(l, mid), divide_and_conquer(mid + 1, r);

	int sl = mid, sr = mid + 1;
	mx = max(a[mid], a[mid + 1]);
	cnt = 0;
	add(sl), add(sr); 
	if(cnt == mx)
		ans = max(ans, 2);

	while((sr != r || sl != l) && (mx <= r - l + 1)){
		if(sr == r || (sl != l && a[sl - 1] < a[sr + 1])){
			add(--sl);
			if(a[sl] > mx)
				mx = a[sl];
		}
		else{
			add(++sr);
			if(a[sr] > mx)
				mx = a[sr];
		}

		if(cnt == mx)
			ans = max(ans, sr - sl + 1);
	}

	for(int i = sl; i <= sr; ++i)
		erase(i);
}

void solve(){
	cin >> n;

	for(int i = 0; i < n; ++i)
		cin >> a[i];

	ans = 0;
	divide_and_conquer(0, n - 1);
	cout << ans << "\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("unique.in", "r", stdin);
	freopen("unique.out", "w", stdout);

	int t;
	cin >> t;

	while(t--)
		solve();
}