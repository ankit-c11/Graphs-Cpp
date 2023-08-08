#include<bits/stdc++.h>
using namespace std;

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

		MinIndexedPQ pq(V);

		pq.insert(src,distance[src]);
	
		while(!pq.isEmpty()){
			int index = pq.deleteMin();


			int w0 = pq.keyOf(index);

			if(w0 > distance[index]){
				continue;
			}

			for(auto nbr:adjList[index]){
				T next = nbr.first;
				int wi = nbr.second;
				int dis = w0 + wi;
				if(dis < distance[next]){
					distance[next] = dis;
					if(pq.contains(next)){
						pq.decreaseKey(next,dis);
					}
					else
						pq.insert(next,dis);
				
					prev[next] = index;
				}
			}
		}

		for(auto p:distance){			
			if(p.second == INT_MAX){
				cout<<(-1)<<endl;continue;
			}

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

	g.djikstras_sssp(1);

	return 0;
}