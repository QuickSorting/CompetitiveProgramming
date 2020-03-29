/*
	-In the beginning we will find the first elemnt by calling ask(1)
	-Then for each bit i from 0 to 6 we will find all the xors of ans[0] and
	the elements with indices that contain the bit i and we place them in mp
	-That means that ans[j] should be included in all mp[i] if the i-th bit is set
	in j and should not be included otherwise
	-Because all elements are different there will be only one answer that corresponds to
	each position
	15 queries
*/
#include <bits/stdc++.h>
#include "interactive.h"

using namespace std;

const int kBits = 7;

map<int, bool> mp[kBits];

vector<int> guess(int n) {
	vector <int> ans(n);
	ans[0] = ask(1);

	for(int i = 0; i < 7; ++i){
		vector<int> v;
		for(int j = 2; j <= n; ++j){
			if((1 << i) & j)
				v.push_back(j);
		}

		if(v.empty())
			continue;

		vector<int> pairs_without = get_pairwise_xor(v);
		pairs_without.insert(pairs_without.begin(), 0);
		v.push_back(1);
		vector<int> pairs_with = get_pairwise_xor(v);

		for(int idx_with = 0, idx_without = 0; idx_with < pairs_with.size(); ++idx_with){
			if(idx_without < pairs_without.size() && pairs_with[idx_with] == pairs_without[idx_without])
				++idx_without;
			else
				mp[i][pairs_with[idx_with]] = true;
		}
	}

	for(int i = 2; i <= n; ++i){
		int first_bit = 0;
		for(; first_bit < kBits; ++first_bit)
			if((1 << first_bit) & i)
				break;

		ans[i - 1] = -1;
		for(auto p: mp[first_bit]){
			int x = p.first;
			bool ok = true;

			for(int bit = 0; bit < kBits; ++bit){
				if(bit == first_bit)
					continue;

				if((1 << bit) & i){
					if(!mp[bit].count(x)){
						ok = false;
						break;
					}
				}
				else{
					if(mp[bit].count(x)){
						ok = false;
						break;
					}
				}
			}

			if(ok){
				ans[i - 1] = x ^ ans[0];
				break;
			}
		}
	}

	return ans;
}
