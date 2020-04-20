#include <bits/stdc++.h>

using namespace std;

const int kN = 200 + 3;
const int kInf = 1e9;

template<class T, size_t n>
class Array{
private:
    T arr[n];
public:
    Array(){}

    T& operator[](int idx){
        return arr[idx];
    }

    T operator[](int idx)const{
        return arr[idx];
    }
};

int n;
int c[kN][kN];

int calculate_cost(const Array<int, kN> &row_add, const Array<int, kN> &column_add){
    int cost = 0;
    for(int i = 0; i < n; ++i)
        cost += row_add[i] + column_add[i];
    return cost;
}

void output_answer(const Array<int, kN> &row_add, const Array<int, kN> &column_add){
    int cost = calculate_cost(row_add, column_add);
    cout << cost << "\n";

    for(int x = 0; x < n; ++x)
        cout << row_add[x] << " ";
    cout << "\n";

    for(int y = 0; y < n; ++y)
        cout << column_add[y] << " ";
    cout << "\n";
}

void build_initial_add(Array<int, kN> &row_add, Array<int, kN> &column_add){
    for(int x = 0; x < n; ++x)
        row_add[x] = 0;
    for(int y = 0; y < n; ++y){
        column_add[y] = 0;
        for(int x = 0; x < n; ++x)
            column_add[y] = max(c[x][y], column_add[y]);
    }
}

bool improve(Array<int, kN> &row_add, Array<int, kN> &column_add, int row_index){
    int possible_improvement = 0;
    for(int y = 0; y < n; ++y){
        if(c[row_index][y] - row_add[row_index] != column_add[y])
            continue;

        int difference = c[row_index][y] - row_add[row_index];
        for(int x = 0; x < n; ++x){
            if(x == row_index)
                continue;
  
            difference = min(column_add[y] - (c[x][y] - row_add[x]), difference);
        }

        possible_improvement = max(difference, possible_improvement);
    }

    if(!possible_improvement)
        return false;

    row_add[row_index] += possible_improvement;
    for(int y = 0; y < n; ++y){
        if(c[row_index][y] - (row_add[row_index] - possible_improvement) != column_add[y])
            continue;

        column_add[y] = 0;
        for(int x = 0; x < n; ++x)
            column_add[y] = max(c[x][y] - row_add[x], column_add[y]);
    }

    return true;
}

void solve(){
    if(n == 1){
        assert(false);
        cout << c[0][0] << "\n";
        cout << c[0][0] << "\n";
        cout << 0 << "\n";
        return;
    }

    static Array<int, kN> row_add, column_add;

    build_initial_add(row_add, column_add);
    
    for(int i = 0; i < 100; ++i)
        for(int x = 0; x < n; ++x)
            improve(row_add, column_add, x);

    output_answer(row_add, column_add);
}

void read(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    for(int x = 0; x < n; ++x)
        for(int y = 0; y < n; ++y)
            cin >> c[x][y];
}

int main(){
    read();
    solve();
}