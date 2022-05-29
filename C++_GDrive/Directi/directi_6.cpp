/*
	find maximum square with same digits in the matrix
*/

#include <bits/stdc++.h>
using namespace std;

int helper(vector<vector<int> > &mat, int n){
	vector<vector<int> > dp (n, vector<int> (n, 0));
	int ans = 1;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i==0 || j==0)
				dp[i][j]=1;
			else if(mat[i][j]==mat[i-1][j] && mat[i][j]==mat[i][j-1] && mat[i][j]==mat[i-1][j-1])
				dp[i][j] = min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1])) + 1;
			ans = max(ans, dp[i][j]);
		}
	}
	return ans;
}

int main(){
	int arr[4][4] = {{9,9,9,8},
				   {9,9,9,6},
				   {9,9,9,3},
				   {2,2,2,2}};
	vector<vector<int> > mat (4, vector<int> (4));
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			mat[i][j] = arr[i][j];
		}
	}	
	cout << helper(mat, 4);
}