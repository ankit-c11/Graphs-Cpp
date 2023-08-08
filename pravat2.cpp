#include<bits/stdc++.h>
using namespace std;

int main(){
	#ifndef ONLINE_JUDGE
	    freopen("input.txt", "r", stdin);
	    freopen("output.txt", "w", stdout);
	#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);


	// priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
	
	map<int,set<int,greater<int>>> m;

	int N;
	cin>>N;

	for(int i = 0; i < N; i++){
		int x,y;
		cin>>x>>y;
		m[x].insert(y);
	}

	for(auto p : m){
		for(auto q : p.second){
			cout<<p.first<<" "<<q<<endl;
		}
	}


	return 0;
}