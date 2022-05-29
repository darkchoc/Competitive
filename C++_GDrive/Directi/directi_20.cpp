/*
Unique value subtrees
11th question of: https://www.geeksforgeeks.org/directi-programming-questions/
*/

#include <bits/stdc++.h>
using namespace std;

bool traverse(int parent, int current, int &ans, vector<vector<int> > &graph, vector<int> &vals){
	bool uniq = true;
	for(int i=0; i<graph[current].size(); i++){
		if(graph[current][i]==parent)
			continue;
		bool is_subtree_unique = traverse(current, graph[current][i], ans, graph, vals);
		if(!is_subtree_unique || vals[current]!=vals[graph[current][i]])
			return false;
	}
	ans++;
	return uniq;
}

int main(){
	int n;
	cin >> n;
	vector<int> vals(n);
	for(int i=0; i<n; i++)
		cin >> vals[i];
	vector<vector<int> > graph(n);
	int u, v;
	for(int i=0; i<n-1; i++){
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	int ans = 0;
	traverse(-1, 0, ans, graph, vals);
	cout << ans << endl;
	return 0;
}