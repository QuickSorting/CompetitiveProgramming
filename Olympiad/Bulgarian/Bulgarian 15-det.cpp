#include <bits/stdc++.h>

using namespace std;

struct Detail{
    int a, b;

    Detail(){}
};

const int kN = 3e5 + 7;

int n;
Detail p[kN];
priority_queue<int> a;

struct Compare{
    bool operator()(const Detail &lvalue, const Detail &rvalue){
        return lvalue.a + lvalue.b > rvalue.a + rvalue.b;
    }
};

void solve(){
    sort(p, p + n, Compare());

    long long sum = 0;
    int answer = 0;
    for(int i = n - 1; i >= 0; --i){
        if(p[i].b >= sum){
            sum += p[i].a;
            ++answer;
            a.push(p[i].a);
        }
        else{
            if(a.top() >= p[i].a && p[i].b >= sum - a.top()){
                sum -= a.top();
                a.pop();
                sum += p[i].a;
                a.push(p[i].a);
            }
        }
    }

    cout << answer << "\n";
}

void read(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> p[i].a >> p[i].b;
}

int main(){
    read();
    solve();
}