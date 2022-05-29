/*
Second question of https://www.geeksforgeeks.org/directi-interview-experience-set-15-on-campus-2/
*/

#include <bits/stdc++.h>
using namespace std;

int maxRectangle(vector<vector<int> > &grid, int n){
	for(int i=1; i<3; i++){
		for(int j=0; j<n; j++)
			if(grid[i][j])
				grid[i][j] += grid[i-1][j];
	}
	int ans = 0;
	for(int i=0; i<3; i++){
		vector<int> left_min;
		stack<int> st;
		for(int j=0; j<n; j++){
			while(!st.empty() && grid[i][st.top()]>=grid[i][j])
				st.pop();
			if(st.empty())
				left_min.push_back(-1);
			else
				left_min.push_back(st.top());
			st.push(j);
		}
		while(!st.empty())
			st.pop();
		vector<int> right_min;
		for(int j=n-1; j>=0; j--){
			while(!st.empty() && grid[i][st.top()]>=grid[i][j])
				st.pop();
			if(st.empty())
				right_min.push_back(n);
			else
				right_min.push_back(st.top());
			st.push(j);
		}
		reverse(right_min.begin(),right_min.end());
		int area = 0;
		for(int j=0; j<n; j++){
			area = grid[i][j]*(right_min[j]-left_min[j]-1);
			ans = max(ans, area);
		}
	}
	return ans;
}

int main(){
	int test;
	cin >> test;
	for(int t=0; t<test; t++){
		int n, m;
		cin >> n >> m;
		vector<vector<int> > grid(3, vector<int> (n, 0));
		int r, s, e;
		for(int i=0; i<m; i++){
			cin >> r >> s >> e;
			grid[r-1][s-1]++;
			grid[r-1][e-1]--;
		}
		for(int i=0; i<3; i++){
			int count=0;
			for(int j=0; j<n; j++){
				count += grid[i][j];
				if(count){
					grid[i][j]=1;
				}
				else{
					if(grid[i][j]!=0)
						grid[i][j]=1;
				}
			}
		}
		cout << "Final grid is:\n";
		for(int i=0; i<3; i++){
			for(int j=0; j<n; j++)
				cout << grid[i][j] << " ";
			cout << endl;
		}
		cout << maxRectangle(grid, n) << endl;
	}
}