/*
Defining substring
For a string P with characters P1, P2 ,…, Pq, let us denote by P[i, j] the substring Pi, Pi+1 ,…, Pj.

Defining longest common subsequence(LCS)
A subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements. LCS(A, B) of 2 sequences A and B is a subsequence, with maximal length, which is common to both the sequences.

Given a string S with small alphabet characters S1, S2 ,…, SN, return an array with two elements. First is the smallest j (1 ≤ j < N) for which LCS(S[1, j], rev(S[j + 1, N])) is maximal and second is the maximal value of LCS(S[1, j], rev(S[j + 1, N])).
Here, rev(A) denotes reverse of string A.

For example,

S="abba"

LCS(S[1, 1], rev(S[2, 4])) = LCS("a", "abb") = 1
LCS(S[1, 2], rev(S[3, 4])) = LCS("ab", "ab") = 2
LCS(S[1, 3], rev(S[4, 4])) = LCS("abb", "a") = 1

Hence, we return [2, 2].

*/

#include <bits/stdc++.h>

using namespace std;

//I tried different approaches. Started with a very brute force approach just to get a feel of the problem.
void recurseBruteForce(string &A, int l, int r, int &maxlen, int &finalj, int currLength){
	if(l >= r)
		return;
	if(l==r-1 || l==r-2){
		if(A[l]==A[r]){
			currLength++;
			if(maxlen < currLength){
				maxlen = currLength;
				finalj = l;
			} else if(maxlen == currLength){
				if(finalj > l)
					finalj = l;
			}
			return;
		}
	}
	if(A[l]==A[r]){
		//I forgot to put below if-else condition. This caused wrong answer coz we want to update everytime we get matching characters, not just when l==r-1 || l==r-2.
		currLength++;
		if(maxlen < currLength){
			maxlen = currLength;
			finalj = l;
		} else if(maxlen == currLength){
			if(finalj > l)
				finalj = l;
		}
		recurseBruteForce(A, l+1, r-1, maxlen, finalj, currLength);
	}
	else{
		recurseBruteForce(A, l+1, r, maxlen, finalj, currLength);
		recurseBruteForce(A, l, r-1, maxlen, finalj, currLength);
	}
	return;
}

vector<int> bruteForce(string A){
	int maxlen=0, finalj=0;
	recurseBruteForce(A, 0, A.length()-1, maxlen, finalj, 0);
	vector<int> ans;
	ans.push_back(finalj+1);
	ans.push_back(maxlen);
	return ans;
}


//After coding the brute force, I applied more brain and thought of simplifying the problem to get rid of TLE.
int bad_lcs(string &A, string &B, int a, int b, vector<vector<int> > &dp){
	if(a+1+b+1 > A.length())
		return 0;
	//Here dp[a][b] will store max common sequence between A[a...x] and reverse(A[x+1...(n-1-b)]) for a <= x < b.
	if(dp[a][b]!=-1)
		return dp[a][b];
	if(A[a]==B[b])
		dp[a][b] = 1 + bad_lcs(A, B, a+1, b+1, dp);
	else
		dp[a][b] = max(bad_lcs(A, B, a+1, b, dp), bad_lcs(A, B, a, b+1, dp));
	return dp[a][b];
}


vector<int> efficientSolution(string A){
	string B = A;
	reverse(B.begin(), B.end());
	int n = A.length();
	vector<vector<int> > dp(n, vector<int> (n, -1));
	int maxlen = bad_lcs(A, B, 0, 0, dp);
	//Now while maxlen will be correct, we cannot know where the minimum j is because of two reasons.
	//1. dp doesn't store that. dp[a][b] is storing what I've mentioned above. 
	//2. We cannot iterate over dp also because not all cells will be filled, since we have a recursive dp. There might be certain indices that may not be filled in this approach.
	//This led me to implement a iterative lcs solution.

	//good lcs
	dp.resize(n, vector<int> (n, 0));
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(A[i]==B[j])
				dp[i][j] = (i>0 && j>0)?dp[i-1][j-1]+1:1;
			else 
				dp[i][j] = max((i>0)?dp[i-1][j]:0, (j>0)?dp[i][j-1]:0);
		}
	}
	//In the above, dp[i][j] stores max common sequence between A[0...i] and reverse(A[n-1-j...n-1])
	int max_len=0, finalj = 0;
	for(int j=0; j<n-1; j++){
		if(dp[j][n-1-(j+1)] > max_len){
			max_len = dp[j][n-j-2];
			finalj = j;
		}
	}
	vector<int> ans;
	ans.push_back(finalj+1);
	ans.push_back(max_len);
	return ans;
}

vector<int> solve(string A){
	//return bruteForce(A);
	return efficientSolution(A);
}

int main(){
	string A;
	cin >> A;
	vector<int> ans = solve(A);
	cout << ans[0] << " " << ans[1] << endl;
	return 0;
}