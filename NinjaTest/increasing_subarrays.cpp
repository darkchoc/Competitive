/*
You are given an array of N positive integers, A1, A2 ,…, AN.

Let’s denote by A[i, j] the subarray Ai, Ai+1 ,…, Aj.

Count pairs (i, j) such that 1 ≤ i ≤ j ≤ N and subarray A[i, j] is increasing. Return the value modulo 109 + 7.

Notes

A subarray A1, A2 ,…, AN is increasing if Ai < Ai+1, for all 1 ≤ i < N.
For example,

A=[4, 5, 1, 2]

All subarrays of size 1 are increasing.

Subarrays A[1, 2], A[3, 4] of size 2 are increasing.

No subarray of size 3 and 4 is increasing.

So, total of 6 subarrays are increasing.

*/


#include <bits/stdc++.h>

using namespace std;

int solve(vector<int> &A){
	int mod = 1000000007;
	int l=0, r=0;
	int ans = 0;
	while(r<A.size()){
		if(r==l){
			ans = (ans+1)%mod;
			r++;
		}
		else if(A[r] > A[r-1]){
			ans = (ans + (r-l+1)%mod)%mod;
			r++;
		}
		else{
			l = r;
		}
	}
	return ans%mod;
}

int main(){
	int n;
	int x;
	cin >> n;
	vector<int> A;
	for(int i=0; i<n; i++){
		cin >> x;
		A.push_back(x);
	}
	cout << solve(A);
	return 0;
}