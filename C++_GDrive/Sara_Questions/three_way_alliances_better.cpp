/*
Question:
There are N tribes in a country numbered from 1 to N. 
For any two different tribes, they are either in alliance or hostility. These relations are symmetric.
These relations are not transitive. 
For 3 different tribes, if all of them are in an alliance, we call them as in "3-way-alliance". Similary, 
if all of them are in a hostility, we call them as in "3-way-hostility".

Given relationships between N tribes, return the sum of all of the 3-way-alliances and 3-way-hostilities.
First line: T <Test cases>
N <Number of tribes> M <number of alliances>
x1 y1 <alliance one between x1 and y1 tribe, x1<y1>
x2 y2
.
.
.
xm ym

Example: if 5 tribes, {1,2}, {1,3} and {1,4} are alliances. In this case: {2,3,4}, {2,3,5} are 3-way-hostility
No 3-way-alliance. So answer=2

Example 2: if N=5, {1,2},{2,3},{1,3} are alliances. In this case: {1,2,3} is alliance, {1,4,5},{2,4,5},{3,4,5} are hositilities.
So answer = 4.
*/

/*
Draw a alliance graph, and the complement of it will be hostility graph. Together they form a complete graph.
Draw alliance graph. 
My thinking: Draw on paper and try to see that each edge will result in elimination of how many alliances. 
An edge that is not connected to any other edge will result in removal of n-2 triplets, that could have been constructed using 
it. 
A pair of edge connected to each other but not any other edges will result in elimination of (n-2)+(n-2)-1 triplets. 
This is because while considering n-2 to for both, we remove the same triplet two times, which included both the edges.

Ans so on..we can arrive at the formula.
*/
#include <bits/stdc++.h>

using namespace std;

double nC3(double n){
	double ans = (n*(n-1)*(n-2))/(double)6.0;
	return ans;
}

int main(){
	int test;
	cin >> test;
	for(int t=1; t<=test; t++){
		double n, m;
		cin >> n >> m;
		vector<int> degree(n, 0);
		vector<vector<int> > adj (n);
		int x, y;
		for(int i=0; i<m; i++){
			cin >> x >> y;
			degree[x-1]++;
			degree[y-1]++;
			adj[x-1].push_back(y-1);
		}
		if(n<3)
			cout << 0 << endl;
		else{
			double max_triplets = nC3(n);
			double ans = max_triplets;
			for(int i=0; i<n; i++){
				for(int j=0; j<adj[i].size(); j++){
					int x, y;
					x=i;
					y=adj[i][j];
					ans -= (n - 2.0 - ((degree[x]+degree[y]-2.0)*(0.5)));
				}
			}
			cout << (long long int)ans << endl;
		}
	}
	return 0;
}

/* Bad brute force code
#include <bits/stdc++.h>

using namespace std;

void dfs2(vector<vector<bool> > &graph, int starting_node, int current_node, int curr_count, long long int &ans){
	if(curr_count==2){
		if(!graph[current_node][starting_node]){
			ans++;
		}
		return;
	}
	else {
		for(int i=current_node+1; i<graph.size(); i++){
			if(!graph[current_node][i]){
				dfs2(graph, starting_node, i, curr_count+1, ans);
			}
		}
	}
}

void dfs(vector<vector<bool> > &graph, int starting_node, int current_node, int curr_count, long long int &ans){
	if(curr_count==2){
		if(graph[current_node][starting_node])
			ans++;
		return;
	}
	else {
		for(int i=current_node+1; i<graph.size(); i++){
			if(graph[current_node][i])
				dfs(graph, starting_node, i, curr_count+1, ans);
		}
	}
	return;
}

long long int helper(vector<vector<bool> > &graph, int n){
	long long int ans = 0;
	for(int i=0; i<n; i++){
		dfs(graph, i, i, 0, ans);
	}
	for(int i=0; i<n; i++){
		dfs2(graph, i, i, 0, ans);
	}
	return ans;
}

int main(){
	int test;
	cin >> test;
	for(int t=1; t<=test; t++){
		int n, m;
		cin >> n >> m;
		vector<vector<bool> > graph(n, vector<bool> (n, false));
		int x, y;
		for(int i=0; i<m; i++){
			cin >> x >> y;
			graph[x-1][y-1]=true;
			graph[y-1][x-1]=true;
		}
		if(n<3)
			cout << 0 << endl;
		else{
			long long int ans = helper(graph, n);
			cout << ans << endl;
		}
	}
	return 0;
}
*/