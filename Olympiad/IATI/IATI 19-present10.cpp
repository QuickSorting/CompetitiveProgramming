#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, n2;

    cin >> n;

    n -= 1;

    if(n & 1)
        n2 = min(n, 61ll);
    else
        n2 = min(n, 62ll);
	int pr = n2;

    unsigned long long x = 0, ans = 0;
    x += (n - n2) / 2ull;
    ans += (n - n2) / 2ull;
    while(n2 >= 0){
        x += (1ull << n2);
        n2 -= 2;
    }

	n = pr;

    for(int i = n; i >= 1; --i){
        unsigned long long curr = (1ull << i) - 1ull;
        if(x >= curr){
            x -= curr;
            ++ans;
        }
    }

    if(!x){
        cout << ans << "\n";
    }
    else{
        cout << "0\n";
    }

    return 0;
}