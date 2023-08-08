#include<bits/stdc++.h>
using namespace std;

int main(){

	priority_queue<pair<int,int>> pq;
	
	int N;
	cin>>N;

	map<int,int> count;

	for(int i = 0; i < N; i++){
		int t;
		cin>>t;
		count[t]++;
	}

	for(auto p : count){
		pq.push(make_pair(p.second,p.first));
	}

	while(!pq.empty()){
		pair<int,int> p = pq.top();
		pq.pop();

		cout<<p.second<<endl;
	}


	return 0;
}