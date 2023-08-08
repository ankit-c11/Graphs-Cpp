#include<bits/stdc++.h>
using namespace std;

template <typename T>
class Graph{
private:
	int vertices;
	unordered_map<T,list<T>> adjList;
	unordered_map<T,bool> visited;
public:
	Graph(int v){
		vertices = v;
		cout<<"Graph initalized\n";
	}
	void addEdge(T u,T v){
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	void dfs(T v){
		if(visited[v]){
			return;
		}
		visited[v] = true;
		cout<<v<<" ";
		for(auto nbr:adjList[v]){
			dfs(nbr);
		}
	}
	void DFS_HELPER(T v){
		if(visited[v]){
			return;
		}
		visited[v] = true;
		// cout<<v<<" ";
		for(auto nbr:adjList[v]){
			DFS_HELPER(nbr);
		}
	}
	int connectedComponents(){
		int components = 0;
		for(auto p : adjList){
			if(!visited[p.first]){
				DFS_HELPER(p.first);
				components++;
			}
		}
		return components;
	}
	T* BFS(T v){// BFS is particularly useful for one thing, finding shortest path on unweighted graph
		queue<T> q;
		q.push(v);
		visited[v] = true;
		T * previous = new T[vertices];
		previous[v] = -1;
		while(!q.empty()){
			T v = q.front();
			q.pop();
			cout<<v<<" ";
			for(auto nbr : adjList[v]){
				if(!visited[nbr]){
					visited[nbr] = true;
					q.push(nbr);
					previous[nbr] = v;
				}
			}
		}
		return previous;
	}
	void clearVisited(){
		for(auto p:adjList){
			visited[p.first] = false;
		}
	}
	void printGraph(){
		for(auto p: adjList){
			cout<<p.first;
			for(auto nbr: p.second){
				cout<<"-->"<<nbr;
			}
			cout<<'\n';
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

	int V;
	cin>>V;

	Graph<int> g1(V);
	int e;
	cin>>e;
	while(e--){
		int u,v;
		cin>>u>>v;
		g1.addEdge(u,v);
	}

	g1.clearVisited();
	cout<<"DFS starting from vertex 0:\n";
	g1.dfs(0);
	cout<<endl;

	g1.clearVisited();
	cout<<"Counting the number of connectedComponents:\n";
	cout<<g1.connectedComponents()<<endl;

	g1.clearVisited();
	int*prev = g1.BFS(0);
	cout<<endl;
	int dest;
	cin>>dest;

	vector<int> path;
	while(prev[dest]!=-1){
		// cout<<dest<<" --> ";
		path.push_back(dest);
		dest = prev[dest];
	}
	path.push_back(dest);
	for(auto i = path.end()-1;i >= path.begin(); i--){
		cout<<(*i)<<" --> ";
	}
	return 0;
}