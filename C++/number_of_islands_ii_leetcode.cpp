/*
Question: https://leetcode.ca/all/305.html

A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land. Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example:

Input: m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]]
Output: [1,1,2,3]
Explanation:

Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

0 0 0
0 0 0
0 0 0
Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

1 0 0
0 0 0   Number of islands = 1
0 0 0
Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

1 1 0
0 0 0   Number of islands = 1
0 0 0
Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

1 1 0
0 0 1   Number of islands = 2
0 0 0
Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

1 1 0
0 0 1   Number of islands = 3
0 1 0
Follow up:

Can you do it in time complexity O(k log mn), where k is the length of the positions?
*/

#include <bits/stdc++.h>
using namespace std;

int getParent_approach1(int x, vector<int> &parent){
    while(x!=parent[x]){
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void doUnion_approach1(int x, int y, int newx, int newy, vector<int> &parent, int &connectingUniqueIslands, int &n){
    int uParent = getParent_approach1(x*n + y, parent);
    int vParent = getParent_approach1(newx*n + newy, parent);
    if(uParent != vParent){
        connectingUniqueIslands++;
        parent[uParent] = vParent;
    }
}

void solve_approach1(int m, int n, vector<vector<int> > addLand){
    int islands = 0;
    vector<vector<int> > grid (m, vector<int> (n, 0));  //pixel[i][j] = 0 -> water, 1 -> land
    vector<int> parent;
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            parent.push_back(i*n + j);

    vector<int> numIslands;
    vector<int> row = {0,-1,0,1};
    vector<int> col = {-1,0,1,0};
    for(int i=0; i<addLand.size(); i++){
        int x = addLand[i][0], y = addLand[i][1];
        grid[x][y] = 1;
        int connectingUniqueIslands = 0;
        int indexInParentArray = x*n + y;
        for(int j=0; j<4; j++){
            int newx = x + row[j], newy = y + col[j];
            if(newx >=0 && newx < m && newy >= 0 && newy < n && grid[newx][newy]==1){
                int indexOfNeighbourInParentArray = newx*n + newy;
                doUnion_approach1(x, y, newx, newy, parent, connectingUniqueIslands, n);
            }
        }
        if(connectingUniqueIslands == 0){
            //means connected to no island
            islands++;
        } else {
            islands -= (connectingUniqueIslands-1);
        }
        numIslands.push_back(islands);
    }
    for(int i=0; i<numIslands.size(); i++)
        cout << numIslands[i] << " ";
    cout << endl;
}

void solve_approach2(int m, int n, vector<vector<int> > addLand){
    vector<int> parent (m*n, -1); //we can use parent array itself as grid. If -1 -> water. If >= 0, land
    vector<int> numIslands;
    int islands = 0;
    vector<int> row = {0, -1, 0, 1};
    vector<int> col = {-1, 0, 1, 0};
    for(int i=0; i<addLand.size(); i++){
        int x = addLand[i][0], y = addLand[i][1];
        parent[x*m + y] = x*n + y; //initializing as its own parent.
        int connectingUniqueIslands = 0;
        for(int j=0; j<4; j++){
            int newx = x + row[j];
            int newy = y + col[j];
            if(newx >= 0 && newx < m && newy >= 0 && newy < n && parent[newx*n + newy]!=-1){
                doUnion_approach1(x, y, newx, newy, parent, connectingUniqueIslands, n);
            }
        }
        if(connectingUniqueIslands==0)
            islands++;
        else
            islands -= (connectingUniqueIslands - 1);
        numIslands.push_back(islands);
    }

    for(int i=0; i<numIslands.size(); i++)
        cout << numIslands[i] << " ";
    cout << endl;
}

int main(){
    solve_approach1(3, 3, {{0,0},{0,1},{1,2},{2,1},{1,1}});
    solve_approach1(5, 5, {{0,0},{0,2},{1,1},{1,2},{2,4},{3,3},{3,1},{2,2},{3,2},{1,4},{4,4},{3,4}});
    solve_approach2(3, 3, {{0,0},{0,1},{1,2},{2,1},{1,1}});
    solve_approach2(5, 5, {{0,0},{0,2},{1,1},{1,2},{2,4},{3,3},{3,1},{2,2},{3,2},{1,4},{4,4},{3,4}});
}