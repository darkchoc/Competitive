/*

Move through grid in which you can jump right or down by grid[i][j] exactly. Traverse as few cells as possible.
Question 9 in https://www.geeksforgeeks.org/directi-programming-questions/

*/

include <bits/stdc++.h>
using namespace std;

int recurse(vector<vector<int> > &dp, int r, int c, vector<vector<int> > &grid){
	if(dp[r][c]!=0)
		return dp[r][c];
	int n = dp.size();
	int m = dp[0].size();
	if(r==n-1 && c==m-1)
		return 1;
	int x = -1, y = -1;
	if(grid[r][c] + r < n){
		x = recurse(dp, r+grid[r][c], c, grid);
	}
	if(grid[r][c]+c < m){
		y = recurse(dp, r, grid[r][c]+c, grid);
	}
	if(x==-1 && y==-1)
		dp[r][c]=-1;
	else if(x==-1)
		dp[r][c]=1+y;
	else if(y==-1)
		dp[r][c]=1+x;
	else 
		dp[r][c] = 1+min(x, y);
	return dp[r][c];
}

int helper(vector<vector<int> > &grid, int n, int m){
	vector<vector<int> > dp (n, vector<int> (m, 0));
	return recurse(dp, 0, 0, grid);
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<vector<int> > grid(n, vector<int> (m));
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++)
			cin >> grid[i][j];
	}
	cout << helper(grid, n, m) << endl;
	return 0;
}