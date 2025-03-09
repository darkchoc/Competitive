/*
You want to build a house on an empty land which reaches all buildings in the shortest amount of distance. You can only move up, down, left and right. You are given a 2D grid of values 0, 1 or 2, where:

Each 0 marks an empty land which you can pass by freely.
Each 1 marks a building which you cannot pass through.
Each 2 marks an obstacle which you cannot pass through.
Example:

Input: [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]

1 - 0 - 2 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0

Output: 7

Explanation: Given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2),
             the point (1,2) is an ideal empty land to build a house, as the total
             travel distance of 3+3+1=7 is minimal. So return 7.
Note:
There will be at least one building. If it is not possible to build such house according to the above rules, return -1.

Example 2:

Input: grid = [[1,0]]
Output: 1
Example 3:

Input: grid = [[1]]
Output: -1
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 50
grid[i][j] is either 0, 1, or 2.
There will be at least one building in the grid.

*/

/*
Thoughts: Create new grid where each cell stores (distance, buildingsReachable) pair. From each building,
do a BFS (will also need to initialize a new visited set for each BFS) and calculate distance of each cell from it.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

void bfs(int x, int y, vector<vector<int> > &grid, vector<vector<int> > &dist, vector<vector<int> > &count) {
    queue<pair<int, int> > q;
    set<pair<int, int> > visited;
    vector<int> row = {0, -1, 0, 1};
    vector<int> col = {-1, 0, 1, 0};
    q.push(make_pair(x, y));
    visited.insert(make_pair(x, y));
    int level=0;
    while(!q.empty()){
        int n = q.size();
        while(n){
            pair<int, int> p = q.front();
            q.pop();
            for(int i=0; i<4; i++){
                int newx = p.first + row[i];
                int newy = p.second + col[i];
                if(newx>=0 && newx < grid.size() && newy>=0 && newy<grid[0].size()){
                    if(grid[newx][newy]==0 && visited.find(make_pair(newx, newy))==visited.end()){
                        visited.insert(make_pair(newx, newy));
                        count[newx][newy]++;
                        dist[newx][newy]+= (level+1);
                        q.push(make_pair(newx, newy));
                    }
                }
            }
            n--;
        }
        level++;
    }
    return;
}

int solve(vector<vector<int> > grid) {
    int n = grid.size();
    if(n==0) return 0;
    int m = grid[0].size();
    vector<vector<int> > dist (n, vector<int> (m, 0));
    vector<vector<int> > count (n, vector<int> (m, 0));
    // do bfs from each building and also keep count of number of buildings
    int buildings = 0;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(grid[i][j]==1){
                bfs(i, j, grid, dist, count);
                buildings++;
            }
    // find shortest dist for a cell that is reachable by all buildings
    int shortestDist = INT_MAX;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(count[i][j]==buildings)
                shortestDist = min(shortestDist, dist[i][j]);
    if(shortestDist!=INT_MAX) return shortestDist;
    // I was thinking what if shortest distance actually adds up to be INT_MAX ? Well that won't 
    // ever happen because of the contraints given.
    return -1;
}

int main(){
    cout << solve({{1,0,2,0,1},{0,0,0,0,0},{0,0,1,0,0}}) << endl; // 7
    cout << solve({{1,0}}) << endl; // 1
    cout << solve({{1}}) << endl; // -1
}