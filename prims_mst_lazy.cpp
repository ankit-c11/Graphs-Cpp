#include<bits/stdc++.h>
using namespace std;

#define pipii pair<int,pair<int,int>>

class Edge{
public:
	int at;
	int to;
	int cost;

	Edge(int at,int a,int b){
		this->at = at;
		this->to = a;
		this->cost = b;
	}
	void print(){
		cout<<"Edge from "<<at<<" to "<<to<<" costing "<<cost<<endl;
	}
};

class Compare{
public:
	bool operator()(Edge a,Edge b){
		return a.cost > b.cost;
	}
};
class Graph{
private:
	int V;
	map<int,list<Edge>> adjList;
	priority_queue<pipii,vector<pipii>,greater<pipii>> pq;
public:
	Graph(int n){
		this->V = n;
		for(int i = 0; i < V; i++){
			adjList[i];
		}
	}
	void addEdge(int a,int b,int w){
		Edge e(a,b,w);
		Edge e_(b,a,w);
		adjList[a].push_back(e);
		adjList[b].push_back(e_);
	}
	void addEdgesToPQ(int s,int* visited){
		visited[s] = 1;
		for(Edge e : adjList[s]){
			if(!visited[e.to]){
				pq.push(make_pair(e.cost,make_pair(e.at,e.to)));
			}
		}
	}
	vector<Edge> findMST(){
		vector<Edge> mstEdges;
		int edgeCount,mstCost;
		edgeCount = mstCost = 0;
		
		int*visited = new int[V]{0};

		addEdgesToPQ(0,visited);

		while(!pq.empty() and edgeCount != V-1){
			pipii node = pq.top();
			pq.pop();

			int cost = node.first;
			auto edge = node.second;
			int at = edge.first;
			int to = edge.second;
			if(visited[to]) continue;

			addEdgesToPQ(to,visited);

			Edge e(at,to,cost);
			edgeCount++;
			mstEdges.push_back(e);   
			mstCost += cost;
		}

		if(edgeCount != V-1){
			cout<<"MST does not exist...\n";
			vector<Edge> vec;
			return vec;
		}
		cout<<"MST found with minimum cost = "<<mstCost<<endl;
		return mstEdges;
	}
	//DSU FIND with path compression
	int find(int x,vector<int>&parent){
		if(parent[x] == -1) return x;

		return parent[x] = find(parent[x],parent);
	}

	void kruskalsMST(){
		vector<int> parent(V,-1);
		vector<int> ranks(V,1);

		priority_queue<Edge,vector<Edge>,Compare> minPQ;

		int mstCost = 0;

		for(int i = 0; i < V; i++){
			for(Edge e : adjList[i]){
				minPQ.push(e);
			}
		}

		vector<Edge> edges;

		while(!minPQ.empty()){
			Edge e = minPQ.top();
			minPQ.pop();

			int s1 = find(e.at,parent);
			int s2 = find(e.to,parent);

			if(s1 != s2){ //Union by rank
				if(ranks[s2] >= s1){
					parent[s1] = s2;
					ranks[s2] += s1;
				}
				else{
					parent[s2] = s1;
					ranks[s1] += s2;
				}
				mstCost += e.cost;
				edges.push_back(e);
			}	
		}

		cout<<"MST COST: "<<mstCost<<endl;
		for(Edge e : edges){
			cout<<e.at<<" "<<e.to<<" "<<e.cost<<endl;
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

	Graph g(n);

	int e;
	cin>>e;
	while(e--){
		int a,b,w;
		cin>>a>>b>>w;

		g.addEdge(a,b,w);
	}

	vector<Edge> mst = g.findMST();
	for(Edge e : mst){
		e.print();
	}

	g.kruskalsMST(); // Uses the disjoint set union data structure


	return 0;
}