#include<bits/stdc++.h>
using namespace std;

class graph
{	
	int v;
	list<pair<int,int>> l;
public:
	graph(int v){
		this->v = v;
	}

	int addEdge(int u,int v){
		l.push_back(make_pair(u,v));
	}

	//DSU find
	int findSet(int i,vector<int> &parent){
		if(parent[i] == -1){
			return i;
		}

		return parent[i] = findSet(parent[i],parent);
	}

	//DSU union
	void unionSet(int x,int y,vector<int>&parent){
		int s1 = findSet(x,parent);
		int s2 = findSet(y,parent);

		if(s1!=s2){
			parent[s1] = s2;
		}
	}

	bool containsCycle(){
		//DSU logic to check graph contains cycle or not

		vector<int> parent(v+1,-1);
		vector<int> ranks(v+1,1);

		for(auto edge:l){

			int i = edge.first;
			int j = edge.second;

			int s1 = findSet(i,parent);
			int s2 = findSet(j,parent);

			if(s1!=s2){ //Union by rank
				if(ranks[s2] >= s1){
					parent[s1] = s2;
					ranks[s2] += s1;
				}
				else{
					parent[s2] = s1;
					ranks[s1] += s2;
				}
			}
			else{
				return true;
			}

		}

		return false;
	}
	
};

int main(){
	#ifndef ONLINE_JUDGE
	    freopen("input.txt", "r", stdin);
	    freopen("output.txt", "w", stdout);
	#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// int n;
	// cin>>n;

	graph g(4);

	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(3,4);
	g.addEdge(4,1);

	if(g.containsCycle()){
		cout<<"Graph contains cycle..\n";
	}
	else{
		cout<<"No cycle found...";
	}
	return 0;
}