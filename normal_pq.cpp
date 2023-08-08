#include<bits/stdc++.h>
using namespace std;

template<typename T>
class Heap{
private:
	int n;
	vector<T> h;
public:
	Heap(){
		n = 1;
		h.push_back(0);
	}
	void push(T v){
		h.push_back(v);
		
		int i = n; n = n+1;

		while(i != 1 and h[i] > h[i/2]){
			swap(h[i],h[i/2]);
			i/=2;
		}
	}
	T top(){
		return h[1];
	}
	void pop(){
		h[1] = h[n-1];
		
		int i = 1;

		while(i < n/2){
			if(h[2*i] < h[i] and h[2*i+1] < h[i]){
				break;
			}
			else{
				int c1 = 2*i;
				int c2 = 2*i+1;

				if(h[c1] > h[c2]){
					swap(h[i],h[c1]);
					i = c1;
				}
				else{
					swap(h[i],h[c2]);
					i = c2;
				}
			}
		}
		n--;
	}
	bool empty(){
		return n == 1;
	}
	void print(){
		for(int i = 1; i < n; i++){
			cout<<h[i]<<" ";
		}
		cout<<endl;
	}
	
};

void heapify(int*h,int n){
	int j = n/2;
	for(;j>=1;j--){
		int i = j;
		while(i <= n/2){
			int c1 = 2*i;
			int c2 = c1+1;

			int prior = i;
			if(c1 <= n && h[c1] > h[i]){
				prior = c1;
			}
			if(c2<=n && h[c2] > h[prior]){
				prior=c2;
			}
			swap(h[i],h[prior]);
			if(i == prior){
				break;
			}
			i = prior;
			
		}
	}
}

void heapSort(int*h,int n){
	while(n>1){
		swap(h[1],h[n]);
		heapify(h,n-1);
		n--;
	}
}

int main(){
	#ifndef ONLINE_JUDGE
	    freopen("input.txt", "r", stdin);
	    freopen("output.txt", "w", stdout);
	#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin>>n;

	int*a=new int[2*n]{0};
	Heap<int> h1;
	for(int i = 0; i < n; i++){
		int t;
		cin>>t;
		h1.push(t);
		a[i+1] = t;
	}

	h1.print();

	while(!h1.empty()){
		cout<<h1.top()<<" ";
		h1.pop();
	}
	cout<<endl<<"The array initially: \n";
	
	for(int i = 1; i < n+1; i++){
		cout<<a[i]<<" ";
	}
	
	cout<<endl;

	heapify(a,n);
	
	cout<<"After heapify: \n";
	
	for(int i = 1; i < n+1; i++){
		cout<<a[i]<<" ";
	}

	heapSort(a,n);
	cout<<"\nAfter heapSort: \n";
	
	for(int i = 1; i < n+1; i++){
		cout<<a[i]<<" ";
	}
	return 0;
}