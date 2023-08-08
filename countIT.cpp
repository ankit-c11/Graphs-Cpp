#include<bits/stdc++.h>
using namespace std;
/*
	Count it

	Problem Statement :


	You are given an integer N. You have to count the number of sequences A1,A2,..,AN
	that follows all the below conditions-


	0 <= Ai <= 9
	There must at least one index i where Ai = 1 (1<=i<=N)
	There must at least one index i where Ai = 2 (1<=i<=N)
	Print the count modulo 998244353.

	Constraints :


	1 <= N <= 2 * 10^5

	Input Format :


	First-line contains N, denoting the length of the sequence.

	Output Format  :


	Print a single integer denoting the count of sequences modulo 998244353 that follows all the above-mentioned conditions.

	Sample Input :


	2

	Sample Output :

	2

	Explanation of Sample :

	Sequences are [1,2] ,[2,1]

	Things to Note for the Candidate :

	You can use your own IDE like Visual Studio Code, Eclipse, or any other IDE that you are comfortable with to build your solution code.
	The IDE provided on the platform is purely for submission. Avoid using the IDE for coding out the solution.
	Test against any custom input in your own IDE. In the IDE provided on the platform, you cannot pass custom test cases and see the output. 
	Use standard input and standard output in your program for the IDE to run the test cases smoothly against your code. We are giving a sample problem statement along with a solution that will pass the test cases in the IDE. - Sample Problem Statement  (Right Click and Open in New Tab to view.)

*/

int main(){
	#ifndef ONLINE_JUDGE
	    freopen("input.txt", "r", stdin);
	    freopen("output.txt", "w", stdout);
	#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin>>n;

	int mod = 998244353;

	long long ans = (n * (n-1))%mod;
	for(int i = 0; i < n-2; i++){
		ans = (ans*10)%mod;
	}
	cout<<ans<<'\n';

	return 0;
}