/*
	-I use two stacks to find the first and second next bigger number for each index
	-Then we have to consider a couple of cases inlcuding removing the first next bigger
	number for a index, which means it will then be able to go until the second one
*/
#include <bits/stdc++.h>

using namespace std;

const int kN = 1e6 + 7;

int a[kN], n;
pair<int, int> bigger[kN];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("turnuri.in", "r", stdin);
	freopen("turnuri.out", "w", stdout);

	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> a[i];

	stack<int> st1, st2, new2;
	for(int i = n - 1; i >= 0; --i){
		while(!st1.empty() && a[i] > a[st1.top()]){
			bigger[st1.top()].first = i;
			new2.push(st1.top());
			st1.pop();
		}
		st1.push(i);

		while(!st2.empty() && a[i] > a[st2.top()]){
			bigger[st2.top()].second = i;
			st2.pop();
		}

		while(!new2.empty()){
			st2.push(new2.top());
			new2.pop();
		}
	}

	while(!st1.empty()){
		bigger[st1.top()].first = -1;
		bigger[st1.top()].second = -1;
		st1.pop();
	}

	while(!st2.empty()){
		bigger[st2.top()].second = -1;
		st2.pop();
	}

	//for(int i = 0; i < n; ++i)
	//	cout << bigger[i].first << " " << bigger[i].second << endl;

	long long ans_normal = 0;
	for(int i = 0; i < n; ++i){
		if(bigger[i].first == -1)
			ans_normal += i;
		else
			ans_normal += i - bigger[i].first;
		//cout << ans_normal << " add" << endl;
	}

	long long ans_new = (long long)n * ans_normal;
	//cout << ans_normal << " " << ans_new << endl;
	for(int i = 0; i < n; ++i){
		if(bigger[i].first == -1)
			ans_new -= i;
		else
			ans_new -= i - bigger[i].first;

		if(bigger[i].first == -1){
			ans_new -= i;
			continue;
		}

		if(bigger[i].second == -1)
			ans_new += (i) - 1;
		else
			ans_new += (i - bigger[i].second) - 1;
		ans_new -= i - bigger[i].first ;

		ans_new -= i - bigger[i].first - 1;
	}

	cout << ans_new << "\n";
}