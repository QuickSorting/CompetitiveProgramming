#include <bits/stdc++.h>

using namespace std;

mt19937 rng(7);
struct ImplicitTreap{
private:
	struct Node;
	typedef Node* pNode;
	
	struct Node{
		int prior, cnt;
		char val;
		bool rev;
		pNode l, r;

		Node(){}
		Node(char val){
			prior = rng();
			this->val = val;
			cnt = 1;
			rev = false;
			l = r = nullptr;
		}
	};

	int cnt(pNode it){
		return it ? it->cnt : 0;
	}

	void upd_cnt(pNode it){
		if(it)
			it->cnt = cnt(it->l) + cnt(it->r) + 1;
	}

	void push(pNode it){
		if(it && it->rev){
			it->rev = false;
			swap(it->l, it->r);
			if(it->l)
				it->l->rev ^= true;
			if(it->r)
				it->r->rev ^= true;
		}
	}

	void merge(pNode &t, pNode l, pNode r){
		push(l);
		push(r);

		if(!l || !r)
			t = l ? l : r;
		else if(l->prior > r->prior)
			merge(l->r, l->r, r), t = l;
		else
			merge(r->l, l, r->l), t = r;
		upd_cnt(t);
	}

	void split(pNode t, pNode &l, pNode &r, int key, int add = 0){
		if(!t){
			l = r = nullptr;
			return;
		}
		push(t);

		int curr_key = add + cnt(t->l);
		if(key <= curr_key)
			split(t->l, l, t->l, key, add), r = t;
		else
			split(t->r, t->r, r, key, add + 1 + cnt(t->l)), l = t;
		upd_cnt(t);
	}

	void reverse(pNode &t, int l, int r){
		pNode t1, t2, t3, t4;
		split(t, t1, t2, l);
		split(t2, t3, t4, r - l + 1);
		t3->rev ^= true;
		merge(t2, t3, t4);
		merge(t, t1, t2);
	}
public:
	pNode root;
	ImplicitTreap(){
		root = nullptr;
	}

	void insert(int pos, int val){
		if(!root){
			root = new Node(val);
			return;
		}

		pNode l, r, nw = new Node(val);
		split(root, l, r, pos);
		merge(l, l, nw);
		merge(root, l, r);
	}

	char query(int pos){
		pNode t1, t2, t3, t4;
		split(root, t1, t2, pos);
		split(t2, t3, t4, 1);

		char ret = t3->val;

		merge(t2, t3, t4);
		merge(root, t1, t2);
		return ret;
	}

	void reverse(int l, int r){
		reverse(root, l, r);
	}
};

ImplicitTreap treap;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, l, r;
	cin >> n >> l >> r;
	--l;
	--r;

	string cells;
	cin >> cells;

	for(int i = 0; i < n; ++i)
		treap.insert(i, cells[i]);

	int m;
	cin >> m;

	for(int i = 0; i < m; ++i){
		//cout << endl;
		//cout << l << " " << r << " l r" << endl;
		char type;
		cin >> type;

		if(type == 'S'){
			//move
			char x, y;
			cin >> x >> y;

			if(x == 'L'){
				if(y == 'L')
					--l;
				else
					++l;
			}
			else{
				if(y == 'L')
					--r;
				else
					++r;
			}
		}
		else if(type == 'R'){
			//reverse
			treap.reverse(l, r);
		}
		else if(type == 'Q'){
			//query
			char x;
			cin >> x;

			if(x == 'L')
				cout << treap.query(l);
			else
				cout << treap.query(r);
		}
	}
	cout << "\n";
}