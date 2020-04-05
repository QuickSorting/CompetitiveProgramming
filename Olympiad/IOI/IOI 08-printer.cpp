#include <bits/stdc++.h>

using namespace std;

const int kN = 25000 + 1;
const int kLen = 20 + 1;

struct Trie{
	struct Node{
		map<char, int> next;
		int cnt_end;
		bool last_word;

		Node(){
			cnt_end = 0;
			last_word = false;
		}
	};
	Node nodes[kN * kLen];
	int sz;

	Trie(){
		sz = 1;
	}

	void add_word(const string &word){
		int curr_node = 0;
		for(char c: word){
			if(!nodes[curr_node].next.count(c)){
				nodes[curr_node].next[c] = sz;
				curr_node = sz++;
				continue;
			}

			curr_node = nodes[curr_node].next[c];
		}

		nodes[curr_node].cnt_end++;
	}
};

string s[kN];
Trie trie;
vector<char> operations;

void dfs(int u){
	for(int _ = 0; _ < trie.nodes[u].cnt_end; ++_)
		operations.push_back('P');

	char last_word_char;
	int last_word_idx = -1;
	for(auto t: trie.nodes[u].next){
		if(trie.nodes[t.second].last_word){
			last_word_idx = t.second;
			last_word_char = t.first;
			continue;
		}

		operations.push_back(t.first);
		dfs(t.second);
		operations.push_back('-');
	}

	if(last_word_idx != -1){
		operations.push_back(last_word_char);
		dfs(last_word_idx);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;

	int max_len = 0;
	for(int i = 0; i < n; ++i){
		cin >> s[i];
		trie.add_word(s[i]);
		max_len = max((int)s[i].size(), max_len);
	}

	for(int i = 0; i < n; ++i){
		if(s[i].size() == max_len){
			int curr_node = 0;
			for(int j = 0; j < s[i].size(); ++j){
				curr_node = trie.nodes[curr_node].next[s[i][j]];
				trie.nodes[curr_node].last_word = true;
			}
			break;
		}
	}

	dfs(0);

	cout << operations.size() << "\n";
	for(char operation: operations)
		cout << operation << "\n";
}