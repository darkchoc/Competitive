#include<bits/stdc++.h>

using namespace std;

void dfs (int current_cluster, vector<int> &cluster_number, vector<set<int> > &in_edges, vector<set<int> > &out_edges, vector<bool> &visited, int current_node){
	cluster_number[current_node] = current_cluster;
	visited[current_node] = true;
	for(set<int>::iterator it = out_edges[current_node].begin(); it!=out_edges[current_node].end(); it++) {
		if(visited[*it]==false)
			dfs(current_cluster, cluster_number, in_edges, out_edges, visited, *it);
	}
	for(set<int>::iterator it = in_edges[current_node].begin(); it!=in_edges[current_node].end(); it++) {
		if(visited[*it]==false)
			dfs(current_cluster, cluster_number, in_edges, out_edges, visited, *it);
	}
	return;
}


int make_clusters(vector<int> &cluster_number, vector<set<int> > &in_edges, vector<set<int> > &out_edges, int n){
	//for purpose of assigning cluster numbers, consider it to be undirected graph
	vector<bool> visited (n, false);
	int current_cluster = 0;
	for(int i=0; i<n; i++){
		if (cluster_number[i]==-1) {
			dfs(current_cluster, cluster_number, in_edges, out_edges, visited, i);
			current_cluster++;
		}
	}
	return current_cluster;
}

int get_max_of_cluster(int cluster, vector<int> &cluster_number, vector<set<int> > &in_edges, vector<set<int> > &out_edges, int n){
	return 0;
}

int main() {
	int test;
	cin >> test;
	for( int t=0; t<test; t++) {
		int n;
		cin >> n; 
		vector<int> fun (n, 0);
		int x;
		for(int i=0; i<n; i++){
			cin >> x;
			fun[i] = x;
		}
		vector< set<int> > in_edges (n);
		vector< set<int> > out_edges (n);
		cout << n << endl;
		for(int i=0; i<n; i++) {
			cin >> x;
			int y; 
			for(int j=0; j<x; j++){
				cin >> y;
				in_edges[i].insert(y-1);
				out_edges[y-1].insert(i);
			}
		}

		vector<int> cluster_number (n, -1);
		int total_clusters = make_clusters(cluster_number, in_edges, out_edges, n);
		
		int final_ans = 0;
		for(int cluster=0; cluster<total_clusters; cluster++) {
			int max_cluster_fun = get_max_of_cluster(cluster, cluster_number, in_edges, out_edges, n);
			final_ans += max(0, max_cluster_fun);
		}
		cout << final_ans << endl;
	}
	return 0;
}