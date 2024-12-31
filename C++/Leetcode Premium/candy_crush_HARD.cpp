/*
https://leetcode.ca/all/723.html
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> row = {0, -1, 0, 1};
vector<int> col = {-1, 0, 1, 0};

int apply_bfs_and_replace(vector<vector<int> > &candy, int i, int j, int replaceWith){
    int n = candy.size(), m = candy[0].size();
    int original = candy[i][j];
    queue<pair<int, int> > q;
    q.push(make_pair(i, j));
    int count = 1;
    candy[i][j]=replaceWith;
    while(!q.empty()){
        pair<int, int> p = q.front();
        q.pop();
        for(int k=0; k<4; k++){
            int newx = p.first + row[k];
            int newy = p.second + col[k];
            if(newx < n && newx >= 0 && newy < m && newy >= 0){
                if(candy[newx][newy]==original){
                    candy[newx][newy]=replaceWith;
                    q.push(make_pair(newx, newy));
                    count++;
                }
            }
        }
    }
    return count;
}

bool count_and_make_zero(vector<vector<int> > &candy, int i, int j){
    int original = candy[i][j];
    int count = apply_bfs_and_replace(candy, i, j, -1);
    if(count >= 3){
        apply_bfs_and_replace(candy, i, j, 0);
        return true;
    } else {
        apply_bfs_and_replace(candy, i, j, original);
        return false;
    }
}

bool crushable(vector<vector<int> > &candy){
    bool foundCrushableGroup = false;
    for(int i=0; i<candy.size(); i++){
        for(int j=0; j<candy[0].size(); j++){
            if(candy[i][j]!=0){
                foundCrushableGroup = foundCrushableGroup | count_and_make_zero(candy, i, j);
            }
        }
    }
    return foundCrushableGroup;
}

void settle(vector<vector<int> > &candy){
    for(int j=0; j<candy[0].size(); j++){
        int empty = candy.size()-1;
        for(int i=candy.size()-1; i>=0; i--){
            if(candy[i][j]!=0){
                swap(candy[i][j], candy[empty][j]);
                empty--;
            }
        }
    }
}

void wrong_solution(vector<vector<int> > candy){
    /*
    this solution is wrong because I'm assuming that if there are adjancent candies and they together make a group of 3 or more, I should crush them. But the question says that we can only crush when 3 or more candies are adjancent "either vertically or horizontally".
    So for a case like:
        1
        1
    1   1
        1
    This code will crush all ones, but actually only the 4 ones in vertical line should be crushed.
    */
    int n = candy.size();
    if(n==0) return;
    int m = candy[0].size();
    if(m==0) return;
    
    while(crushable(candy)){
        settle(candy);
    }
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
            cout << candy[i][j] << ", ";
        cout << endl;
    }
}

bool crush_vertically_or_horizontally(vector<vector<int> > &candy){
    /*
    We can iterate from top left to bottom right. For each cell that's not equal to 0, we need to check if it has 3 or more cells on it's left that are same as current cell, or if there are 3 or more cells below that it that are same as current cell. 
    Now, we don't want to make them -1 or 0 on the first go itself. For example, if we have:
    1 1 1 1
      1
      1
    Now on seeing first 1, we'll make all 4 ones in the row 0. But then we won't be crushing the 2 ones below the 2nd one. So we need to either mark them somehow to be made 0. One option is to keep collecting these indices and at the end make them all 0. Or, we can simply make the cell = -candy[i][j]. 

    Another option is that for each cell, we check if there are 3 or more cells either on top of it, below it, on left of it, or on right of it.. that are the same as current cell. If so, just mark the current cell to be made 0 later.

    Second approach is simpler.
    */
    int n = candy.size(), m = candy[0].size();
    bool foundCrushable = false;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(candy[i][j]==0) continue;

            // check if top 2 cells are same
            if(i>1 && abs(candy[i][j])==abs(candy[i-1][j]) && abs(candy[i][j])==abs(candy[i-2][j])){
                // mark these three for crushing
                candy[i][j] = candy[i-1][j] = candy[i-2][j] = -abs(candy[i][j]);
                foundCrushable = true;
            }
            // check if bottom 2 cells are same
            if(i+2 < n && abs(candy[i][j])==abs(candy[i+1][j]) && abs(candy[i][j])==abs(candy[i+2][j])) {
                candy[i][j] = candy[i+1][j] = candy[i+2][j] = -abs(candy[i][j]);
                foundCrushable = true;
            }
            // check left 2 cells
            if(j>1 && abs(candy[i][j])==abs(candy[i][j-1]) && abs(candy[i][j])==abs(candy[i][j-2])){ 
                candy[i][j] = candy[i][j-1] = candy[i][j-2] = -abs(candy[i][j]);
                foundCrushable = true;
            }
            // check right 2 cells
            if(j+2 < m && abs(candy[i][j])==abs(candy[i][j+1]) && abs(candy[i][j])==abs(candy[i][j+2])){
                candy[i][j] = candy[i][j+1] = candy[i][j+2] = -abs(candy[i][j]);
                foundCrushable = true;
            }
        }
    }

    if(!foundCrushable) return false;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
            if(candy[i][j]<0) candy[i][j] = 0;
    }
    return true;
}

void correct_solution(vector<vector<int> > candy){
    int n = candy.size();
    if(n==0) return;
    int m = candy[0].size();
    if(m==0) return;
    
    while(crush_vertically_or_horizontally(candy)){
        settle(candy);
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
            cout << candy[i][j] << ", ";
        cout << endl;
    }
}

int main() {
    // wrong_solution({{110,5,112,113,114},{210,211,5,213,214},{310,311,3,313,314},{410,411,412,5,414},{5,1,512,3,3},{610,4,1,613,614},{710,1,2,713,714},{810,1,2,1,1},{1,1,2,2,2},{4,1,4,4,1014}});
    correct_solution({{110,5,112,113,114},{210,211,5,213,214},{310,311,3,313,314},{410,411,412,5,414},{5,1,512,3,3},{610,4,1,613,614},{710,1,2,713,714},{810,1,2,1,1},{1,1,2,2,2},{4,1,4,4,1014}});
}