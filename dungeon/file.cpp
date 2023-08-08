#include<bits/stdc++.h>
using namespace std;

bool matchLocations(pair<int,int> A, pair<int,int> B){
	return (A.first == B.first && A.second == B.second);
}

int main(){
	#ifndef ONLINE_JUDGE
	    freopen("input.txt", "r", stdin);
	    freopen("output.txt", "w", stdout);
	#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int R,C;
	cin>>R>>C;
	char**dungeon = new char*[R];
	for(int i = 0; i < R; i++){
		dungeon[i] = new char[C];
		cin.get(); // consumes the enter
		for(int j = 0; j < C; j++){
			dungeon[i][j] = cin.get();
		}
	}

	int sr,sc,er,ec;
	cin>>sr>>sc>>er>>ec;
	pair<int,int> S = make_pair(sr,sc);
	pair<int,int> E = make_pair(er,ec);


	int dr[4] = {-1,+1,0,0};
	int dc[4] = {0,0,+1,-1};

	queue<pair<int,int>> q;

	map<pair<int,int>,bool> visited;
	map<pair<int,int>,pair<int,int>> previous;
	previous[S] = S;
	visited[S] = true;
	q.push(S);
	while(!q.empty()){
		pair<int,int> current = q.front();
		int r = current.first;
		int c = current.second;
		q.pop();
		if(r == E.first && c == E.second){
			break;
		}
		for(int i = 0; i < 4; i++){
			int r_ = r + dr[i];
			int c_ = c + dc[i];
			if(r_ < 0 or r_ >= R){
				continue;
			}
			if(c_ < 0 or c_ >= C){
				continue;
			}
			if(dungeon[r_][c_] == '#'){
				continue;
			}
			pair<int,int> next = make_pair(r_,c_);

			if(!visited[next]){
				q.push(next);
				visited[next] = true;
				previous[next] = current;
			}
		}
	}
	int path_length = 0;
	
	if(visited[E]){
		while(!matchLocations(S,E)){
			E = previous[E];
			path_length++;
		}
		cout<<path_length<<" steps to reach E from S"<<endl;
	}
	else{
		cout<<"No path exists"<<endl;
	}
	return 0;
}