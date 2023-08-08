#include<bits/stdc++.h>

class Graph{
	int V;
	int s;
	int t;
	std::unordered_map<int,std::list<int>> adjList;
	std::vector<std::vector<int>> capacity;
	std::vector<std::vector<int>> flow;
public:
	Graph(int n,int s, int t){ // s = source; t = sink;
		this->V = n;
		this->s = s;
		this->t = t;
		for(int i = 0; i < n; i++){
			adjList[i]; //initializing empty list for each vertex
			capacity.push_back(std::vector<int>(n,0));
			flow.push_back(std::vector<int>(n,0));
		}
	}

	void addEdge(int from, int to, int cap){
		adjList[from].push_back(to);
		adjList[to].push_back(from);

		capacity[from][to] = cap;
		capacity[to][from] = 0; //Residual edge has zero capacity
	}

	void augment(int from, int to,int bottleNeck){
		flow[from][to] += bottleNeck;
		flow[to][from] -= bottleNeck;
	}

	int remainingCapacity(int at, int to){
		return capacity[at][to] - flow[at][to];
	}

	int fordFulkersonAlgorithm(){
		int maxFlow = 0;
		std::vector<int> visited(V,0);
		int visitedFlag = 1;
		int flow = dfs(s,visited,visitedFlag,INT_MAX);
		while(flow != 0){
			maxFlow += flow;
			visitedFlag++;

			flow = dfs(s,visited,visitedFlag,INT_MAX);
		}

		return maxFlow;
	}

	int dfs(int at,std::vector<int>&visited,int visitedFlag,int flow){
		visited[at] = visitedFlag;

		if(at == t) return flow;

		for(int to : adjList[at]){
			if(remainingCapacity(at,to) > 0 && visited[to] != visitedFlag){
				int bottleNeck = dfs(to,visited,visitedFlag,std::min(remainingCapacity(at,to),flow));

				if(bottleNeck > 0){
					augment(at,to,bottleNeck);

					return bottleNeck;
				}
			}
		}

		return 0;
	}


};

int main(){
	#ifndef ONLINE_JUDGE
	    freopen("input.txt", "r", stdin);
	    freopen("output.txt", "w", stdout);
	#endif
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int n = 12;
    int s = n - 2;
    int t = n - 1;
	Graph g(n,s,t); //Initializing the graph

	g.addEdge(s, 0, 10);
    g.addEdge(s, 1, 5);
    g.addEdge(s, 2, 10);

    // Middle edges
    g.addEdge(0, 3, 10);
    g.addEdge(1, 2, 10);
    g.addEdge(2, 5, 15);
    g.addEdge(3, 1, 2);
    g.addEdge(3, 6, 15);
    g.addEdge(4, 1, 15);
    g.addEdge(4, 3, 3);
    g.addEdge(5, 4, 4);
    g.addEdge(5, 8, 10);
    g.addEdge(6, 7, 10);
    g.addEdge(7, 4, 10);
    g.addEdge(7, 5, 7);

    // Edges to sink
    g.addEdge(6, t, 15);
    g.addEdge(8, t, 10);
	
    std::cout<<"\nMax flow: "<<g.fordFulkersonAlgorithm()<<std::endl;


	return 0;
}