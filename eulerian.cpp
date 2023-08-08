#include<bits/stdc++.h>
using std::cout;
using std::endl;
using std::cin;

class Eulerian{
	std::unordered_map<int,int> inDegree;
	std::unordered_map<int,int> outDegree;
	std::stack<int> traversal;
public:
	Eulerian(int v){
		for(int i = 0; i < v; i++){
			inDegree[i];
			outDegree[i];
		}
	}
	void findInAndOutDegrees(std::map<int,std::list<int>> adjList){
		for(auto a:adjList){
			for(auto b:a.second){
				inDegree[b]++;
				outDegree[a.first]++;
			}
		}
	}
	bool hasEulerianPath(){
		int v = inDegree.size();
		int startNodes,endNodes;
		startNodes=endNodes=0;
		for(int i = 0; i < v; i++){
			if(inDegree[i]-outDegree[i] > 1 or outDegree[i]-inDegree[i] > 1){
				return false;
			}
			if(inDegree[i]-outDegree[i] == 1) endNodes++;
			if(outDegree[i]-inDegree[i] == 1) startNodes++;
		}
		return (startNodes == 1 and endNodes == 1) or (startNodes == 0 and endNodes == 0);
	}
	bool hasEulerianCircuit(){
		int v = inDegree.size();
		for(int i = 0; i < v; i++){
			if(inDegree[i] != outDegree[i]){
				return false;
			}
		}
		return true;
	}

	int findStartNode(){
		int start = 0;
		int n = inDegree.size();
		for(int i = 0; i < n; i++){
			if(outDegree[i]-inDegree[i] == 1){
				return i;
			}
			if(outDegree[i] > 0) start = i;
		}
		return start;

	}

	void dfs(int at,std::map<int,std::list<int>> adjList){
		while(outDegree[at] != 0){
			outDegree[at]--;
			int to = adjList[at].back();
			adjList[at].pop_back();
			dfs(to,adjList);
		}
		traversal.push(at);
	}
	
	std::stack<int> findEulerianPath(int e,std::map<int,std::list<int>> adjList){
		findInAndOutDegrees(adjList);
		if (!hasEulerianPath()) return traversal;
		
		dfs(findStartNode(),adjList);

		if (traversal.size() == e+1) return traversal;

		std::stack<int> s;
		return s;
	}
};

class Graph{
	int v,e;
	std::map<int,std::list<int>> adjList;
public:
	Graph(int n){
		this->v = n;
		this->e=0;
	}
	void addEdge(int a,int b){
		e++;
		adjList[a].push_back(b);
	}
	void printEulerianPath(){
		Eulerian solver(v);
		std::stack<int> traversal = solver.findEulerianPath(e,adjList);

		if(traversal.empty()){
			cout<<"Eulerian Path does not exist!!!"<<endl;
			return;
		}

		while(!traversal.empty()){
			cout<<traversal.top()<<"  ";
			traversal.pop();
		}

		return;
	}
};

int main(){
	#ifndef ONLINE_JUDGE
	    freopen("input.txt", "r", stdin);
	    freopen("output.txt", "w", stdout);
	#endif
	std::ios_base::sync_with_stdio(false);
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
	cout<<"The Eulerian traversal is: \n";
	g.printEulerianPath();
	// cout<<"Hello World!"<<endl;
	return 0;
}