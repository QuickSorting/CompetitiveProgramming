/*
	-Used an implicit treap
*/
#include <bits/stdc++.h>

using namespace std;

mt19937 rng(667);
class ImplictTreap{
private:
	struct Node;
	typedef Node* pNode;

	struct Node{
		int prior, val, l_val, r_val, cnt, ans;
		pNode l, r;

		Node(){}
		Node(int val){
			prior = rng();
			this->val = val;
			l_val = r_val = val;
			l = r = nullptr;
			cnt = 1;
			ans = 1;
		}
	};

	int cnt(pNode t){
		return t ? t->cnt : 0;
	}

	void upd_cnt(pNode t){
		if(t){
			t->cnt = cnt(t->l) + cnt(t->r) + 1;
			if(t->l)
				t->l_val = t->l->l_val;
			else
				t->l_val = t->val;

			if(t->r)
				t->r_val = t->r->r_val;
			else
				t->r_val = t->val;

			t->ans = 1;
			if(t->l)
				t->ans += t->l->ans - (t->val == t->l->r_val);
			if(t->r)
				t->ans += t->r->ans - (t->val == t->r->l_val);
		}
	}

	void push(pNode t){
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

		int curr_key = cnt(t->l) + add;
		if(key <= curr_key)
			split(t->l, l, t->l, key, add), r = t;
		else
			split(t->r, t->r, r, key, add + cnt(t->l) + 1), l = t;

		upd_cnt(t);
	}
public:
	pNode root;

	ImplictTreap(){
		root = nullptr;
	}

	void insert(int pos, int val){
		if(!root){
			root = new Node(val);
			return;
		}

		pNode new_node = new Node(val);
		pNode t1, t2, t3;
		split(root, t1, t2, pos);
		merge(t1, t1, new_node);
		merge(root, t1, t2);
	}

	void erase(int pos){
		pNode t1, t2, t3;
		split(root, t1, t2, pos);
		split(t2, t2, t3, 1);

		merge(root, t1, t3);
	}

	void replace(int pos, int val){
		erase(pos);
		insert(pos, val);
	}

	int get_ans(){
		if(!root)
			return 0;
		return root->ans;
	}
};

const int kN = 1e5 + 7;

int n, a[kN], t;
ImplictTreap treap;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> a[i];

	for(int i = 0; i < n; ++i)
		treap.insert(i, a[i]);

	cin >> t;
	while(t--){
		int type;
		cin >> type;

		if(type == 1){
			int k;
			cin >> k;
			--k;

			treap.erase(k);
		}
		else if(type == 2){
			int p, c;
			cin >> p >> c;
			--p;

			treap.insert(p, c);
		}
		else if(type == 3){
			int q, c;
			cin >> q >> c;
			--q;

			treap.replace(q, c);
		}
		else if(type == 4){
			cout << treap.get_ans() << "\n";
		}
	}
}