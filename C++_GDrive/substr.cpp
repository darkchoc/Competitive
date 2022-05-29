#include <bits/stdc++.h>
#include <iomanip>
using namespace std;
int dp[305][305][305];
int a[]={0,0,1,-1};
int b[]={1,-1,0,0};
 
bool isValid(int x,int y, int n,int m){
    if(x>=0 && x<n && y>=0 && y<m)
        return true;
    return false;
}
 
 
int helper(int x,int y,int A, vector<vector<int> > &B ){
    if(!isValid(x,y,B.size(),B[0].size())){
        return 0;
    }
    if(A<0)
        return 0;
    if(dp[x][y][A]!=-1)
        return dp[x][y][A];
    for(int i=0;i<4;i++){
        for(int k=0; k<A; k++)
        	dp[x][y][A] = max(dp[x][y][A],helper(x+a[i],y+b[i],k,B));
    }
    return dp[x][y][A];
}
 

vector<vector<int> > solve(int A, vector<vector<int> > &B) {
    int n = B.size();
    int m = B[0].size();
    memset(dp,-1,sizeof(dp));
    for(int i = 0;i<n;i++){
        for(int j=0;j<m;j++){
            dp[i][j][0] = B[i][j];
        }
    }
    vector<vector<int> > sol(n,vector<int>(m,0));
 
    for(int i = 0;i<sol.size();i++){
        for(int j=0;j<sol[0].size();j++){
           dp[i][j][A] = helper(i,j,A,B);
           sol[i][j] =  dp[i][j][A];
        }
    }

    //for(int i=0; i<sol.size(); i++)
	//for(int j=0; j<sol[0].size(); j++)
	//    for(int k=0; k<=A; k++)
	//	sol[i][j]=max(sol[i][j], dp[i][j][k]);

    return sol;

}

int main()
{
	vector<vector<int> > input;
	input.resize(2, vector<int> (3));
	input[0][0]=1;
	input[0][1]=2;
	input[0][2]=4;
	input[1][0]=4;
	input[1][1]=5;
	input[1][2]=8;
	vector<vector<int> > res = solve(2, input);	
	for(int i=0; i<res.size(); i++){
		for(int j=0; j<res[0].size(); j++){
			cout << res[i][j] << " " ;
		}
		cout << endl;
	}
	return 0;

}
