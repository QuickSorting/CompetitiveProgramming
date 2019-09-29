/*
	This is not the cleanest solution, but it works, I guess.
	So we first do intervals [1...(n/2 + n%2)] and [(n/2 + n%2)...1]
	If we get two BIP there, we can locate the bomb and query it until we hear n BIPs
	Otherwise we continue with [(n/2 + n %2 + 1)...n] and [(n/2 + n%2 + 1)...n].
	Now if we DON'T have two BIPs then the bomb is in the right part and we again do the same intervals and then locate the bomb.
	Otherwise though, we can't be certain whether the bomb is in the left or right part.
	So we calculate the eventual answers for both cases. Then we also calculate the expected time when we should get a BIP for both of them.
	When we get one, we check to which it corresponds, and we do this tile until we hear n BIPs.

	For the first case we have 0(3 * n) queries
	For the second case we have O(5 * n) queries
	For the third case we have O(2 * n (for the first four intervals) + n (for finding in which side is the bomb) + 2 * n (actually removing it))
*/
#include <bits/stdc++.h>

using namespace std;

bool query(int x){
	cout << x << "\n";
	fflush(stdout);

	string s;
	cin >> s;

	return (s == "BIP");
}

int main(){
	string line;
	cin >> line;

	int n, t, r;

	cin >> n >> t >> r;

	int cnt = 0;
	int m1 = n / 2 + n % 2, m2 = n / 2;
	int cnt_q = 1, p1 = -1, p2 = -1, p3 = -1, p4 = -1;
	bool first = false;

	for(int j = 1;  j < 1 + m1; ++j, ++cnt_q){
		if(query(j)){
			++cnt;
			if(p1 == -1){
				p1 = cnt_q;
			}
			else{
				if(p2 == -1){
					p2 = cnt_q;
				}
			}
		}
	}
	for(int j = m1; j >= 1; --j, ++cnt_q){
		if(query(j)){
			++cnt;
			if(p1 == -1){
				p1 = cnt_q;
			}
			else{
				if(p2 == -1){
					p2 = cnt_q;
				}
			}
		}
	}

	if(p1 != -1){
		first = true;
	}

	//cout << p1 << " p1 p2 " << p2 << endl;

	if(p1 != -1 && p2 != -1){
		int a = (p1 - p2 + 1) / 2 + m1;
		//cout << diff << endl;
		//cout << (p1 - p2 + 1) / 2 << endl;

		while(cnt < n){
			cnt += query(a);
		}
		return 0;
	}

	for(int j = 1 + m1;  j <= n && p2 == -1; ++j, ++cnt_q){
		if(query(j)){
			++cnt;
			if(p1 == -1){
				p1 = cnt_q;
			}
			else{
				if(p2 == -1){
					p2 = cnt_q;
					break;
				}
			}
		}
	}
	for(int j = n; j >= m1 + 1 && p2 == -1; --j, ++cnt_q){
		if(query(j)){
			++cnt;
			if(p1 == -1){
				p1 = cnt_q;
			}
			else{
				if(p2 == -1){
					p2 = cnt_q;
					break;
				}
			}
		}
	}

	//cout << p1 << " p1 p2 " << p2 << endl;

	if(p1 != -1 && p2 != -1){
		if(first){
			int a = (p1 - p2 + 1) / 2 + m1;

			while(cnt < n){
				cnt += query(a);
			}
			return 0;
		}

		if(p3 == -1){
			int a1 = (p1 - p2 + 1) / 2 + m1;
			int a2 = (p1 - p2 + 1) / 2 + n;
			//cout << diff << endl;
			//cout << (p1 - p2 + 1) / 2 << endl;

			int q1 = cnt_q, q2 = cnt_q + 1;
			int y1 = (p1 + p2 - 1) / 2 - m1;

			while(cnt < n){
				if(query(a1)){
					++cnt;
					if(cnt_q == q1 + y1){
						while(cnt < n){
							cnt += query(a1);
						}
						return 0;
					}
					else{
						while(cnt < n){
							cnt += query(a2);
						}
						return 0;
					}
				}
				++cnt_q;
				if(query(a2)){
					++cnt;
					if(cnt_q == q1 + y1){
						while(cnt < n){
							cnt += query(a1);
						}
						return 0;
					}
					else{
						while(cnt < n){
							cnt += query(a2);
						}
						return 0;
					}
				}
				++cnt_q;
			}
			return 0;
		}
	}

	for(int j = 1 + m1;  j <= n; ++j, ++cnt_q){
		if(query(j)){
			++cnt;
			if(p1 == -1){
				p1 = cnt_q;
			}
			else{
				if(p2 == -1){
					p2 = cnt_q;
				}
			}
		}
	}
	for(int j = n; j >= m1 + 1; --j, ++cnt_q){
		if(query(j)){
			++cnt;
			if(p1 == -1){
				p1 = cnt_q;
			}
			else{
				if(p2 == -1){
					p2 = cnt_q;
				}
			}
		}
	}

	if(p1 != -1 && p2 != -1){
		int a = (p1 - p2 + 1) / 2 + n;
		//cout << diff << endl;
		//cout << (p1 - p2 + 1) / 2 << endl;

		while(cnt < n){
			cnt += query(a);
		}
		return 0;
	}

	return 0;
}