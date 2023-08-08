#include<bits/stdc++.h>

class Edge{
public:
	int from;
	int to;
	int capacity;
	int flow;

	Edge* residual;

	Edge(int from,int to,int capacity){
		this->from = from;
		this->to = to;
		this->capacity = capacity;
		this->flow = 0;
		this->residual = NULL;
	}

	bool isResidual(){
		return capacity == 0;
	}

	int remainingCapacity(){
		return (capacity-flow);
	}

	void augment(int bottleNeck){
		flow += bottleNeck;
		// residual->flow -= bottleNeck;
	}
	void print(){
		std::cout<<"From "<<from<<"  To "<<to<<"  with capacity: "<<capacity<<"  and flow: "<<flow<<std::endl;
	}
};

class NetworkFlowSolverBase{
	int n,s,t;
	std::vector<int> visited;
	bool solved;
	int visitedToken;
	int maxFlow;
	std::map<int,std::list<Edge>> graph; //The adjacency list representing the flow graph
public:
	NetworkFlowSolverBase(int n,int s,int t){
		this->n = n;
		this->s = s;
		this->t = t;
		solved = false;
		visitedToken = 1;
		maxFlow = 0;
		initializeEmptyFlowGraph();
	}
	void initializeEmptyFlowGraph(){
		for(int i = 0; i < n; i++){
			visited.push_back(0);
			graph[i]; 
		}
	}
	void addEdge(int from, int to, int capacity){

		Edge* e1 = new Edge(from,to,capacity);
		Edge* e2 = new Edge(to,from,0); //The back edge or the residual edge

		e1->residual = e2;
		e2->residual = e1;

		graph[from].push_back(*e1);
		graph[to].push_back(*e2);
	}
	int getMaxFlow(){
		execute();
		return maxFlow;
	}
	void execute(){
		if(solved) return;
		solved = true;
		solve();
	}
	void solve(){
		int f = dfs(s,INT_MAX);
		while(f!=0){
			maxFlow += f;
			visitedToken++;
			f = dfs(s,INT_MAX);
		}	
	}
	int dfs(int node,int flow){
		if(node == t) return flow; //we've reached the sink
		visited[node] = visitedToken;

		for(Edge& e : graph[node]){
			if(e.remainingCapacity() > 0 && visited[e.to] != visitedToken){
				
				int bottleNeck = dfs(e.to,std::min(flow,e.remainingCapacity()));
						
				if(bottleNeck > 0){
					e.augment(bottleNeck);
					e.residual->augment(-bottleNeck);
					
					return bottleNeck;
				}
			}
		}
		return 0;
	}
	void printGraph(){
		for(auto p:graph){
			for(auto e:p.second){
				e.print();
			}
		}
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
    NetworkFlowSolverBase solver(n, s, t);


    // Edges from source
    solver.addEdge(s, 0, 10);
    solver.addEdge(s, 1, 5);
    solver.addEdge(s, 2, 10);

    // Middle edges
    solver.addEdge(0, 3, 10);
    solver.addEdge(1, 2, 10);
    solver.addEdge(2, 5, 15);
    solver.addEdge(3, 1, 2);
    solver.addEdge(3, 6, 15);
    solver.addEdge(4, 1, 15);
    solver.addEdge(4, 3, 3);
    solver.addEdge(5, 4, 4);
    solver.addEdge(5, 8, 10);
    solver.addEdge(6, 7, 10);
    solver.addEdge(7, 4, 10);
    solver.addEdge(7, 5, 7);

    // Edges to sink
    solver.addEdge(6, t, 15);
    solver.addEdge(8, t, 10);

    // solver.printGraph();
    std::cout<<"\nMax flow: "<<solver.getMaxFlow()<<std::endl;

	return 0;
}