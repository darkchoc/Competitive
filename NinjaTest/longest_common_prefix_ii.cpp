/*
Defining substring
For a string P with characters P1, P2 ,…, Pq, let us denote by P[i, j] the substring Pi, Pi+1 ,…, Pj.

Defining longest common prefix
LCP(S1, S2 ,…, SK), is defined as largest possible integer j such that S1[1, j] = S2[1, j] = … = SK[1, j].

You are given an array of N strings, A1, A2 ,…, AN and an integer K. Count how many indices (i, j) exist such that 1 ≤ i ≤ j ≤ N and LCP(Ai, Ai+1 ,…, Aj) ≥ K. Print required answer modulo 109+7.

Note that K does not exceed the length of any of the N strings. K <= min(len(A_i)) for all i

For example,

A = ["ab", "ac", "bc"] and K=1.

LCP(A[1, 1]) = LCP(A[2, 2]) = LCP(A[3, 3]) = 2
LCP(A[1, 2]) = LCP("ab", "ac") = 1
LCP(A[1, 3]) = LCP("ab", "ac", "bc") = 0
LCP(A[2, 3]) = LCP("ac", "bc") = 0

So, answer is 4.
Return your answer % MOD = 1000000007

Constraints
1 ≤ Sum of length of all strings ≤ 5*105
Strings consist of small alphabets only.
*/

#include <bits/stdc++.h>

using namespace std;

bool lcp_greater_than_k(string A, string B, int k){
	for(int i=0; i<k; i++)
		if(A[i]!=B[i])
			return false;
	return true;
}

int solve(vector<string> &A, int k){
	long long int ans = 0;
	int left = 0, right = 0;
	int mod = 1000000007;
	while(right < A.size()){
		if(left == right){
			ans = (ans + 1)%mod;
			right++;
		} else if(lcp_greater_than_k(A[left], A[right], k)){
			ans = (ans + (right - left + 1)%mod)%mod;
			right++;
		} else {
			left = right;
		}
	}
	return ans%mod;
}


int main(){
	int n, k;
	cin >> n >> k;
	vector<string> A;
	string s;
	for(int i=0; i<n; i++){
		cin >> s;
		A.push_back(s);
	}
	cout << solve(A, k) << endl;
	return 0;
}
