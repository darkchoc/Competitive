//https://codeforces.com/blog/entry/66972

#include <bits/stdc++.h>

using namespace std;

/*
int dfs(vector<vector<int> > &adj, vector<int> &visited, vector<pair<int, int> > &parent, int node){
	if(visited[node]!=0)
		return 0;
	visited[node]=1;
	int childNodes = 0;
	for(int i=0; i<adj[node].size(); i++){
		if(visited[adj[node][i]]==0) {
			parent[adj[node][i]].first = node;
			childNodes += dfs(adj, visited, parent, adj[node][i]);
		}
	}
	parent[node].second = 1 + childNodes;
	return parent[node].second;
}

vector<int> solve(int nodes, vector<pair<int, int> > &edges, vector<int> &queries){
	vector<pair<int, int> > parent (nodes, make_pair(-1, 0)); //parent[i] contains who is parent of ith node, and number of nodes below this ith node + 1 (node itself).  
	vector<vector<int> > adj (nodes);
	for(int i=0; i<edges.size(); i++){
		adj[edges[i].first].push_back(edges[i].second);
		adj[edges[i].second].push_back(edges[i].first);
	}
	vector<int> visited (nodes, 0);
	parent[0].first = -1;
	parent[0].second = dfs(adj, visited, parent, 0);
	vector<int> ans;
	priority_queue<pair<int, int> > pq;
	pq.push(make_pair(nodes, 0));
	for(int i=0; i<queries.size(); i++){
		int u = queries[i].first;
		int v = queries[i].second;
		if(parents[u].first == v)
			swap(u,v);
		//now u is upper node
		pq.push(make_pair(parents[v].second, v));
		int temp = u;
		while(parents[temp].first!=-1){
			if(pq.find(parents[temp].second, temp)!=pq.end()){
				********
				//can't understand here onwards. 
				********
			}
		}

	}
	return visited;
}

int main(){
	int N, Q;
	cin >> N >> Q;
	vector<pair<int, int> > edges;
	int u, v;
	for(int i=0; i<N-1; i++){
		cin >> u >> v;
		edges.push_back(make_pair(u-1,v-1));
	}
	vector<int> queries (Q);
	for(int i=0; i<Q; i++){
		cin >> u;
		queries[i] = u-1;
	}
	vector<int> ans = solve(N, edges, queries);
	for(int i=0; i<ans.size(); i++)
		cout << ans[i] << " ";
	cout << endl;
	return 0;
}


		1
	2		3
	7		4 5 6
	8
9		10
*/

int getRoot(int n, vector<int> &parent){
	while(parent[n] != n)
		n = parent[parent[n]];
	return n;
}

void treeUnion(int u, int v, vector<int> &parent, vector<int> &size, int &maxSubtree){
	int parent_u = getRoot(u, parent);
	int parent_v = getRoot(v, parent);
	if(parent_u == parent_v){
		//won't ever happen I guess, since it is a tree and every node will join two unjoined subtrees
		return;
	}
	if(size[parent_u] > size[parent_v]){
		parent[parent_v] = parent_u;
		size[parent_u] += size[parent_v];
		maxSubtree = max(maxSubtree, size[parent_u]);
	} else {
		parent[parent_u] = parent_v;
		size[parent_v] += size[parent_u];
		maxSubtree = max(maxSubtree, size[parent_v]);
	}
	return;
}

vector<int> solve(int n, vector<pair<int, int> > &edges, vector<int> &queries){
	set<int> removedEdges;
	for(int i=0; i<queries.size(); i++)
		removedEdges.insert(queries[i]);
	vector<int> parent(n);
	vector<int> size(n, 1);
	for(int i=0; i<n; i++)
		parent[i] = i;
	int maxSubtree = 1;
	for(int i=0; i<edges.size(); i++){
		if(removedEdges.find(i)==removedEdges.end()){
			treeUnion(edges[i].first, edges[i].second, parent, size, maxSubtree);
		}
	}
	vector<int> ans ((int)queries.size());
	for(int i=queries.size()-1; i>=0; i--){
		ans[i] = maxSubtree;
		treeUnion(edges[queries[i]].first, edges[queries[i]].second, parent, size, maxSubtree);
	}
	return ans;
}

int main(){
	int N, Q;
	cin >> N >> Q;
	vector<pair<int, int> > edges;
	int u, v;
	for(int i=0; i<N-1; i++){
		cin >> u >> v;
		edges.push_back(make_pair(u-1, v-1));
	}
	vector<int> queries(Q);
	for(int i=0; i<Q; i++){
		cin >> u;
		queries[i] = u-1;
	}
	vector<int> ans = solve(N, edges, queries);
	for(int i=0; i<ans.size(); i++)
		cout << ans[i] << " ";
	cout << endl;
}

