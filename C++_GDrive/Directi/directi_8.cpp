/*
https://www.geeksforgeeks.org/directi-interview-experience-set-16-pool-campus-for-application-developer/
Costly Visit
*/

#include <bits/stdc++.h>
using namespace std;

int helper(vector<vector<int> > &mat, vector<vector<int> > &P, int n, int m){
	vector<vector<vector<int>>> dp(n, vector<vector<int>> (m, vector<int> (2,INT_MAX)));
	// dp[i][j][0] -> means coming at i,j from top
	// dp[i][j][1] -> means coming at i,j from right
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(i==0 && j==0){
				dp[i][j][0]=mat[i][j];
				dp[i][j][1]=mat[i][j];
			}
			else if(i==0){
				dp[i][j][0] = INT_MAX;
				dp[i][j][1] = dp[i][j-1][1] + mat[i][j];
			}
			else if(j==0){
				dp[i][j][0] = dp[i-1][j][0] + mat[i][j];
				dp[i][j][1] = INT_MAX;
			}
			else{
				int top = min(dp[i-1][j][0], 
						dp[i-1][j][1]!=INT_MAX?(dp[i-1][j][1]+P[i-1][j]):INT_MAX);
				dp[i][j][0]= (top!=INT_MAX)?(mat[i][j]+top):top;
				int right = min(dp[i][j-1][1],
						dp[i][j-1][0]!=INT_MAX?(dp[i][j-1][0]+P[i][j-1]):INT_MAX);
				dp[i][j][1] = right!=INT_MAX?(mat[i][j]+right):right;
			}
		}
	}
	return min(dp[n-1][m-1][0], dp[n-1][m-1][1]);
}

int main() {
	int test;
	cin >> test;
	for(int t=1; t<=test; t++){
		int n, m;
		cin >> n >> m;
		vector<vector<int> > mat (n, vector<int> (m));
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++)
				cin >> mat[i][j];
		vector<vector<int> > p (n, vector<int> (m));
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++)
				cin >> p[i][j];
		cout << helper(mat, p, n, m) << endl;
	} 
	return 0;
}