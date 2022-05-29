/*
LCS
*/

#include <bits/stdc++.h>
using namespace std;

int helper_bottom_up(string A, string B){
	int n = A.length();
	int m = B.length();
	if(n==0 || m==0)
		return 0;
	vector<vector<int> > dp (n+1, vector<int> (m+1));
	for(int i=0; i<=m; i++)
		dp[0][i]=0;
	for(int i=0; i<=n; i++)
		dp[i][0]=0;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(A[i]==B[j])
				dp[i][j] = 1+dp[i-1][j-1];
			else
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		}
	}
	return dp[n][m];
}

int recurse(string A, string B, int inda, int indb, vector<vector<int> > &dp){
	if(inda==-1 || indb==-1)
		return 0;
	if(A[inda]==B[indb])
		dp[inda][indb] = 1+recurse(A, B, inda-1, indb-1, dp);
	else{
		dp[inda][indb]=max(recurse(A, B, inda-1, indb, dp), recurse(A, B, inda, indb-1, dp));
	}
	return dp[inda][indb];
}

int helper_recursive(string A, string B){
	int n = A.length();
	int m = B.length();
	if(n==0 || m==0)
		return 0;
	vector<vector<int> > dp (n, vector<int> (m, -1));
	return recurse(A, B, n-1, m-1, dp);
}

int main(){
	string first, second;
	cin >> first >> second;
	cout << helper_recursive(first, second) << endl;
	cout << helper_bottom_up(first, second) << endl;
	return 0;
}