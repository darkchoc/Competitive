#include <bits/stdc++.h>
using namespace std;

vector<vector<vector<vector<int> > > > dp;

//dp[i][j][k][c] means num1=i, num2=j, num3=k, and chances = c

int helper(int a, int b, int c, int chances){
	if(dp[a][b][c][chances]!=-1)
		return dp[a][b][c][chances];
	if((a==b || b==c || c==a) && chances!=0){
		dp[a][b][c][chances]=0;
		return dp[a][b][c][chances];
	}
	if(chances==12){
		dp[a][b][c][chances]=1;
		return 1;
	}
	//scene 1 (a,b)
	int a1 = min(2*a, b-a);
	int b1 = max(2*a, b-a);
	int x = helper(min(a1,c), a1+b1+c-min(a1, c)-max(b1,c), max(b1, c), chances+1);
	if(x==0){
		dp[a][b][c][chances]=0;
		return 0;
	}
	//scene 2 (a,c)
	a1 = min(2*a, c-a);
	int c1 = max(2*a, c-a);
	int y = helper(min(a1,b), a1+b+c1-min(a1, b)-max(b,c1), max(b, c1), chances+1);
	if(y==0){
		dp[a][b][c][chances]=0;
		return 0;
	}
	//scene 3 (b,c)
	b1 = min(2*b, c-b);
	c1 = max(2*b, c-b);
	int z = helper(min(a,b1), a+b1+c1-min(a, b1)-max(a,c1), max(a,c1), chances+1);
	if(z==0){
		dp[a][b][c][chances]=0;
		return 0;
	}
	dp[a][b][c][chances]=1;
	return 1;
}

int main(){
	bool flag = false;
	dp.clear();
	dp.resize(751, vector<vector<vector<int> > > (751, vector<vector<int> > (751, vector<int> (13, -1))));
	for(int i=1; i<248; i++){
		for(int j=i; j<249; j++){
			for(int k=j; k<250; k++){
				int x = helper(i, j, k, 0);
				if(x==1){
					flag=true;
					cout << i << " " << j << " " << k << endl;
					break;
				}
			}
			if(flag)
				break;
		}
		if(flag)
			break;
	}
	return 0;
}