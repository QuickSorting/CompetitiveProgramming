#include <bits/stdc++.h>

using namespace std;

struct Point{
	int x, y;

	Point(){}
	Point(int x, int y){
		this->x = x;
		this->y = y;
	}

	friend bool operator<(Point lvalue, Point rvalue){
		if(lvalue.x == rvalue.x)
			return lvalue.y < rvalue.y;
		return lvalue.x < rvalue.x;
	}

	friend bool operator>(Point lvalue, Point rvalue){
		if(lvalue.x == rvalue.x)
			return lvalue.y > rvalue.y;
		return lvalue.x > rvalue.x;
	}
};

bool same_direction(int a, int b, int c){
	if(a > b && b > c)
		return true;
	if(a < b && b < c)
		return true;

	return false;
}


void find_next_idx(const vector<Point> &points, 
                   const vector<bool> &used, 
                   const int &n, 
                   const Point &curr, 
                   const int &curr_idx, 
                   const Point &prev, 
                   bool &ok, 
                   int &next_idx){
	ok = true;

	if(curr.x == prev.x){
		int down_idx = curr_idx, up_idx = curr_idx;
		int down_cnt = 0, up_cnt = 0;
		for(int i = 0; i < n; ++i){
			if(used[i])
				continue;
			Point point = points[i];

			if(same_direction(prev.y, curr.y, point.y)){
				if(point.x < curr.x){
					if(down_idx == curr_idx || point.x > points[down_idx].x)
						down_idx = i;
					++down_cnt;
				}
				else{
					if(up_idx == curr_idx || point.x < points[up_idx].x)
						up_idx = i;
					++up_cnt;
				}
			}
		}

		if(!down_cnt && !up_cnt){
			for(int i = 0; i < n; ++i){
				if(!used[i]){
					next_idx = i;
					ok = false;
					break;
				}
			}
		}
		else{
			if(down_cnt > up_cnt)
				next_idx = down_idx;
			else
				next_idx = up_idx;
		}
	}
	else if(curr.y == prev.y){
		int down_idx = curr_idx, up_idx = curr_idx;
		int down_cnt = 0, up_cnt = 0;
		for(int i = 0; i < n; ++i){
			if(used[i])
				continue;
			Point point = points[i];

			if(same_direction(prev.x, curr.x, point.x)){
				if(point.y < curr.y){
					if(down_idx == curr_idx || point.y > points[down_idx].y)
						down_idx = i;
					++down_cnt;
				}
				else{
					if(up_idx == curr_idx || point.y < points[up_idx].y)
						up_idx = i;
					++up_cnt;
				}
			}
		}

		if(!down_cnt && !up_cnt){
			for(int i = 0; i < n; ++i){
				if(!used[i]){
					next_idx = i;
					ok = false;
					break;
				}
			}
		}
		else{
			if(down_cnt > up_cnt)
				next_idx = down_idx;
			else
				next_idx = up_idx;
		}
	}
}

vector<Point> greedy(const int &n, const vector<Point> &points){
	vector<bool> used(n, false);

	vector<Point> ret;
	Point curr = points[0], prev(points[0].x, 0);
	int curr_idx = 0;
	ret.push_back(prev);

	used[0] = true;

	for(int i = 1; i < n; ++i){
		int next_idx;
		bool ok;

		find_next_idx(points, used, n, curr, curr_idx, prev, ok, next_idx);

		used[next_idx] = true;
		Point nxt = points[next_idx];

		if(ok){
			if(curr.x == prev.x)
				prev = Point(curr.x, nxt.y);
			else
				prev = Point(nxt.x, curr.y);
		}
		else{
			ret.push_back(curr);
			if(curr.x == prev.x)
				prev = Point(nxt.x, curr.y);
			else
				prev = Point(curr.x, nxt.y);
		}
		ret.push_back(prev);
		curr = nxt;
		curr_idx = next_idx;
	}
	ret.push_back(curr);

	return ret;
}

vector<Point> solve(int &n, vector<Point> &points){
	sort(points.begin(), points.end());
	return greedy(n, points);
}

void read(int &n, vector<Point> &points){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for(int i = 0; i < n; ++i){
		points.push_back(Point());
		cin >> points[i].x >> points[i].y;
	}
}

void write(const vector<Point> &ans){
	cout << (int)ans.size() << "\n";
	for(Point point: ans){
		cout << point.x << " " << point.y << "\n";
	}
}

int main(){
	int n;
	vector<Point> points, ans;

	read(n, points);
	ans = solve(n, points);
	write(ans);
}
