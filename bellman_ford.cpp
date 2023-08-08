#include<bits/stdc++.h>
using namespace std;

template <typename T>
class Edge{
public:
	T from;
	T to;
	int cost;

	Edge(int a,int b,int w){
		this->from = a;
		this->to = b;
		this->cost = w;
	}
};

template <typename T>
class Graph{
	int V;
	int E;
	vector<Edge<T>> edgeList;
public:
	Graph(int v){
		this->V = v;
		this->E = 0;
	}

	void addEdge(T a,T b,int w){
		edgeList.push_back(Edge<T>(a,b,w));
		E++;
	}

	void bellmanFord(T src){
		map<T,int> distance;
		for(int i = 0; i < V; i++){
			distance[i] = INT_MAX;
		}
		distance[src] = 0;

		for(int i = 0; i < V; i++){
			for(auto edge:edgeList){
				if(distance[edge.from] + edge.cost < distance[edge.to]){
					distance[edge.to] = distance[edge.from] + edge.cost;
				}
			}
		}
		for(int i = 0; i < V; i++){
			for(auto edge:edgeList){
				
				if(distance[edge.from] == INT_MIN){
					distance[edge.to] = INT_MIN;
				}
				else if(distance[edge.from] + edge.cost < distance[edge.to]){
					distance[edge.to] = INT_MIN;
				}
			}
		}
		cout<<"The minimum distance from the source "<<src<<" is:\n";
		for(auto p:distance){
			cout<<p.first<<"        "<<p.second<<endl;
		}
	}	

	void printEdges(){
		for(auto edge:edgeList){
			cout<<edge.from<<"  to  "<<edge.to<<"  with cost  "<<edge.cost<<endl;
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

	Graph<int> G(n);

	int E;
	cin>>E;
	while(E--){
		int a,b,w;
		cin>>a>>b>>w;
		G.addEdge(a,b,w);
	}

	// G.printEdges();
	G.bellmanFord(0);

	return 0;
}