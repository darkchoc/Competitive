/*
Spiderman, buildings, can jump only a certain height
https://www.geeksforgeeks.org/directi-programming-questions/
Question 10
*/

#include <bits/stdc++.h>
using namespace std;

int row[] = {-1, 0, 1, 0};
int col[] = {0, 1, 0, -1};

int helper_bfs(vector<vector<int> > &grid, int n, int m, int x, int y, int diff){
	vector<vector<int> > dist (n, vector<int> (m, INT_MAX));
	//bfs
	queue<pair<int, int> > q;
	q.push(make_pair(0,0));
	dist[0][0]=0;
	while(!q.empty()){
		pair<int, int> p = q.front();
		q.pop();
		int u = p.first, v = p.second;
		for(int i=0; i<4; i++){
			if(u+row[i]<n && u+row[i]>=0 && v+col[i]<m && v+col[i]>=0){
				if(abs(grid[u+row[i]][v+col[i]]-grid[u][v])<=diff){
					if(dist[u+row[i]][v+col[i]] > dist[u][v]+1){
						dist[u+row[i]][v+col[i]] = dist[u][v] + 1;
						q.push(make_pair(u+row[i], v+col[i]));
					}
				}
			}
		}
	}
	if(dist[x-1][y-1]==INT_MAX)
		return -1;
	else 
		return dist[x-1][y-1] - 1;
}

int helper_djikstra(vector<vector<int> > &grid, int n, int m, int x, int y, int diff){
	x--; y--;
	vector<vector<int> > dist(n, vector<int> (m, INT_MAX));
	priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > pq;
	pq.push(make_pair(0, make_pair(0,0)));
	dist[0][0]=0;
	while(!pq.empty()){
		pair<int, pair<int, int> > p = pq.top();
		pq.pop();
		int d = p.first;
		int u = p.second.first;
		int v = p.second.second;
		if(u==x && v==y)
			return dist[x][y]-1;
		for(int i=0; i<4; i++){
			if(u+row[i]<n && u+row[i]>=0 && v+col[i]<m && v+col[i]>=0){
				if(abs(grid[u+row[i]][v+col[i]] - grid[u][v])<=diff){
					if(dist[u+row[i]][v+col[i]]> dist[u][v]+1){
						dist[u+row[i]][v+col[i]] = dist[u][v]+1;
						pq.push(make_pair(dist[u+row[i]][v+col[i]], make_pair(u+row[i], v+col[i])));
					}
				}
			}
		}
	}
	if(dist[x][y]==INT_MAX)
		return -1;
	else
		return dist[x][y]-1;
}

int main(){
	int test;
	cin >> test;
	for(int t=1; t<=test; t++){
		int n, m, x, y, d;
		cin >> n >> m >> x >> y >> d;
		vector<vector<int> > grid (n, vector<int> (m));
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				cin >> grid[i][j];
			}
		}
		cout << helper_bfs(grid, n, m, x, y, d) << endl;
		cout << helper_djikstra(grid, n, m , x, y, d) << endl;
	}
}