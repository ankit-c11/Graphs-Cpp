#include<bits/stdc++.h>
using namespace std;
/*
	Pacman & Monsters

	Problem Statement :

	For centuries there has been a war between the mighty warriors of the planet Pacman and planet Monsters. 

	This year is no different: the battlefield has been set and it's time for the showdown. The battlefield has N rows and N columns: 
	   

	   1. Every row contains some units of Pacman and the Monsters. 
	   2. A Monster can kill at most one Pacman if and only if they are not in different rows.
	   3. Also, Pacman must be under the range of R units from the monster. 

	You need to print the minimum number of Pacman which will survive this year. 

	Input format:

	The first line of the input gives the number of test cases T to be answered. Each test case begins with 2 Integers N and R. 
	Size of the battlefield and the Range. 
	N lines consist of N space-separated units of ( "P" or "M" )


	Output format: 

	For each test case, In a new line output the minimum number of Pacman's which will survive this year. 

	Constraints:

	1<= T <= 10 
	1<= N <= 1000 
	1<= R <= N
	 
	Sample Input:

	1
	3 1
	P P M
	M P P
	M P M

	Sample Output:

	2

	Explanation:

	 

	There are a total 5 Pacman this year. 

	In the first row, the monster can kill only the pacman on his left.
	In the second row, the monster can kill pacman on hit right
	In the last row,either of the monsters can kill that pacman.

	Hence only 2 Pacman will survive this year.

	Things to Note for the Candidate:

	 

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
	int t;
	cin>>t;
	while(t--){
		int N,R;
		
		cin>>N>>R;
		
		vector<vector<char>> field;
		
		for(int i = 0; i < N; i++){
			vector<char> c; // initializing

			for(int j = 0; j < N; j++){
				cin.get();
				char ch = cin.get();

				c.push_back(ch);
			}
			field.push_back(c);
		}
		
		int survived = 0;
		for(int i = 0; i < N; i++){
			// vector<int> monsters;
			// vector<int> pacmans;

			// for(int j = 0; j < N; j++){
			// 	if(field[i][j] == 'P'){
			// 		pacmans.push_back(j);
			// 	}
			// 	else
			// 		monsters.push_back(j);
			// }

			// int n = pacmans.size() - monsters.size();
			// if(n < 0){
			// 	n = 0;
			// }

			// survived += n;

		}
		cout<<survived<<endl;
	}
	// return 0;
	return 0;
}