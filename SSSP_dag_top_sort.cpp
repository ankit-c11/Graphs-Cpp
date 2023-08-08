#include<bits/stdc++.h>
using namespace std;

template <typename T>
class Graph{
private:
	int V;
	map<T,list<pair<T,int>>> adjList;
	map<T,bool> visited;
public:
	Graph(int v){
		V = v;
	}
	void addEdge(T a, T b,int W){
		adjList[a].push_back(make_pair(b,W));
	}
	void printGraph(){
		for(auto p:adjList){
			cout<<p.first<<" : ";
			for(auto nbr:p.second){
				cout<<nbr.first<<" ";
			}
			cout<<"\n";
		}
	}
	void clearVisited(){
		for(auto p:adjList){
			visited[p.first] = false;
		}
	}
	int topSortHelper(int i,int*ordering,T v){
		for(auto nbr:adjList[v]){
			if(!visited[nbr.first]){
				visited[nbr.first] = true;
				i = topSortHelper(i,ordering,nbr.first);
			}
		}
		ordering[i] = v;

		return i-1;
	}

	int* toplogicalOrdering(){
		int*ordering = new int[V];
		int idx = V-1;
		for(auto p:adjList){
			if(!visited[p.first]){
				visited[p.first] = true;
				idx = topSortHelper(idx,ordering,p.first);
			}
		}
		return ordering;
	}

	void sssp_topological(T src,int*toplogicalOrdering){
		vector<int> distance(V,INT_MAX);
		distance[src] = 0;

		for(int i = 0; i < V; i++){
			T node = toplogicalOrdering[i];
			if(distance[node] != INT_MAX){
				
			}
		}
	}
};

int main(){
	#ifndef ONLINE_JUDGE
	    freopen("input.txt", "r", stdin);
	    freopen("output.txt", "w", stdout);
	#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin>>n;

	Graph<int> g1(n);

	int e;
	cin>>e;
	while(e--){
		int a,b,w;
		cin>>a>>b>>w;
		g1.addEdge(a,b,w);
	}

	g1.printGraph();

	g1.clearVisited();

	int*ordering = g1.toplogicalOrdering();


	for(int i = 0; i < n; i++){
		cout<<ordering[i]<<" ";
	}
	cout<<endl;

	
	



	return 0;
}