/*
Given matrix, with white and black cells. 0 = white, 1 = black
Given Q queries with (x,y,k). Find length of max square possible with center as (x,y) and at most k black cells.
Return array of length Q with answers to each query.
*/

#include <bits/stdc++.h>

using namespace std;

vector<int> solve(vector<vector<int> > &mat, vector<vector<int> > &queries){
	int r = mat.size();
	int c = mat[0].size();
	vector<vector<int> > cumm(r+2, vector<int> (c+2, 0));
	for(int i=0; i<r; i++)
		for(int j=0; j<c; j++)
			cumm[i+1][j+1] = mat[i][j];
	//form a wrapper so that further calculations don't need edge cases.
	for(int i=0; i<r+2; i++){
		for(int j=0; j<c+2; j++){
			if(i==0 && j==0)
				continue;
			else if(i==0)
				cumm[i][j] += cumm[i][j-1];
			else if(j==0)
				cumm[i][j] += cumm[i-1][j];
			else
				cumm[i][j] += cumm[i][j-1] + cumm[i-1][j] - cumm[i-1][j-1];
		}
	}
	vector<int> ans;
	for(int i=0; i<queries.size(); i++){
		int x = queries[i][0];
		x++;
		int y = queries[i][1];
		y++;
		int k = queries[i][2];
		int numBlacks = 0;
		int size = 0;
		while(numBlacks <= k){
			int newSize = size+1;
			numBlacks = 0;
			if(x+newSize-1 < r+2 && y+newSize-1 < c+2 && x-newSize >= 0 && y-newSize >= 0){
				int tl_x, tl_y, tr_x, tr_y, bl_x, bl_y, br_x, br_y;
				tl_x = x-newSize, tl_y = y-newSize;
				tr_x = x-newSize, tr_y = y+newSize-1;
				bl_x = x+newSize-1, bl_y = y-newSize;
				br_x = x+newSize-1, br_y = y+newSize-1;
				numBlacks = cumm[br_x][br_y] - cumm[bl_x][bl_y] - cumm[tr_x][tr_y] + cumm[tl_x][tl_y];
			}
			else 
				break;
			if(numBlacks <= k)
				size++;
		}
		if (size==0)
			ans.push_back(0);
		else
			ans.push_back(2*size - 1);
	}
	return ans;
}

int main(){
	int x, y;
	cin >> x >> y;
	vector<vector<int> > mat(x, vector<int> (y, 0));
	int w;
	for(int i=0; i<x; i++){
		for(int j=0; j<y; j++){
			cin >> w;
			mat[i][j] = w;
		}
	}
	int q;
	cin >> q;
	vector<vector<int> > queries (q, vector<int> (3));
	for(int i=0; i<q; i++){
		cin >> x >> y >> w;
		queries[i][0] = x;
		queries[i][1] = y;
		queries[i][2] = w;
	}
	vector<int> ans = solve(mat, queries);
	for(int i=0; i<q; i++){
		cout << ans[i] << " ";
	}
	cout << endl;
	return 0;
}