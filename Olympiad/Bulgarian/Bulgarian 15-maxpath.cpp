#include <bits/stdc++.h>

using namespace std;

const int kN = 1e4 + 3;

int n, b, p;

inline int get_cost(long long x, long long y) {
    return ((x*b) ^ ((y+1)*b)) % p;
}

inline long long max(long long a, long long b){
    return (a > b ? a : b);
}

long long arr[3][kN];
long long *row[3];

void divide_and_conquer(int l_row, int r_row, int l_column, int r_column){
    if(l_row == r_row){
        for(int y = l_column; y <= r_column; ++y)
            cout << l_row << " " << y << "\n";
        return;
    }

    int mid_row = (l_row + r_row) >> 1;

    for(int y = l_column; y <= r_column; ++y)
        row[0][y] = 0;
    for(int x = l_row; x <= mid_row; ++x){
        row[1][l_column - 1] = 0;

        for(int y = l_column; y <= r_column; ++y)
            row[1][y] = max(row[0][y], row[1][y - 1]) + get_cost(x, y);

        swap(row[1], row[0]);
    }

    swap(row[2], row[0]);

    for(int y = l_column; y <= r_column; ++y)
        row[0][y] = 0;
    for(int x = r_row; x >= mid_row + 1; --x){ 
        row[1][r_column + 1] = 0;

        for(int y = r_column; y >= l_column; --y)
            row[1][y] = max(row[0][y], row[1][y + 1]) + get_cost(x, y);

        swap(row[1], row[0]);
    }

    int max_val_idx = l_column;
    for(int y = l_column; y <= r_column; ++y){
        row[2][y] += row[0][y];

        if(row[2][max_val_idx] < row[2][y])
            max_val_idx = y;
    }

    if(l_row == 1 && r_row == n && l_column == 1 && r_column == n)
        cout << row[2][max_val_idx] << "\n";

    divide_and_conquer(l_row, mid_row, l_column, max_val_idx);
    divide_and_conquer(mid_row + 1, r_row, max_val_idx, r_column);
}

void solve(){
    divide_and_conquer(1, n, 1, n);
}

void read(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> b >> p;
}

int main(){
    for(int i = 0; i < 3; ++i)
        row[i] = arr[i];
    read();
    solve();
}