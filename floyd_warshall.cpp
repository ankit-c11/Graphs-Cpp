#include<bits/stdc++.h>
using namespace std;

#define POSITIVE_INFINITY int(1e7)
#define NEGATIVE_INFINITY int(-(1e7))

class Graph{
private:
	int v;
	int** m;
public:
	Graph(int n){
		this->v = n;
		for(int i = 0; i < n; i++){
			m[i] = new int[n];
			for(int j = 0; j < n; j++){
				m[i][j] = POSITIVE_INFINITY; // Initially no edges
			}
			m[i][i] = 0; //Distance of a node from itself
		}
	}
	void addEdge(int a,int b,int W){
		m[a][b] = W;

	}
	void printGraph(){
		for(int i = 0; i < v; i++){
			for(int j = 0; j < v; j++){
				cout<<m[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	void floydWarshall(){
		int**dp = new int*[v];
		int**next = new int*[v];
		for(int i = 0; i < v; i++){
			dp[i] = new int[v];
			next[i] = new int[v];

			for(int j = 0; j < v; j++){
				if(dp[i][j] != POSITIVE_INFINITY){
					next[i][j] = j;
				}
				dp[i][j] = m[i][j];
			}
		}

		for(int k = 0; k < v; k++){
			for(int i = 0; i < v; i++){
				for(int j = 0; j < v; j++){
					if(dp[i][k] != POSITIVE_INFINITY && dp[k][j] != POSITIVE_INFINITY && dp[i][k] + dp[k][j] < dp[i][j]){
						dp[i][j] = dp[i][k] + dp[k][j];
						next[i][j] = next[i][k];
					}
				}
			}
		}
		// TARJANS SCC


		//Now identifying the negative cycles
		for(int k = 0; k < v; k++){
			for(int i = 0; i < v; i++){
				for(int j = 0; j < v; j++){
					if(dp[i][j] == NEGATIVE_INFINITY){
						dp[i][j] = NEGATIVE_INFINITY;
						next[i][j] = -1;
					}
					if(dp[i][k] != POSITIVE_INFINITY && dp[k][j] != POSITIVE_INFINITY && (dp[i][k] + dp[k][j] < dp[i][j] or dp[k][k] < 0)){
						dp[i][j] = NEGATIVE_INFINITY;
						next[i][j] = -1;
					}
				}
			}
		}
		cout<<"Printing the dp grid: "<<endl;
		for(int i = 0; i < v; i++){
			for(int j = 0 ; j < v; j++){
				cout<<dp[i][j]<<"         ";
			}
			cout<<endl;
		}
		cout<<"Printing DOne"<<endl;
		for(int i = 0; i < v; i++){
			for(int j = 0; j < v; j++){
				// cout<<next[i][j]<<"       ";
				vector<int>path;
				if(dp[i][j] == POSITIVE_INFINITY){
					cout<<"Shortest path between "<<i<<" and "<<j<<" is INIFINITY.\n";
					continue;
				}
				

				int at = i;
				for(;at != j; at=next[at][j]){
					if(at == -1){
						cout<<"Shortest path between "<<i<< " and "<< j<<" is -INFINITY.\n";
						break;
					}
					path.push_back(at);
				}
				if(at == -1){
					continue;
				}
				if(at != -1 && next[at][j] == -1){
					cout<<"Shortest path between "<<i<< " and "<< j<<" is -INFINITY.\n";
					continue;
				}
				else{
					path.push_back(j);

					cout<<"Path from "<<i<<" to "<<j<<" is : ";
					for(int i : path){
						cout<<i<<" --> ";
					}
					cout<<" end.\n";
				}

			}
			cout<<"\n";
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

	g.printGraph();
	cout<<endl;

	g.floydWarshall();

	return 0;	
}