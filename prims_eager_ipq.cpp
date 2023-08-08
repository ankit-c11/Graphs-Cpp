#include<bits/stdc++.h>
using namespace std;
//Read the comment:
/*
			The input:
			8
			13
			0 1 10
			0 2 1 
			0 3 4
			2 1 3
			2 3 2
			1 4 0
			2 5 8
			3 5 2
			3 6 7
			5 6 6
			5 4 1
			5 7 9
			4 7 8
			6 7 12
*/
class Edge{
public:
	int from;
	int to;
	int cost;
	Edge(int from, int to, int cost){
		this->from = from;
		this->to = to;
		this->cost = cost;
	}
	void print(){
		cout<<"Edge from "<<from<<" to "<<to<<" costing "<<cost<<endl;
	}
};

class MinIndexedPQ {
    int NMAX, N, *heap, *index, *keys;

    void swap(int i, int j) {
        int t = heap[i]; heap[i] = heap[j]; heap[j] = t;
        index[heap[i]] = i; index[heap[j]] = j;
    }

    void bubbleUp(int k)    {
        while(k > 1 && keys[heap[k/2]] > keys[heap[k]])   {
            swap(k, k/2);
            k = k/2;
        }
    }

    void bubbleDown(int k)  {
        int j;
        while(2*k <= N) {
            j = 2*k;
            if(j < N && keys[heap[j]] > keys[heap[j+1]])
                j++;
            if(keys[heap[k]] <= keys[heap[j]])
                break;
            swap(k, j);
            k = j;
        }
    }

public:
    // Create an empty MinIndexedPQ which can contain atmost NMAX elements
    MinIndexedPQ(int NMAX)  {
        this->NMAX = NMAX;
        N = 0;
        keys = new int[NMAX + 1];
        heap = new int[NMAX + 1];
        index = new int[NMAX + 1];
        for(int i = 0; i <= NMAX; i++)
            index[i] = -1;
    }
	
    ~MinIndexedPQ() {
        delete [] keys;
        delete [] heap;
        delete [] index;
    }

    // check if the PQ is empty
    bool isEmpty()  {
        return N == 0;
    }

    // check if i is an index on the PQ
    bool contains(int i)    {
        return index[i] != -1;
    }

    // return the number of elements in the PQ
    int size()  {
        return N;
    }

    // associate key with index i; 0 < i < NMAX
    void insert(int i, int key) {
        N++;
        index[i] = N;
        heap[N] = i;
        keys[i] = key;
        bubbleUp(N);
    }

    // returns the index associated with the minimal key
    int minIndex()  {
        return heap[1];
    }

    // returns the minimal key
    int minKey()    {
        return keys[heap[1]];
    }

    // delete the minimal key and return its associated index
    // Warning: Don't try to read from this index after calling this function
    int deleteMin() {
        int min = heap[1];
        swap(1, N--);
        bubbleDown(1);
        index[min] = -1;
        heap[N+1] = -1;
        return min;
    }

    // returns the key associated with index i
    int keyOf(int i)    {
        return keys[i];
    }

    // change the key associated with index i to the specified value
    void changeKey(int i, int key)  {
        keys[i] = key;
        bubbleUp(index[i]);
        bubbleDown(index[i]);
    }

    // decrease the key associated with index i to the specified value
    void decreaseKey(int i, int key){
        keys[i] = key;
        bubbleUp(index[i]);
    }

    // increase the key associated with index i to the specified value
    void increaseKey(int i, int key){
        keys[i] = key;
        bubbleDown(index[i]);
    }

    // delete the key associated with index i
    void deleteKey(int i)   {
        int ind = index[i];
        swap(ind, N--);
        bubbleUp(ind);
        bubbleDown(ind);
        index[i] = -1;
    }
};

class Graph{
	int V;
	map<int,list<Edge>> adjList;
	map<int,Edge*> bestEdgeFor;
public:
	Graph(int n){
		this->V = n;
		for(int i = 0; i < n; i++){
			adjList[i];
			bestEdgeFor[i] = NULL;
		}
	}
	void addEdge(int a, int b,int w){
		//Undirected edges => bidirectional edges
		Edge e(a,b,w);
		Edge e_(b,a,w);
		adjList[a].push_back(e);
		adjList[b].push_back(e_);
	}
	void relaxEdgesAtNode(int currentNode,MinIndexedPQ& ipq,vector<int>&visited){
		visited[currentNode] = 1;
		for(Edge& e : adjList[currentNode]){
			int destNode = e.to;
			if(visited[destNode]){
				continue;
			}
			if(!ipq.contains(destNode)){
				ipq.insert(destNode,e.cost);

				bestEdgeFor[destNode] = &e; //new Edge(e.from,e.to,e.cost); // Works
			}
			else{
				if(e.cost < ipq.keyOf(destNode)){
					ipq.decreaseKey(destNode,e.cost);
					bestEdgeFor[destNode] = &e;//new Edge(e.from,e.to,e.cost);
				}
			}
		}
	}
	vector<Edge*> primsMST(){
		int s = 0; //choosing the starting node
		vector<int> visited(V,0);
		MinIndexedPQ ipq(V);
		visited[s] = 1; // marking the starting node visited

		int m = V - 1;
		int edgeCount,mstCost;
		edgeCount = mstCost = 0;
		vector<Edge*> mstEdges; // This is the return value in case the mst exists

		relaxEdgesAtNode(s,ipq,visited);
		
		while(!ipq.isEmpty() and edgeCount != m){
			
			int vertex = ipq.minIndex();
			ipq.deleteMin(); 
			Edge* e = bestEdgeFor[vertex];

			mstEdges.push_back(e);
			edgeCount++;
			mstCost += e->cost;
			relaxEdgesAtNode(vertex,ipq,visited);

		}
		
		if(edgeCount != m){
			cout<<"MST does not exist\n";
			vector<Edge*> vec;
			return vec;
		}
		cout<<"MST found with minimum cost: "<<mstCost<<endl;
		return mstEdges;
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

	vector<Edge*> mst = g.primsMST();
	for(Edge* e : mst){
		e->print();
	}
	return 0;
}