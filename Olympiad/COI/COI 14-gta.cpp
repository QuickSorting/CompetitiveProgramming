#include <bits/stdc++.h>

using namespace std;

char idx[256], ch[4] = {'A', 'G', 'T', 'C'};
pair<char, char> lnk1[4];
char lnk2[4][4]; 

map<string, bool> mp[4];

void find_strings(int x, string & s, int mx){
	if((int)s.size() > mx)
		return;
	if(mp[x].count(s))
		return;
	
	mp[x][s] = true;
	for(char c: s){
		cout << ch[c];
	}
	cout << endl; 

	for(int i = 0; i < (int)s.size(); ++i){
		int pr = s[i];

		string t = "";
		t += lnk1[pr].first;
		t += lnk1[pr].second;

		s.erase(i, 1);
		s.insert(i, t);

		find_strings(x, s, mx);

		t = pr;
		s.erase(i, 2);
		s.insert(i, t);
	}
}

void init(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	for(int i = 0; i < 4; ++i){
		idx[ch[i]] = i;
	}

	for(int i = 0; i < 4; ++i){
		for(int j = 0; j < 4; ++j){
			lnk2[i][j] = -1;
		}
	}
	lnk1[0] = {2, 3};
	lnk1[1] = {3, 2};
	lnk1[2] = {1, 0};
	lnk1[3] = {0, 1};

	for(int i = 0; i < 4; ++i){
		lnk2[ lnk1[i].first ][ lnk1[i].second ] = i;
	}

	string s = "";
	s += (char)0;
	find_strings(0, s, 10);
}

int main(){
	init();
}