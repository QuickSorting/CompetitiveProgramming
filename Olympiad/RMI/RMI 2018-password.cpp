/*
	We can compare the position of the next letter for each letter of the alphabet in one operation
	So we maintain a sorted array of the letters
	The first one is obviously the next letter so we output it
	After that we remove it and try to find where it's new place in the array will be
*/
#include <bits/stdc++.h>

using namespace std;

int query(const string &s){
	cout << s << "\n";
	fflush(stdout);

	int ret;

	cin >> ret;

	return ret;
}

int cnt[256], let[26];
string ans = "";

bool first(int lvalue, int rvalue){
	if(!cnt[lvalue])
		return false;
	if(!cnt[rvalue])
		return true;

	string x = ans;
	x += lvalue;
	for(int k = 0; k < cnt[rvalue]; ++k)
		x += rvalue;
	if(query(x) != ans.size() + cnt[rvalue] + 1)
		return false;

	return true;
}

void insert(int x, int pos){
	for(int i = 25; i > pos; --i){
		let[i] = let[i - 1];
	}
	let[pos] = x;
}

int main(){
	//freopen("password2.in", "r", stdin);
	//freopen("password2.out", "w", stdout);

	int n, s;

	cin >> n >> s;

	if(s == 1){
		string ans = "";
		for(int i = 0; i < n; ++i){
			ans += 'a';
		}

		query(ans);

		return 0;
	}

	for(int i = 'a'; i < 'a' + s; ++i){
		string s = "";
		for(int j = 0; j < n; ++j){
			s += i;
		}
		cnt[i] = query(s);
	}

	let[0] = 'a';
	for(int i = 1; i < s; ++i){
		int l = 0, r = i;

		while(l != r){
			int mid = (l + r) >> 1;

			//cout << l << " " << r << endl;

			if(first(i + 'a', let[mid])){
				r = mid;
			}
			else{
				l = mid + 1;
			}
		}
		insert(i + 'a', l);
	}
	ans += let[0];
	--cnt[let[0]];
//
	for(int i = 0; i < n - 1; ++i){
		int c = let[0];
		for(int j = 0; j < 25; ++j){
			let[j] = let[j + 1];
		}

		int l = 0, r = s - 1;

		while(l != r){
			int mid = (l + r) >> 1;

			//cout << l << " " << r << endl;

			if(first(c, let[mid])){
				r = mid;
			}
			else{
				l = mid + 1;
			}
		}
		insert(c, l);
		ans += let[0];
		--cnt[let[0]];
	}

	query(ans);

	return 0;
}