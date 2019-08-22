#include "rect.h"
#include <bits/stdc++.h>

using namespace  std;

const int MAXN = 2507;
const int inf = 1e9;

inline int fast_min(int lvalue, int rvalue){
	return ((lvalue < rvalue) ? lvalue : rvalue);
}

inline int fast_max(int lvalue, int rvalue){
	return ((lvalue > rvalue) ? lvalue : rvalue);
}

struct b_str{
	int l, r, u, d;

	b_str(){}
};


b_str b[MAXN][MAXN];

struct segment_tree{
	int mn[2 * MAXN];
	char type;
	int val;
	int sz;

	segment_tree(){}

	void init(char type, int val, int sz){
		this->type = type;
		this->val = val;
		this->sz = sz;
		
		for(int i = 0; i < sz; ++i){
			int idx = i + sz;

			switch(type){
			case 'l':
				mn[idx] = b[i][val].l;
				break;
			case 'r':
				mn[idx] = b[i][val].r;
				break;
			case 'u':
				mn[idx] = b[val][i].u;
				break;
			case 'd':
				mn[idx] = b[val][i].d;
				break;
			}
		}
		for(int i = sz - 1; i > 0; --i){
			mn[i] = fast_min(mn[i << 1], mn[(i << 1) | 1]);
		}
	}

	int query(int l, int r){
		++r;

		int resl = inf, resr = inf;

		for(l += sz, r += sz; l < r; l >>= 1, r >>= 1){
            if(l & 1){
            	resl = fast_min(resl, mn[l++]);
            }
            if(r & 1){
            	resr = fast_min(mn[--r], resr);
            }
        }

        return fast_min(resl, resr);
	}
};

struct rect{
	int x1, y1, x2, y2;

	rect(){}

	friend bool operator<(rect lvalue, rect rvalue){
		if(lvalue.x1 != rvalue.x1){
			return lvalue.x1 < rvalue.x1;
		}
		if(lvalue.x2 != rvalue.x2){
			return lvalue.x2 < rvalue.x2;
		}
		if(lvalue.y1 != rvalue.y1){
			return lvalue.y1 < rvalue.y1;
		}

		return lvalue.y2 < rvalue.y2;
	}
};

rect v[MAXN * MAXN];
segment_tree st_l[MAXN], st_r[MAXN], st_u[MAXN], st_d[MAXN];
int a[MAXN][MAXN], n, m;

bool check(int x1, int y1, int x2, int y2){
	//cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;

	int lvalue = st_l[y2 + 1].query(x1, x2);
	int rvalue = st_r[y1 - 1].query(x1, x2);
	int uvalue = st_u[x2 + 1].query(y1, y2);
	int dvalue = st_d[x1 - 1].query(y1, y2);

	if(fast_min(lvalue, rvalue) < y2 - y1 + 2){
		return false;
	}
	if(fast_min(uvalue, dvalue) < x2 - x1 + 2){
		return false;
	}

	return true;
}

stack<int> st;

