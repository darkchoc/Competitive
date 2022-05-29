/*
Two sets of courses, penalty given for switching. Can skip k courses at a time
Question 2 of
https://www.geeksforgeeks.org/directi-interview-experience-set-19-round-1-questions/
*/


#include <bits/stdc++.h>
using namespace std;

int helper(vector<int> &A, vector<int> &B, int n, int p, int k){
	vector<vector<int> > dp(2, vector<int> (n, INT_MAX));
	dp[0][0]=A[0];
	dp[1][0]=B[0];
	for(int i=1; i<n; i++){
		for(int j=i-1; j>=0 && j>=i-k; j--){
			dp[0][i] = min(dp[0][i], dp[0][j]);
			dp[0][i] = min(dp[0][i], dp[1][j]+p);
			dp[0][i] += A[i];
			dp[1][i] = min(dp[1][i], dp[1][j]);
			dp[1][i] = min(dp[1][i], dp[0][j]+p);
			dp[1][i] += B[i];
		}
	}
	return min(dp[0][n-1], dp[1][n-1]);
}

int main(){
	int test;
	cin >> test;
	for(int t=1; t<=test; t++){
		int n, p, k;
		cin >> n  >> k >> p ;
		vector<int> A(n);
		vector<int> B(n);
		for(int i=0; i<n; i++){
			cin >> A[i];
		}
		for(int i=0; i<n; i++){
			cin >> B[i];
		}
		cout << helper(A, B, n, p, k) << endl;
	}
}