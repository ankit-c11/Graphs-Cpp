#include<bits/stdc++.h>
using namespace std;

class tarjansSCC{
	int*visited;
	stack<int> s;
	int* onStack;
	int* low; // stores the low link
	int* ids; //stores the id
	int scc;
	int id;
public:
	tarjansSCC(int v){
		onStack = new int[v+1]{0};
		visited = new int[v+1]{0};
		ids = new int[v+1]{0};
		low = new int[v+1]{0};
		scc = 0;id = 0;
	}

	void dfsHelper(int current,unordered_map<int,list<int>> adjList){
		visited[current] = 1;
		ids[current] = low[current] = ++id;

		s.push(current);
		onStack[current] = 1;
		
		for(int next : adjList[current]){
			if(!visited[next]) dfsHelper(next,adjList);

			if(onStack[next]){
				low[current] = min(low[current],low[next]);
			}
		}
		if(ids[current] == low[current]){
			while(true){
				int node = s.top();
				s.pop();
				onStack[node] = 0;
				low[node] = ids[current];
				if(node == current) break;
			}
			scc++;
		}	
	}

	int* getStronglyConnectedComponents(int v, unordered_map<int,list<int>> adjList){
		
		for(int i = 1; i <= v; i++){
			if(!visited[i]){
				dfsHelper(i,adjList);
			}
		}
		cout<<"Found "<<scc<<" StronglyConnectedComponents\n";
		return low;
	}

};


class Graph{
	int v;
	unordered_map<int,list<int>> adjList;

public:
	Graph(int n){
		this->v = n;
	}
	void addEdge(int a, int b){ // directed edges.
		adjList[a].push_back(b);
	}

	void getSCC(){
		tarjansSCC solver(v);
		int*low = solver.getStronglyConnectedComponents(v,adjList);
		
		for(int i = 1; i <= v; i++){
			cout<<low[i]<<"  ";
		}
		cout<<endl;
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

	Graph g(n);
	
	int e;
	cin>>e;
	while(e--){
		int a,b;
		cin>>a>>b;
		g.addEdge(a,b);
	}

	// int*lowLinks = 
	g.getSCC();

	return 0;
}