#include <bits/stdc++.h>

using namespace std;
int r, c, x, y;
vector<vector<char> > bar_;
vector<vector<int> > count_;
vector<vector<int> > dp;

int helper(int col, int color, int width){
    if(col==c){
        if(width==1 || (width-1>=x && width-1<=y))
                return 0;
        else
            return INT_MAX;
    }
    if(dp[color][col]!=-1)
            return dp[color][col];
    int cost = count_[1-color][col];
    if(width<x){
            int x = helper(col+1, color, width+1);
            if(x<INT_MAX)
                cost += x;
            else cost = INT_MAX;
    }
    else if(width==y){
            int x = helper(col+1, !color, 1);
            if(x<INT_MAX)
            cost += x;
            else cost = INT_MAX;
    }
    else{
        //width < y. We won't come across condition when width > y as we first check width = y in recursion
        int x = min(helper(col+1, color, width+1), helper(col+1, !color, 1));
        if(x<INT_MAX) 
            cost += x;
        else cost = INT_MAX;
    }
    dp[color][col]=cost;
    return dp[color][col];
}

int main(){
    cin >> r >> c >> x >> y;
    bar_.resize(r, vector<char> (c));
    count_.resize(2, vector<int> (c, 0));
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            cin >> bar_[i][j];
            if(bar_[i][j]=='#')
                count_[0][j]++;
            else
                count_[1][j]++;
        }
    }   
    dp.resize(2, vector<int> (c,-1));
    cout << min(helper(0, 0, 1), helper(0, 1, 1));
    return 0;
}
