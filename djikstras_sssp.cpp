//we need to specify the starting vertex for djikstras algorithm
#include<bits/stdc++.h>
using namespace std;


template<typename T>
class Graph{
private:
	int V;
	map<T,list<pair<T,int>>> adjList;
	unordered_map<T,bool> visited;
public:
	Graph(int v){
		V = v;
	}
	void addEdge(T a,T b,int W){//W cant be negative
		adjList[a].push_back(make_pair(b,W));
		adjList[b];//initializing the other vertex to ensure every vertex has a adjacency list
	}
	void djikstras_sssp(T src){
		map<T,int> distance;
		map<T,T> prev;
		for(auto p:adjList){
			distance[p.first] = INT_MAX;
		}
		distance[src] = 0;
		prev[src] = src;

		priority_queue<pair<int,T>,vector<pair<int,T>>,greater<pair<int,T>>> pq;

		pq.push(make_pair(distance[src],src));

		while(!pq.empty()){
			pair<int,T> current = pq.top();
			pq.pop();

			int w0 = current.first;
			T node = current.second;

			if(w0 > distance[node]){
				continue;
			}

			for(auto nbr:adjList[node]){
				T next = nbr.first;
				int wi = nbr.second;
				int dis = w0+wi;
				if(dis < distance[next]){
					distance[next] = dis;
					pq.push(make_pair(dis,next));
					prev[next] = node;
				}
			}
		}

		for(auto p:distance){
			cout<<p.first<<"   "<<p.second<<endl;
			
			if(p.second == INT_MAX) continue;

			T vertex = p.first;
			vector<T> vec;
			while(true){
				vec.push_back(vertex);
				vertex = prev[vertex];

				if(vertex == prev[vertex]){
					vec.push_back(vertex);
					break;
				}
			}

			for(int i = vec.size()-1;i>=0;i--){
				cout<<vec[i]<<" ";
			}
			cout<<endl;
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

	Graph<int> g(n);
	int e;
	cin>>e;
	while(e--){
		int a,b,w;
		cin>>a>>b>>w;
		g.addEdge(a,b,w);
	}

	g.djikstras_sssp(0);

	return 0;
}