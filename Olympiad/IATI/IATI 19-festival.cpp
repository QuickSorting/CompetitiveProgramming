#include <bits/stdc++.h>

using namespace std;

struct range{
    int l, r;
    range(){}
};

bool intersect(range lvalue, range rvalue){
    if(lvalue.l > rvalue.r || lvalue.r < rvalue.l)
        return false;
    return true;
}

const int MAXN = 1e5 + 7;
range a[MAXN][2];
int n, ans[MAXN], comp[MAXN];
vector<int> adj[MAXN], rev_adj[MAXN], order;
bool used[MAXN];
int timer = 0;

void dfs(int u){
    used[u] = true;
    for(int to: adj[u]){
        if(!used[to])
            dfs(to);
    }
    order.push_back(u);
}

void dfs_scc(int u){
    comp[u] = timer;
    for(int to: rev_adj[u]){
        if(!comp[to])
            dfs_scc(to);
    }
}

void solve(){
    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            for(int i2 = 0; i2 < 2; ++i2){
                for(int j2 = 0; j2 < 2; ++j2){
                    if(intersect(a[i][i2], a[j][j2])){
                        adj[2 * i + i2].push_back(2 * j + 1 - j2);
                        adj[2 * j + j2].push_back(2 * i + 1 - i2);

                        rev_adj[2 * j + 1 - j2].push_back(2 * i + i2);
                        rev_adj[2 * i + 1 - i2].push_back(2 * j + j2);
                    }
                }
            }
        }
    }

    for(int i = 0; i < 2 * n; ++i){
        if(!used[i])
            dfs(i);
    }

    reverse(order.begin(), order.end());
    for(int u: order){
        if(!comp[u]){
            timer++;
            dfs_scc(u);
        }
    }

    for(int i = 0; i < n; ++i){
        if(comp[2 * i] == comp[2 * i + 1]){
            cout << "NO\n";
            return;
        }
        ans[i] = (comp[2 * i] < comp[2 * i + 1]) + 1;
    }

    cout << "YES\n";
    for(int i = 0; i < n; ++i){
        cout << ans[i] << " ";
    }
    cout << "\n";
}

void read(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> a[i][0].l >> a[i][0].r;
        cin >> a[i][1].l >> a[i][1].r;
    }
}

int main(){
    read();
    solve();
}