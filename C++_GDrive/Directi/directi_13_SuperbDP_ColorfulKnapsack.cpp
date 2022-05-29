/*
Third question here: https://www.geeksforgeeks.org/directi-interview-experience-set-15-on-campus-2/
https://discuss.codechef.com/t/colorful-knapsack-problem-directi-interview/19980
*/


/*
EXPLANATION:
First, we make a 2D array. The first list is weights of stones of colour 0 (0 based indexing for colors). 
Second list is weights of stones with color 1.
In all, we have M lists, for m colours.

Now, dp[i][j] gives the max weight possible with i stones (1 of each of the colors from 0 to i),
and when capacity is j.

So for filling this dp array, we fill colorwise. 
For the first colors, we simply check the weight of 
heaviest stone for color 0 weighing less than j. 

Now for filling other rows, we first pick color i. We already have information about
the maximum weight that we can get by taking stones upto i-1 color, and with max weight j.
if dp[i-1][j] is -1, it means we cannot take one stone each of color 0 to i-1 and have combined
weight less than j. 

So once we have picked the color i, we pick each stone of this color one by one. 
Now for each of these stones, we check for each weight. 
If we have dp[i-1][j-weight_of_picked_stone]!=-1, then we can add this stone to the combination.
So we get at least one combination to make dp[i][j]. Here, j is capacity, not weight. 
So dp[i-1][j-weight_of_picked_stone]!=-1 means that it must have some value, lets say x. 
Let y = j-weight_of_picked_stone. Then we know x<=y. dp[i-1][y] gives value of max weight that we can get 
using 1 stone from each of 0 to i-1 color.  
Now we pick another stone of the same color, let's say it's weight is w2. We check if we had some
combination of stones uptil i-1 weighing <= j-w2. So if dp[i-1][w2]!=-1, we again get another 
combination for dp[i][j]. But we see if previous combination's combined weight is more, then we keep it, otherwise,
we update it with new value for dp[i][j], that we just got. 

*/
#include <bits/stdc++.h>
using namespace std;

int helper(vector<vector<int> > &stones, int n, int m, int k){
	vector<vector<int> > dp(m, vector<int> (k+1, -1));
	for(int w=1; w<=k; w++){
		for(int s_m=0; s_m<stones[0].size(); s_m++){
			if(w>=stones[0][s_m])
				dp[0][w]=max(dp[0][w], stones[0][s_m]);
		}
	}
	for(int c=1; c<m; c++){
		for(int s_m=0; s_m<stones[c].size(); s_m++){
			for(int w=0; w<=k; w++){
				if(stones[c][s_m]>w)
					continue;
				else{
					if(dp[c-1][w-stones[c][s_m]]!=-1){
						dp[c][w] = max(dp[c][w], 
									   dp[c-1][w-stones[c][s_m]]+stones[c][s_m]);
								// , dp[c][w-stones[c][s_m]] +  stones[c][s_m]; // if instead of exactly one, we need at least 1
					}
				}
			}
		}
	}
	return dp[m-1][k];
}

int main(){
	int test;
	cin >> test;
	for(int t=0; t<test; t++){
		int n, m, k;
		cin >> n >> m >> k;
		vector<int> weights(n);
		vector<int> colors(n);
		for(int i=0; i<n; i++)
			cin >> weights[i];
		for(int i=0; i<n; i++)
			cin >> colors[i];
		vector<vector<int> > stones(m);
		for(int i=0; i<n; i++){
			stones[colors[i]-1].push_back(weights[i]);
		}
		cout << helper(stones, n, m, k) << endl;
	}
}
