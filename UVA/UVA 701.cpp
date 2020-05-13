#include <bits/stdc++.h>

using namespace std;

template<size_t t_Size, size_t t_Log_Size>
struct Suffix_Array{
    int c[t_Log_Size][t_Size], cnt[t_Size];
    int p[t_Size], pn[t_Size];
    int n, log_n;

    Suffix_Array(){}
    void initialise(const vector<int> &s){
        n = s.size();
        log_n = 0;

        fill(cnt, cnt + t_Size, 0);

        for(int i = 0; i < n; ++i)
            cnt[s[i]]++;
        for(int i = 1; i < t_Size; ++i)
            cnt[i] += cnt[i - 1];
        for(int i = n - 1; i >= 0; --i)
            p[--cnt[s[i]]] = i;

        c[0][p[0]] = 0;

        int classes = 1;
        for(int i = 1; i < n; ++i){
            if (s[p[i]] != s[p[i - 1]])
                classes++;
            c[0][p[i]] = classes - 1;
        }

        for(int step = 1, h = 1; h < n; h <<= 1, ++step){
            log_n = step;

            for(int i = 0; i < n; i++){
                pn[i] = p[i] - h;
                if(pn[i] < 0)
                    pn[i] += n;
            }

            fill(cnt, cnt + classes, 0);

            for(int i = 0; i < n; ++i)
                cnt[c[step - 1][pn[i]]]++;
            for(int i = 1; i < classes; ++i)
                cnt[i] += cnt[i - 1];
            for(int i = n - 1; i >= 0; --i)
                p[--cnt[c[step - 1][pn[i]]]] = pn[i];

            c[step][p[0]] = 0;
            classes = 1;

            for(int i = 1; i < n; i++){
                pair<int, int> curr = {c[step - 1][p[i]], c[step - 1][(p[i] + h) % n]};
                pair<int, int> prev = {c[step - 1][p[i - 1]], c[step - 1][(p[i - 1] + h) % n]};
                if (curr != prev)
                    ++classes;
                c[step][p[i]] = classes - 1;
            }
        }
    }

    int& operator[](int index){
        return p[index];
    }

    int compare(int i, int j, int l, int k){
        pair<int, int> a = {c[k][i], c[k][(i + l - (1 << k)) % n]};
        pair<int, int> b = {c[k][j], c[k][(j + l - (1 << k)) % n]};

        return a == b ? 0 : a < b ? -1 : 1;
    }

    int lcp(int i, int j) {
        i = p[i];
        j = p[j];

        int ans = 0;
        for(int k = log_n; k >= 0; k--){
            if(c[k][i] == c[k][j]){
                ans += 1 << k;
                i += 1 << k;
                j += 1 << k;
            }
        }
        return ans;
    }
};

const int k_N = 600 + 7;
const int k_Log_N = 10;

Suffix_Array<k_N, k_Log_N> suffix_array;

bool are_in_different_strings(int i, int j, const string &s, const string &t){
    i = suffix_array[i];
    j = suffix_array[j];

    if(i <= (int)s.size() - 1)
        return ((int)s.size() + 1 <= j && j <= (int)s.size() + (int)t.size());
    if((int)s.size() + 1 <= i && i <= (int)s.size() + (int)t.size())
        return j <= (int)s.size() - 1;
    return false;
}

void solve_test(const string &s, const string &t){
    vector<int> v;
    for(char c: s)
        v.push_back(c);
    v.push_back(0);
    for(char c: t)
        v.push_back(c);
    v.push_back(1);

    suffix_array.initialise(v);

    int length_of_longest_common_sequence = 0;
    for(int i = 0; i < (int)v.size() - 1; ++i){
        if(!are_in_different_strings(i, i + 1, s, t))
            continue;

        length_of_longest_common_sequence = max(suffix_array.lcp(i, i + 1), length_of_longest_common_sequence);
    }

    if(length_of_longest_common_sequence == 0){
        cout << "No common sequence.\n";
        return;
    }

    int previous = -1;
    vector<string> answer;
    for(int i = 0; i < (int)v.size() - 1; ++i){
        if(!are_in_different_strings(i, i + 1, s, t))
            continue;

        if(suffix_array.lcp(i, i + 1) == length_of_longest_common_sequence && (previous == -1 || suffix_array.lcp(previous, i) != length_of_longest_common_sequence)){
            previous = i;
            if(suffix_array[i] <= (int)s.size() - 1)
                answer.push_back(s.substr(suffix_array[i], length_of_longest_common_sequence));
            else
                answer.push_back(s.substr(suffix_array[i + 1], length_of_longest_common_sequence));
        }
    }

    for(const string &longest_string: answer)
        cout << longest_string << "\n";
}

int main(){
    string s, t;

    bool previous = false;
    while(cin >> s >> t){
        if(previous)
            cout << "\n";
        previous = true;

        solve_test(s, t);
    }
}