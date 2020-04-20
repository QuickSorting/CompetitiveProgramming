#include <bits/stdc++.h>

using namespace std;

const int kN = 1e5 + 7;

struct Boat{
    long long sx, sy, vx, vy;
    int left_idx, right_idx;

    Boat(){}
};

struct Event{
    long double time;
    int left_idx, mid_idx, right_idx;

    Event(){}
    Event(long double time, int left_idx, int mid_idx, int right_idx){
        this->time = time;
        this->left_idx = left_idx;
        this->mid_idx = mid_idx;
        this->right_idx = right_idx;
    }

    friend bool operator<(const Event &lvalue, const Event &rvalue){
        return lvalue.time > rvalue.time;
    }
};

int n, boats_left;
Boat boats[kN];
bool removed[kN];
long double removed_time[kN];
priority_queue<Event> events;

void output_answer(){
    for(int i = 0; i < n; ++i)
        cout << fixed << setprecision(10) << removed_time[i] << "\n";
}

long double find_time_of_event(int idx){
    long double t[3] = {0, 0, 0};
    Boat triangle[3] = {boats[boats[idx].left_idx], boats[idx], boats[boats[idx].right_idx]};

    for(int i = 0; i < 3; ++i){
        int next_idx = (i + 1) % 3;

        t[2] += triangle[i].vx * triangle[next_idx].vy;
        t[1] += triangle[i].vx * triangle[next_idx].sy + triangle[i].sx * triangle[next_idx].vy;
        t[0] += triangle[i].sx * triangle[next_idx].sy;
    }

    for(int i = 0; i < 3; ++i){
        int next_idx = (i + 2) % 3;

        t[2] -= triangle[i].vx * triangle[next_idx].vy;
        t[1] -= triangle[i].vx * triangle[next_idx].sy + triangle[i].sx * triangle[next_idx].vy;
        t[0] -= triangle[i].sx * triangle[next_idx].sy;
    }

    //cout << idx << " " << t[2] << " " << t[1] << " " << t[0] << " idx t^2 t 1" << endl;

    if(round(t[2]) == 0){
        if(round(t[1]) == 0){
            if(round(t[0]) != 0)
                return -100;

            return 0;
        }

        long double x = -t[0] / t[1];
        if(x >= 0)
            return x;
        return -100;
    }

    long double d = t[1] * t[1] - 4ll * t[0] * t[2];
    if(d < 0)
        return -100;

    d = sqrt(d);

    long double x1 = (-t[1] - d) / (long double)2 / t[2];
    long double x2 = (-t[1] + d) / (long double)2 / t[2];

    if(x1 >= 0)
        return x1;
    if(x2 >= 0)
        return x2;

    return -100;
}

void add_event(int idx){
    long double time = find_time_of_event(idx);
    //cout << time << " time" << endl;;
    if(time < -1)
        return;

    events.push(Event(time, boats[idx].left_idx, idx, boats[idx].right_idx));
}

void solve(){
    boats_left = n;
    for(int i = 0; i < n; ++i)
        removed_time[i] = -1;

    for(int i = 0; i < n; ++i)
        add_event(i);

    while(boats_left > 2 && !events.empty()){
        Event event = events.top();
        events.pop();

        if(removed[event.left_idx] || removed[event.mid_idx] || removed[event.right_idx])
            continue;

        --boats_left;
        removed[event.mid_idx] = true;
        removed_time[event.mid_idx] = event.time;

        boats[event.left_idx].right_idx = event.right_idx;
        boats[event.right_idx].left_idx = event.left_idx;

        if(boats_left > 2){
            add_event(event.left_idx);
            add_event(event.right_idx);
        }
    }

    output_answer();
}

void read(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> boats[i].sx >> boats[i].sy >> boats[i].vx >> boats[i].vy;
        boats[i].left_idx = (i + n - 1) % n;
        boats[i].right_idx = (i + 1) % n;
    }
}

int main(){
    read();
    solve();
}