/*
https://www.geeksforgeeks.org/directi-interview-experience-set-16-pool-campus-for-application-developer/
Binary sum
*/
#include <bits/stdc++.h>
using namespace std;


int pathsum(vector<int> &nodes, int n, int curr, int &ans){
	if(curr>=n)
		return 0;
	int left = pathsum(nodes, n, 2*curr+1, ans);
	int right = pathsum(nodes, n, 2*curr+2, ans);

	ans = max(ans, nodes[curr]+left+right); // now answer will be either passing through this node, or not.
	return max(left,right)+nodes[curr];
}

int helper(vector<int> &nodes, int n){
	//sum either goes through root, or is within one children.
	int ans = INT_MIN;
	pathsum(nodes, n, 0, ans); //gives max sum possible from this node to a leaf. 
	return ans;
}

int main(){
	int n;
	cin >> n; 
	vector<int> nodes(n);
	for(int i=0; i<n; i++)
		cin >> nodes[i];
	cout << helper(nodes, n);
}