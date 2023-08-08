#include<bits/stdc++.h>
using namespace std;

template <typename T>
class Graph{
private:
	int V;
	map<T,list<T>> adjList;
	map<T,bool> visited;
public:
	Graph(int v){
		V = v;
	}
	void addEdge(T a, T b){
		adjList[a].push_back(b);
	}
	void printGraph(){
		for(auto p:adjList){
			cout<<p.first<<" : ";
			for(auto nbr:p.second){
				cout<<nbr<<" ";
			}
			cout<<"\n";
		}
	}
	void clearVisited(){
		for(auto p:adjList){
			visited[p.first] = false;
		}
	}
	void topologicalSortHelper(T v,stack<T>& s){
		for(auto nbr:adjList[v]){
			if(!visited[nbr]){
				visited[nbr] = true;
				topologicalSortHelper(nbr,s);
			}
		}
		s.push(v);

	}
	void topologicalSort(stack<T>& s){
		for(auto p:adjList){
			if(!visited[p.first]){
				visited[p.first] = true;
				topologicalSortHelper(p.first,s);
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
		int a,b;
		cin>>a>>b;
		g1.addEdge(a,b);
	}

	g1.printGraph();

	stack<int> topologicalOrdering;

	g1.topologicalSort(topologicalOrdering);

	while(!topologicalOrdering.empty()){
		cout<<topologicalOrdering.top()<<" ";
		topologicalOrdering.pop();
	}
	cout<<"\n";

	return 0;
}