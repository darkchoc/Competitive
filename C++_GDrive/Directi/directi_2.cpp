/*
You need to go from 0,0 to m,n and come back. Can't use diagonal elements. Go down using upper triangle and return using bottom triangle.
*/

#include <bits/stdc++.h>
using namespace std;

int arr[4][4] = {{5,11,4,6},
				 {3,2,10,3},
				 {1,3,1,3},
				 {4,2,8,8}};

int helper(int n){
	vector<vector<int> > dp (n, vector<int> (n, 0));
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			dp[i][j]=arr[i][j];
			if(i==j && i!=0 && i!=n-1)
				dp[i][j]=INT_MAX;
		}
	}

	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			int x = INT_MAX;
			if(i>0)
			 	x = min(x, dp[i-1][j]);
			x = min(x, dp[i][j-1]);
			dp[i][j] += x;
		}
	}

	for(int i=1; i<n; i++){
		for(int j=0; j<i; j++){
			int x = INT_MAX;
			if(j>0)
				x = min(x, dp[i][j-1]);
			x = min(x, dp[i-1][j]);
			dp[i][j] += x;
		}
	}
	return dp[n-2][n-1] + dp[n-1][n-2] + dp[n-1][n-1];
}

int main(){

	cout << helper(4);
	return 0;
}