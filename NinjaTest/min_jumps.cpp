/*
You are given an array of N integers, A1, A2 ,…, AN and an integer B which denotes that from any index i, you can jump to any of the indices i+1, i+2, …, i+B. Also, if you step on index i, you have to pay Ai coins. If Ai is -1, it means you can’t land on index i.

You start from index 1, and your aim is to reach index N. Return the path you should take to minimise the number of coins required. If there are multiple paths with same cost, return the lexicographically smallest such path. If its not possible to reach index N return empty array.

Notes

Ai is either > 0(denoting cost) or -1(denoting that it is not possible to land on index i).
You have to pay coins both at starting and ending indices.
Path a1, a2 ,…, an is lexicographically smaller than b1, b2 ,…, bm, if and only if at the first i where ai and bi differ, ai < bi, or if no such i exists, then n < m.
For example,

A=[1, 2, 4, -1, 2] and B = 2

The path which requires minimum coins is to start at index 1 and then move to index 3 and then to 5.
So return [1, 3, 5].

Another example,

A=[1, 2, 4, -1, 2] and B = 1

In this case it is not possible to reach index 5. So return empty array [].

*/

#include <bits/stdc++.h>

using namespace std;

vector<int> solve(vector<int> &A, int B){
	int n = A.size();
	vector<int> ans;
	if(n==0 || A[0]==-1 || A[n-1]==-1)
		return ans;
	vector<int> jumpFromIndex(n, -1);
	vector<int> cost(n, INT_MAX);
	jumpFromIndex[0]=0;
	cost[0]=A[0];
	for(int i=1; i<A.size(); i++){
		if(A[i]==-1)
			continue;
		for(int j=max(0, i-B); j<i; j++){
			if(A[j]==-1 || cost[j]==INT_MAX)
				continue;
			if(cost[i] > cost[j]){
				cost[i] = cost[j];
				jumpFromIndex[i] = j;
			}
		}
		if(cost[i]!=INT_MAX)
			cost[i] += A[i];
	}
	if(cost[n-1]==INT_MAX)
		return ans;
	int i=n-1;
	while(i!=0){
		ans.push_back(i+1);
		i = jumpFromIndex[i];
	}
	ans.push_back(0+1);
	reverse(ans.begin(), ans.end());
	return ans;
}

int main(){
	int n, k;
	cin >> n >> k;
	vector<int> A;
	int x;
	for(int i=0; i<n; i++){
		cin >> x;
		A.push_back(x);
	}
	vector<int> ans = solve(A, k);
	for(int i=0; i<ans.size(); i++)
		cout << ans[i] << " ";
	cout << endl;
	return 0;
}