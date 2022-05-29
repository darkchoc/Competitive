#include <bits/stdc++.h>
using namespace std;

long long int helper(vector<vector<int> > &grid, int n, int m, int k, int q){
	vector<vector<vector<int>>> dp (n, vector<vector<int>> (m, vector<int> (k, INT_MAX)));
	if(grid[0][0]==1){
		dp[0][0][1]
	}	

}

int main(){
	int n, m, k, q;
	cin >> n >> m >> k >> q;
	vector<vector<int> > grid (n, vector<int> (m, 0));
	int r, c;
	for(int i=0; i<k; i++){
		cin >> r >> c;
		grid[r-1][c-1]=1;
	}
	for(int i=0; i<q; i++){
		cin >> c;
		for(int i=0; i<r; i++){
			if(grid[i][c-1]==0)
				grid[i][c-1]=2;
		}
	}
	cout << helper(grid, n, m, k, q) << endl;
	return 0;
}