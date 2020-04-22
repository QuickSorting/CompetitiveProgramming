#include <bits/stdc++.h>

using namespace std;

const int kN = 1000 + 3;

class Rational_Number{
private:
    long long a, b;
    void rationalise(){
        long long gcd = __gcd(a, b);
        if(gcd){
            a /= gcd;
            b /= gcd;
        }

        if(b < 0){
            a = -a;
            b = -b;
        }
    }
public:
    Rational_Number(){}
    Rational_Number(long long a, long long b){
        this->a = a;
        this->b = b;
        rationalise();
    }

    friend bool operator<(const Rational_Number &lvalue, const Rational_Number &rvalue){
        return make_pair(lvalue.a, lvalue.b) < make_pair(rvalue.a, rvalue.b);
    }
    friend bool operator==(const Rational_Number &lvalue, const Rational_Number &rvalue){
        return make_pair(lvalue.a, lvalue.b) == make_pair(rvalue.a, rvalue.b);
    }
    friend ostream &operator<<(ostream &output, Rational_Number rational_number){ 
        output << rational_number.a << "/" << rational_number.b;
        return output;            
    }
};

struct Point{
    long long x, y;

    Point(){}
    Point(long long x, long long y){
        this->x = x;
        this->y = y;
    }

    friend bool operator==(Point a, Point b){
        return (a.x == b.x) && (a.y == b.y);
    }
};

struct Rational_Point{
    Rational_Number x, y;

    Rational_Point(){}
    Rational_Point(Rational_Number x, Rational_Number y){
        this->x = x;
        this->y = y;
    }
    Rational_Point(Point p){
        x = Rational_Number(p.x, 1);
        y = Rational_Number(p.y, 1);
    }

    friend bool operator<(const Rational_Point &lvalue, const Rational_Point &rvalue){
        if(lvalue.x == rvalue.x)
            return lvalue.y < rvalue.y;
        return lvalue.x < rvalue.x;
    }
    friend ostream &operator<<(ostream &output, Rational_Point rational_point){ 
        output << rational_point.x << " " << rational_point.y;
        return output;            
    }
};

struct Line{
    long long A, B, C;

    Line(){}
    Line(Point a, Point b){
        A = a.y - b.y;
        B = b.x - a.x;
        C = -(A * a.x + B * a.y);
    }
};

int n, k;
pair<int, int> lines[kN];
map<Rational_Point, int> idx;
set<int> points_in_line[kN];
int points_cnt = 0, lines_cnt = 0;

bool area(Point p1, Point p2, Point p3){
    long long area = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y
                    -(p1.x * p3.y + p2.x * p1.y + p3.x * p2.y);

    return (area < 0);
}

pair<bool, Rational_Point> intersect(Point p1, Point p2, Point p3, Point p4){
    if(p1 == p3 || p1 == p4 || p2 == p3 || p2 == p4)
        return make_pair(false, Rational_Point());
    if(area(p1, p2, p3) == area(p1, p2, p4))
        return make_pair(false, Rational_Point());

    Line line_1(p1, p2);
    Line line_2(p3, p4);

    long long A1 = line_1.A, B1 = line_1.B, C1 = line_1.C;
    long long A2 = line_2.A, B2 = line_2.B, C2 = line_2.C;

    long long d = A1 * B2 - A2 * B1;
    if(d == 0)
        return make_pair(false, Rational_Point());

    Rational_Point answer;
    answer.x = Rational_Number(B1 * C2 - B2 * C1, d);
    answer.y = Rational_Number(A1 * C2 - A2 * C1, -d);

    return make_pair(true, answer);
}

Point get_point(int idx){
    if(idx <= n)
        return Point(idx - 1, 0);
    if(idx <= 2 * n)
        return Point(n, idx - n - 1);
    if(idx <= 3 * n)
        return Point(3 * n + 1 - idx, n);

    assert(idx <= 4 * n);
    return Point(0, 4 * n + 1 - idx);
}

void add_endpoint_to_line(int point_idx, int line_idx){
    if(point_idx > 3 * n + 1 || 2 * n + 1 > point_idx){
        Rational_Point p(get_point(point_idx));
        if(!idx.count(p))
            idx[p] = points_cnt++; 

        points_in_line[line_idx].insert(idx[p]);
    }
}

void solve(){
    for(int i = 0; i < k; ++i){
        add_endpoint_to_line(lines[i].first, i);
        add_endpoint_to_line(lines[i].second, i);
        ++lines_cnt;
    }

    lines_cnt += points_cnt + 1;
    if(!idx.count(get_point(1))){
        ++lines_cnt;
        ++points_cnt;
    }
    if(!idx.count(get_point(n + 1))){
        ++lines_cnt;
        ++points_cnt;
    }
 
    for(int i = 0; i < k; ++i){
        for(int j = i + 1; j < k; ++j){
            Point p1 = get_point(lines[i].first);
            Point p2 = get_point(lines[i].second);
            Point p3 = get_point(lines[j].first);
            Point p4 = get_point(lines[j].second);

            pair<bool, Rational_Point> t = intersect(p1, p2, p3, p4);
            if(!t.first)
                continue;

            Rational_Point p = t.second;

            if(!idx.count(p))
                idx[p] = points_cnt++;

            if(!points_in_line[i].count(idx[p])){
                points_in_line[i].insert(idx[p]);
                ++lines_cnt;
            }
            if(!points_in_line[j].count(idx[p])){
                points_in_line[j].insert(idx[p]);
                ++lines_cnt;
            }
        }
    }

    cout << lines_cnt - points_cnt << "\n";
}

void read(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < k; ++i)
        cin >> lines[i].first >> lines[i].second;
}

int main(){
    read();
    solve();
}
/*
2 5
1 5
2 6
3 7
4 8
3 6
*/