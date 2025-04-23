/*
https://leetcode.com/discuss/post/6671317/meta-banglore-rejection-by-anonymous_use-8q0l/

Shortest path in binary matrix. Print the path
0 -> can travel through this. 1 -> blocked

Adjacent - all 8 sides

n x n matrix

*/

/*
Thoughts: while applying bfs, also keep track of who the parent was. To keep track of parent, either we can have a map, or we can have another grid
with pair<int, int>  as the element, that will keep track of who the parent is. 
I think I'll go with map solution.
*/

#include <iostream>
#include <map>
using namespace std;


void calculateAndPrintShortestPath(map<pair<int, int>, pair<int, int> > &parent, int n) {
    int x = n-1;
    int y = n-1;
    pair<int, int> p = make_pair(x, y);
    vector<pair<int, int> > path;
    path.push_back(p);
    while(parent.find(p)!=parent.end()){
        path.push_back(parent[p]);
        p = parent[p];
    }
    reverse(path.begin(), path.end());
    for(int i=0; i<path.size(); i++){
        cout << "[" << path[i].first << ", " << path[i].second << "], ";
    }
    cout << endl;
    return;
}

void printShortestPath(vector<vector<int> > grid) {
    int n = grid.size(); 
    if(n==0) {
        cout << -1 << endl;
        return;
    }
    if(grid[0].size()==0) {
        cout << -1 << endl;
        return;
    }
    if(grid[0][0]==1 || grid[n-1][n-1]==1) {
        cout << -1 << endl;
        return;
    }
    if(n==1 && grid[0][0]==0) {
        cout << "[0, 0]" << endl;
        return;
    }

    vector<int> row = {0, -1, -1, -1, 0, 1, 1, 1};
    vector<int> col = {-1, -1, 0, 1, 1, 1, 0, -1};
    
    map<pair<int, int>, pair<int, int> > parent;
    queue<pair<int, int> > q;
    q.push(make_pair(0, 0));
    grid[0][0]=2;
    while(!q.empty()){
        int qSize = q.size();
        while(qSize) {
            pair<int, int> p = q.front();
            q.pop();
            int x = p.first;
            int y = p.second;
            for(int i=0; i<8; i++){
                int newx = x + row[i];
                int newy = y + col[i];
                if(newx==n-1 && newy==n-1) {
                    parent[make_pair(newx, newy)] = make_pair(x, y);
                    calculateAndPrintShortestPath(parent, n);
                    return;
                }
                if(newx>=0 && newx<n && newy>=0 && newy<n && grid[newx][newy]==0) {
                    grid[newx][newy]=2;
                    parent[make_pair(newx, newy)] = make_pair(x, y);
                    q.push(make_pair(newx, newy));
                }
            }
            qSize--;
        }
    }
    cout << "-1" << endl;
    return;
}

int main() {
    printShortestPath({}); // -1
    printShortestPath({{}}); // -1
    printShortestPath({{0}}); // 1
    printShortestPath({{1, 0}, {0, 0}}); // -1
    printShortestPath({{0, 0}, {0, 1}}); // -1
    printShortestPath({{0, 1}, {1, 0}}); // 2
    printShortestPath({{0,0,1}, {1, 0, 0}, {1, 1, 0}}); // 3
    printShortestPath({{0, 0, 1, 1}, {1, 0, 1, 1}, {0, 1, 1, 1}, {0, 0, 0, 0}}); // 6
    printShortestPath({{0, 0, 1, 1}, {1, 0, 1, 1}, {0, 1, 1, 1}, {0, 1, 0, 0}}); // -1
}