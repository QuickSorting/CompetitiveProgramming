#include "coprobber.h"
#include <bits/stdc++.h>

using namespace std;

struct Node{
	int x, y;
	bool turn;

	Node(){}
	Node(int x, int y, bool turn){
		this -> x = x;
		this -> y = y;
		this -> turn = turn;
	}
};

int dp[MAX_N][MAX_N][2], movea[MAX_N][MAX_N];
bool used[MAX_N][MAX_N][2];
int cnt[MAX_N][MAX_N];
int n;

int cop;

int start(int N, bool A[MAX_N][MAX_N]){
    n = N;
    for(int i = 0; i < n; ++i){
    	for(int j = 0; j < n; ++j){
    		A[i][j] = A[i][j];
    	}
    }

    for(int i = 0; i < n; ++i){
    	for(int j = 0; j < n; ++j){
    		movea[i][j] = -1;
    	}
    }

    queue<Node> q;

    for(int i = 0; i < n; i++){
    	int t = 0;
    	for(int j = 0; j < n; j++){
    		if(A[i][j]){
    			t++;
    		}
    	}
    	for(int j = 0; j < n; j++){
    		cnt[j][i] = t;
    	}
    }

    for(int i = 0; i < n; ++i){
    	q.push(Node(i, i, false));
    	q.push(Node(i, i, true));
    	used[i][i][1] = true;
    	used[i][i][0] = true;
    	movea[i][i] = i;
    }

    while(!q.empty()){
    	Node t = q.front();
    	q.pop();

    	//cout << t.x << " " << t.y << " " << t.turn << endl;

    	if(t.turn){
    		for(int i = 0; i < n; ++i){
    			if(A[i][t.x] || i == t.x){
    				if(used[i][t.y][!t.turn]){
    					continue;
    				}
    				used[i][t.y][!t.turn] = true;
    				movea[i][t.y] = t.x; 
    				q.push(Node(i, t.y, !t.turn));
    			}
    		}
    	}
    	else{
    		for(int i = 0; i < n; ++i){
    			if(A[i][t.y]){
    				cnt[t.x][i]--;
    				if(!cnt[t.x][i]){
    					used[t.x][i][!t.turn] = true;
    					q.push(Node(t.x, i, !t.turn));
    				}
    			}
    		}
    	}
    }

    cop = -1;
    for(int i = 0; i < n; ++i){
    	int ok = true;
    	for(int j = 0; j < n; ++j){
    		if(movea[i][j] == -1){
    			ok = false;
    			break;
    		}
    	}
    	if(ok){
    		cop = i;
    	}
    }

    return cop;
}

int nextMove(int R){
	cop = movea[cop][R];

	return cop;
}
/*
g++ "Baltic 14-coprobber.cpp" grader.cpp -std=c++11 -O2 -static -Wall -o coprobber
*/
/*
4
0 1 0 0
1 0 1 0
0 1 0 1
0 0 1 0
0
*/
