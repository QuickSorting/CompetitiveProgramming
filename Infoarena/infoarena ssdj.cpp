/*
	followed this - https://github.com/stefdasca/CompetitiveProgramming/blob/master/Infoarena/ssdj.cpp	
*/
#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC target("sse4")

using namespace std;

const int MAXN = 1007;

int pr[MAXN][MAXN];
string s2[MAXN];
int ans = 0;

struct my_stack{
	int arr[MAXN];
	int sz;

	my_stack(){
		sz = 0;
	}
	inline void clear(){
		sz = 0;
	}
	inline void push_back(int x){
		arr[sz++] = x;
	}
	inline void pop_back(){
		--sz;
	}
	inline int get_arr(int idx){
		return arr[idx];
	}
	inline bool empty(){
		return !sz;
	}
	inline int back(){
		return arr[sz - 1];
	}
	inline int size(){
		return sz;
	}
};

my_stack st;

inline char get_s(int x, int y){
	return s2[x - 1][y - 1];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("ssdj.in", "r", stdin);
	freopen("ssdj.out", "w", stdout);

	int n;

	cin >> n;

	for(int i = 0; i < n; ++i){
		cin >> s2[i];
	}

	for(char c = 'a'; c <= 'z'; ++c){
		for(int i = 0; i <= n + 1; ++i){
			for(int j = 0; j <= n + 1; ++j){
				pr[i][j] = 0;
			}
		}
		for(int i = 1; i <= n; ++i){
			st.clear();
			for(int j = 1; j <= n; ++j){
				if(get_s(i, j) >= c){
					pr[i][j] = i;
				}
				else{
					pr[i][j] = pr[i - 1][j];
				}

				while(!st.empty() && pr[i - 1][j] >= pr[i][st.back()]){
					st.pop_back();
				}

				if(get_s(i, j) == c){
					ans += st.size();
					if(!st.empty() && st.get_arr(0) == j){
						--ans;
					}
				}

				while(!st.empty() && pr[i][j] >= pr[i][st.back()]){
					st.pop_back();
				}

				if(pr[i][j] <= i - 1 && pr[i][j] != 0){
					st.push_back(j);
				}
			}
		}

		for(int i = 0; i <= n + 1; ++i){
			for(int j = 0; j <= n + 1; ++j){
				pr[i][j] = n + 1;
			}
		}
		for(int i = n; i >= 1; --i){
			st.clear();
			int eq = 0;
			for(int j = n; j >= 1; --j){
				if(get_s(i, j) >= c){
					pr[i][j] = i;
				}
				else{
					pr[i][j] = pr[i + 1][j];
				}

				while(!st.empty() && pr[i + 1][j] <= pr[i][st.back()]){
					if(get_s(pr[i][st.back()],st.back()) == c){
						--eq;
					}
					st.pop_back();
				}

				if(get_s(i, j) == c){
					ans += st.size();
					ans -= eq;
					if(!st.empty() && st.back() == j){
						--ans;
					}
				}

				while(!st.empty() && pr[i][j] <= pr[i][st.back()]){
					if(get_s(pr[i][st.back()], st.back()) == c){
						--eq;
					}
					st.pop_back();
				}
				if(pr[i][j] >= i + 1 && pr[i][j] != n + 1){
					if(get_s(pr[i][j], j) == c){
						++eq;
					}
					st.push_back(j);
				}
			}
		}
	}

	cout << ans << "\n";

	return 0;
}
/*
4
caae
aada
abaa
aaba
*/
/*
4
abaa
aaba
adaa
eaac
*/