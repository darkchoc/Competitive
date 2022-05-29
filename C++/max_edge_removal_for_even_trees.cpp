/*
https://www.geeksforgeeks.org/maximum-edge-removal-tree-make-even-forest/
Input:
Number of nodes (0 based indexing for nodes)
N-1 lines, each having two integers -> edge between these nodes
*/

#include <bits/stdc++.h>

using namespace std;

int dfs(vector<vector<int> > &adj, vector<bool> &visited, int &ans, int curr){
	visited[curr] = true;
	int subTreeNodesToBeConsidered = 0;
	for(int i=0; i<adj[curr].size(); i++){
		if(visited[adj[curr][i]]==false){
			int currSubTreeNodes = dfs(adj, visited, ans, adj[curr][i]);
			if(currSubTreeNodes%2 == 0){
				//means we can remove edge between curr & adj[curr][i]
				cout << "Removed edge between " << curr << " " << adj[curr][i] << endl;
				ans++;
				//no need to consider these nodes for further calculation
			} else{
				subTreeNodesToBeConsidered += currSubTreeNodes;
			}
		}
	}
	return subTreeNodesToBeConsidered + 1;
}

int solve(int n, vector<vector<int> > &adj){
	int ans = 0;
	vector<bool> visited (n, false);
	int x = dfs(adj, visited, ans, 0);
	return ans;
}

int main(){
	int n;
	cin >> n;
	vector<pair<int, int> > edges(n-1);
	int u, v;
	vector<vector<int> > adj (n);
	for(int i=0; i<n-1; i++){
		cin >> u >> v;
		edges[i] = make_pair(u, v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int ans = solve(n, adj);
	cout << ans;
}