#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2007;

class Number{
private:
	bool digits[MAXN];
	int size;
public:
	Number(){
		size = 0;
	}
	inline int Size()const{
		return size;
	}
	void FromString(string s){
		reverse(s.begin(), s.end());
		size = (int)s.size();

		for(int i = 0; i < size; ++i)
			digits[i] = s[i] - '0';
	}
	bool operator[](const int &idx)const{
		return digits[idx];
	}
	bool& operator[](const int &idx){
		return digits[idx];
	}
	void AddOne(int idx, Number &lhs){
		while(digits[idx]){
			lhs[idx] ^= 1;
			digits[idx++] = 0; 
		}
		lhs[idx] ^= 1;
		digits[idx] = 1;
	}
	void SubtractOne(int idx, Number &lhs){
		while(!digits[idx]){
			lhs[idx] ^= 1;
			digits[idx++] = 1; 
		}
		lhs[idx] ^= 1;
		digits[idx] = 0;
	}
	/*void AddNumber(int idx, int n){
		while(n){
			n += digits[idx];
			digits[idx++] = (n & 1);
			n >>= 1;
		}
	}*/
	friend bool operator==(const Number &lvalue, const Number &rvalue){
		for(int i = 0; i < MAXN; ++i){
			if(lvalue[i] != rvalue[i])
				return false;
		}
		return true;
	}
};

Number Xor(const Number &lvalue, const Number &rvalue){
	Number ret;

	for(int i = 0; i < MAXN; ++i){
		int add = 0;
		add ^= lvalue[i];
		add ^= rvalue[i];

		ret[i] = add;
	}

	return ret;
}

int n;
Number a[MAXN], b, lhs;

bool Recurse(int idx, Number &num){
	if(lhs == b)
		return true;
	if(idx > 2000){
		return false;
	}

	if(n & 1){
		if(lhs[idx] != b[idx]){
			num[idx] = 1;
			for(int i = 0; i < n; ++i)
				a[i].AddOne(idx, lhs);
		}
		else
			num[idx] = 0;
		return Recurse(idx + 1, num);
	}
	
	if(lhs[idx] != b[idx])
		return false;

	if(lhs[idx + 1] != b[idx + 1]){
		if(lhs[idx] & 1){
			num[idx] = 1;
			for(int i = 0; i < n; ++i)
				a[i].AddOne(idx, lhs);
		}
		else
			return false;
	}
	else{
		if(lhs[idx] & 1)
			num[idx] = 0;
		else{
			num[idx] = 1;
			for(int i = 0; i < n; ++i)
				a[i].AddOne(idx, lhs);

			if(!Recurse(idx + 1, num)){
				if(num[idx]){
					num[idx] = 0;
					for(int i = 0; i < n; ++i)
						a[i].SubtractOne(idx, lhs);
				}
				
				return Recurse(idx + 1, num);
			}
			return true;
		}
	}

	if(!Recurse(idx + 1, num)){
		if(num[idx]){
			num[idx] = 0;
			for(int i = 0; i < n; ++i)
				a[i].SubtractOne(idx, lhs);
		}
		return false;
	}
	return true;
}

Number ans;

void Solve(){
	lhs.FromString("0");
	for(int i = 0; i < n; ++i)
		lhs = Xor(lhs, a[i]);

	bool ok = Recurse(0, ans);
	if(!ok){
		cout << "-1\n";
		return;
	}

	int first = -1;
	for(int i = MAXN - 1; i >= 0; --i){
		if(ans[i]){
			first = i;
			break;
		}
	}

	if(first == -1){
		cout << "0\n";
		return;
	}
	for(int i = first; i >= 0; --i)
		cout << ans[i];
	cout << "\n";
}

void Read(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	string s;
	cin >> n;
	for(int i = 0; i < n; ++i){
		cin >> s;
		a[i].FromString(s);
	}
	cin >> s;
	b.FromString(s);
}

int main(){
	Read();
	Solve();
}