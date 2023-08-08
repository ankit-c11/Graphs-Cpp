#include<bits/stdc++.h>
using namespace std;


class bridgesAndAP{
private:
	int id;
	int*visited;
	int*ids;
	int*lowLinks;
	int*isArticulation;
	int outEdgeCount;
	vector<pair<int,int>> bridges;
public:

	bridgesAndAP(int v){
		visited = new int[v]{0};
		ids = new int[v]{0};
		lowLinks = new int[v]{0};
		isArticulation = new int[v]{0};
	}
	void dfsHelper(int root,int vertex,int parent,unordered_map<int,list<int>> adjList){
		if(parent == root) outEdgeCount++;
		visited[vertex] = 1;
		id = id+1;
		ids[vertex] = lowLinks[vertex] = id;
		for(auto nbr:adjList[vertex]){
			if(nbr == parent){
				continue;
			}
			if(!visited[nbr]){
				dfsHelper(root,nbr,vertex,adjList);

				lowLinks[vertex] = min(lowLinks[vertex],lowLinks[nbr]);

				if(lowLinks[nbr] > ids[vertex]){
					bridges.push_back(make_pair(vertex,nbr));
					isArticulation[vertex] = 1;
				}
				if(lowLinks[nbr] == ids[vertex]){
					isArticulation[vertex] = 1;	
				}
			}
			else{
				lowLinks[vertex] = min(lowLinks[vertex],ids[nbr]);
			}
		}
	}
	vector<pair<int,int>> findBridges(int v,unordered_map<int,list<int>> adjList){

		for(int i = 0; i < v; i++){
			if(!visited[i]){
				outEdgeCount = 0;
				dfsHelper(i,i,-1,adjList);
				isArticulation[i] = (outEdgeCount>1);
			}		
		}

		cout<<"Articulation points are: \n";
		for(int i = 0; i < v; i++){
			if(isArticulation[i]){
				cout<<i<<", ";
			}
		}
		cout<<endl;
		return bridges;
	}
};


class graph{
private:
	int v;
	unordered_map<int,list<int>> adjList;
public:
	graph(int n){
		this->v = n;
	}
	void addEdge(int a, int b){
		adjList[a].push_back(b);
		adjList[b].push_back(a);
	}
	void findBridges(){
		bridgesAndAP solver(v);
		vector<pair<int,int>> b = solver.findBridges(v,adjList);
		cout<<"Bridges are \n";
		for(pair<int,int> p : b){
			cout<<p.first<<" to "<<p.second<<endl;
		}

		return;
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
	graph g(n);
	int e;
	cin>>e;
	while(e--){
		int a,b;

		cin>>a>>b;
		g.addEdge(a,b);

	}
	g.findBridges();
	cout<<endl;
	return 0;
}