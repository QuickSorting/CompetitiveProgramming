#include <bits/stdc++.h>

using namespace std;

const int k_N = 1e5;
const int k_Q = 1e5;
const int k_K = 5;
const long double k_Infinity = 1e18;

const int k_Invalid = -1;

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

struct TreeNode{
    int left_node, right_node;
    Array<int, k_K> left_point, right_point;

    TreeNode(){
        left_node = right_node = k_Invalid;
    }
};

class Tree{
private:
    TreeNode nodes[4 * k_N];
    int sz;
public:
    Tree(){
        sz = 0;
    }

    int get_next_node_idx(){
        return sz++;
    }

    TreeNode& operator[](int idx){
       return nodes[idx];
    }
};


Array<int, k_K> points[k_N], query_points[k_N];
int n, k;
int q;

Tree tree;

long double get_distance(const Array<int, k_K> &a, const Array<int, k_K> &b){
    long double answer = 0;

    for(int i = 0; i < k; ++i)
        answer += ((long long)a[i] - b[i]) * ((long long)a[i] - b[i]);
    answer = max(answer, (long double)0.0);
    answer = sqrt(answer);

    return answer;
}

void get_answer_for_query(const Array<int, k_K> &query_point, int node, int dimension, long double &answer){
    if(tree[node].left_node == k_Invalid && tree[node].right_node == k_Invalid){
        answer = min(answer, get_distance(tree[node].left_point, query_point));
        return;
    }

    int next_dimension = (dimension + 1) % k;

    Array<int, k_K> &left_point = tree[node].left_point;
    Array<int, k_K> &right_point = tree[node].right_point;
    int left_node = tree[node].left_node;
    int right_node = tree[node].right_node;

    if(query_point[dimension] <= left_point[dimension]){
        get_answer_for_query(query_point, left_node, next_dimension, answer);

        if(right_point[dimension] - query_point[dimension] <= answer)
            get_answer_for_query(query_point, right_node, next_dimension, answer);
    }
    else{
        get_answer_for_query(query_point, right_node, next_dimension, answer);

        if(query_point[dimension] - left_point[dimension] <= answer)
            get_answer_for_query(query_point, left_node, next_dimension, answer);
    }
}

void answer_queries(){
    for(int i = 0; i < q; ++i){
        long double answer = k_Infinity;
        get_answer_for_query(query_points[i], 0, 0, answer);
        cout << fixed << setprecision(3) << answer << "\n";
    }
}

struct Cmp{
    Cmp(int dimension){this->dimension = dimension;}
    int dimension;
    bool operator()(const Array<int, k_K> &lvalue, const Array<int, k_K> &rvalue){
        return lvalue[dimension] < rvalue[dimension];
    }
};

void dfs(int node, int l, int r, int dimension = 0){
    if(l == r){
        tree[node].left_point = tree[node].right_point = points[l];
        return;
    }

    sort(points + l, points + r + 1, Cmp(dimension));

    int next_dimension = (dimension + 1) % k;
    int mid = l + ((r - l) >> 1);

    tree[node].left_point = points[mid];
    tree[node].right_point = points[mid + 1];

    tree[node].left_node = tree.get_next_node_idx();
    dfs(tree[node].left_node, l, mid, next_dimension);

    tree[node].right_node = tree.get_next_node_idx();
    dfs(tree[node].right_node, mid + 1, r, next_dimension);
}

void preprocess(){
    dfs(tree.get_next_node_idx(), 0, n - 1);
}

void solve(){
    preprocess();
    answer_queries();
}

void read(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < k; ++j)
            cin >> points[i][j];

    cin >> q;

    for(int i = 0; i < q; ++i)
        for(int j = 0; j < k; ++j)
            cin >> query_points[i][j];
}

int main(){
    read();
    solve();
}