long long count_rectangles(vector<vector<int> > _a) {
	n = _a.size();
	m = _a[0].size();

	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			a[i][j] = _a[i][j];
		}
	}

	for(int i = 0; i < n; ++i){
		st.push(0);
		for(int j = 1; j < m; ++j){
			while(!st.empty() && a[i][j] >= a[i][st.top()]){
				b[i][st.top()].r = j - st.top();
				st.pop();
			}
			st.push(j);
		}
		while(!st.empty()){
			b[i][st.top()].r = m - st.top();
			st.pop();
		}
	}

	for(int i = 0; i < n; ++i){
		st.push(m - 1);
		for(int j = m - 2 ; j >= 0; --j){
			while(!st.empty() && a[i][j] >= a[i][st.top()]){
				b[i][st.top()].l = st.top() - j;
				st.pop();
			}
			st.push(j);
		}
		while(!st.empty()){
			b[i][st.top()].l = st.top() + 1;
			st.pop();
		}
	}

	for(int i = 0; i < m; ++i){
		st.push(0);
		for(int j = 1; j < n; ++j){
			while(!st.empty() && a[j][i] >= a[st.top()][i]){
				b[st.top()][i].d = j - st.top();
				st.pop();
			}
			st.push(j);
		}
		while(!st.empty()){
			b[st.top()][i].d = n - st.top();
			st.pop();
		}
	}

	for(int i = 0; i < m; ++i){
		st.push(n - 1);
		for(int j = n - 2; j >= 0; --j){
			while(!st.empty() && a[j][i] >= a[st.top()][i]){
				b[st.top()][i].u = st.top() - j;
				st.pop();
			}
			st.push(j);
		}
		while(!st.empty()){
			b[st.top()][i].u = st.top() + 1;
			st.pop();
		}
	}

	for(int i = 0; i < n; ++i){
		st_u[i].init('u', i, m);
		st_d[i].init('d', i, m);
	}
	for(int i = 0; i < m; ++i){
		st_l[i].init('l', i, n);
		st_r[i].init('r', i, n);
	}

	for(int i = 0; i < n; ++i){
		st.push(0);
		for(int j = 1; j < m; ++j){
			while(!st.empty() && a[i][j] > a[i][st.top()]){
				b[i][st.top()].r = j - st.top();
				st.pop();
			}
			st.push(j);
		}
		while(!st.empty()){
			b[i][st.top()].r = m - st.top();
			st.pop();
		}
	}

	for(int i = 0; i < n; ++i){
		st.push(m - 1);
		for(int j = m - 2 ; j >= 0; --j){
			while(!st.empty() && a[i][j] > a[i][st.top()]){
				b[i][st.top()].l = st.top() - j;
				st.pop();
			}
			st.push(j);
		}
		while(!st.empty()){
			b[i][st.top()].l = st.top() + 1;
			st.pop();
		}
	}

	for(int i = 0; i < m; ++i){
		st.push(0);
		for(int j = 1; j < n; ++j){
			while(!st.empty() && a[j][i] > a[st.top()][i]){
				b[st.top()][i].d = j - st.top();
				st.pop();
			}
			st.push(j);
		}
		while(!st.empty()){
			b[st.top()][i].d = n - st.top();
			st.pop();
		}
	}

	for(int i = 0; i < m; ++i){
		st.push(n - 1);
		for(int j = n - 2; j >= 0; --j){
			while(!st.empty() && a[j][i] > a[st.top()][i]){
				b[st.top()][i].u = st.top() - j;
				st.pop();
			}
			st.push(j);
		}
		while(!st.empty()){
			b[st.top()][i].u = st.top() + 1;
			st.pop();
		}
	}

	long long ans = 0;
	int cnt = 0;

	for(int i = 1; i < n - 1; ++i){
		for(int j = 1; j < m - 1; ++j){
			rect r;

			r.x1 = fast_min(n - 2, fast_max(1, i - b[i][j].u + 1));
			r.x2 = fast_min(n - 2, fast_max(1, i + b[i][j].d - 1));
			r.y1 = fast_min(m - 2, fast_max(1, j - b[i][j].l + 1));
			r.y2 = fast_min(m - 2, fast_max(1, j + b[i][j].r - 1));

			//cout << i << " " << j << " - " << r.x1 << " " << r.y1 << " " << r.x2 << " " << r.y2 << endl;

			v[cnt++] = r;
		}
	}

	sort(v, v + cnt);

	for(int i = 0; i < cnt; ++i){
		if(i != 0 && v[i - 1].x1 == v[i].x1 && v[i - 1].y1 == v[i].y1 && v[i - 1].x2 == v[i].x2 && v[i - 1].y2 == v[i].y2){
			continue;
		}
		ans += check(v[i].x1, v[i].y1, v[i].x2, v[i].y2);
	}

	return ans;
}
/*
6 5
4 8 7 5 6
7 4 10 3 5
9 7 20 14 2
9 14 7 3 6
5 7 5 2 7
4 5 13 5 6
*/
