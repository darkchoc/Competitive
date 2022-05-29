/*
https://www.geeksforgeeks.org/find-maximum-dot-product-two-arrays-insertion-0s/
*/

#include <bits/stdc++.h>
using namespace std;

int recurse(vector<int> &A, vector<int> &B, int n, int m, int inda, int indb, vector<vector<int> > &dp){
	if(indb==-1)
		return 0;
	if(indb==inda){
		int temp = 0;
		while(inda>=0){
			temp+=A[inda]*B[inda];
			inda--;
		}
		dp[indb][indb]=temp; //coz inda has become 0
		return dp[indb][indb];
	}
	if(dp[inda][indb]!=INT_MIN)
		return dp[inda][indb];
	dp[inda][indb] = recurse(A, B, n, m, inda-1, indb-1, dp)+A[inda]*B[indb];
	if(inda>indb)
		dp[inda][indb]=max(dp[inda][indb], 
						   recurse(A, B, n, m, inda-1, indb, dp));
	return dp[inda][indb];
}

int helper(vector<int> &A, vector<int> &B, int n, int m){
	vector<vector<int> > dp1 (n, vector<int> (m, INT_MIN));
	int x = recurse(A, B, n, m, n-1, m-1, dp1);

	//bottom up
	vector<vector<int> > dp (n, vector<int> (m, 0));
	for(int b=0; b<m; b++){
		for(int a=b; a<n; a++){
			if(b==0)
				dp[a][0]=max(a>0?dp[a-1][0]:0, A[a]*B[b]);
			else
				dp[a][b] = max(dp[a-1][b-1]+A[a]*B[b], dp[a-1][b]);
		}
	}
	cout << x << " " << dp[n-1][m-1] << endl;
	return x;
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<int> A(n);
	vector<int> B(m);
	for(int i=0; i<n; i++)
		cin >> A[i];
	for(int i=0; i<m; i++)
		cin >> B[i];
	cout << helper(A, B, n, m);
}