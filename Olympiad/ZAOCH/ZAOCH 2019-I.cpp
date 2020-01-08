#include <bits/stdc++.h>

using namespace std;

const int MAX_SUM = 500;
const int MX_10 = 101;

vector<int> prime;
vector<vector<int> > pow_prime, pow_10, copy_cnt;
vector<bool> possible;

void init_powers(){
	prime = vector<int>{2, 3, 7, 11, 13, 17};

	for(int _ = 0; _ < (int)prime.size(); ++_){
		int &prime_ = prime[_];
		pow_prime.push_back(vector<int>());
		pow_10.push_back(vector<int>());
		vector<int> &pow_prime_ = pow_prime.back();
		vector<int> &pow_10_ = pow_10.back();
		
		pow_prime_.push_back(1);
		for(int i = 1; true; ++i){
			pow_prime_.push_back(0);
			pow_prime_[i] = pow_prime_[i - 1] * prime_;
			if(pow_prime_[i] > MAX_SUM){
				pow_prime_.pop_back();
				break;
			}
		}

		pow_10_.push_back(1);
		for(int i = 1; i < MX_10; ++i){
			pow_10_.push_back(0);
			pow_10_[i] = (pow_10_[i - 1] * 10) % pow_prime_.back();
		}
	}

	copy_cnt.resize(MAX_SUM, vector<int>(prime.size(), 0));
	possible.resize(MAX_SUM, false);
	for(int i = 1; i < MAX_SUM; ++i){
		int num = i;
		for(int j = 0; j < prime.size(); ++j){
			while(num % prime[j] == 0){
				num /= prime[j];
				++copy_cnt[i][j];
			}
		}
		possible[i] = (num == 1);
	}
}

int n;
void solve(int pos, int num, vector<int> &rem, vector<int> &cnt, string &curr){
	//cout << pos << " " << num << " " << rem2 << " " << cnt2 << " " << rem3 << " " << cnt3 << " " << curr << endl
	if(pos == n){
		for(int i = 0; i < (int)prime.size(); ++i){
			if(rem[i] % pow_prime[i][cnt[i]])
				return;
		}

		reverse(curr.begin(), curr.end());
		cout << curr << "\n";
		exit(0);
	}
	if(rem[0] % pow_prime[0][min(cnt[0], pos)])
		return;

	int branches_explored = 0;
	for(int i = 1; i <= 9; ++i){
		int copy_num = num + i;
		if(!possible[copy_num])
			continue;

		bool ok = true;
		for(int j = 0; j < prime.size(); ++j){
			if(copy_cnt[copy_num][j] >= pow_prime[j].size()){
				ok = false;
				break;
			}
		}

		if(!ok)
			continue;
		++branches_explored;

		curr += (char)('0' + i);

		vector<int> new_rem(prime.size()), new_cnt(prime.size());
		for(int j = 0; j < prime.size(); ++j){
			new_rem[j] = (pow_10[j][pos] * i + rem[j]) % pow_prime[j].back();
			new_cnt[j] = max(cnt[j], copy_cnt[copy_num][j]);
		}
		solve(pos + 1, num + i, new_rem, new_cnt, curr);

		curr.erase(curr.size() - 1, 1);

		if(branches_explored >= 2/* || (pos >= 25 && (n - pos) > 2)*/)
			break;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	init_powers();

	cin >> n;

	string str = "";
	vector<int> rem, cnt;
	rem.resize(prime.size(), 0);
	cnt.resize(prime.size(), 0);
	solve(0, 0, rem, cnt, str);
}