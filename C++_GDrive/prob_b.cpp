//Second submission after seeing editorial. 
//The first submission is also nice. The way it figures out how many steps to reach
// next number from current, given a digit, is nice. It calculates i and j index, and then
//sees if i>j or otherway and then returns the appropriate answer.

#include <bits/stdc++.h>
using namespace std;

int main(){
	string s;
	cin >> s;
	vector<vector<int> > counts(10, vector<int> (10, 0));
	for(int i=1; i<s.length(); i++){
		counts[s[i-1]-'0'][s[i]-'0']++;
	}

	for(int x=0; x<10; x++){
		for(int y=0; y<10; y++){
			vector<vector<int> > dist(10, vector<int> (10, INT_MAX));
			for(int a=0; a<10; a++){
				for(int times_x=0; times_x<10; times_x++){
					for(int times_y=0; times_y<10; times_y++){
						if(times_x==0 && times_y==0){ //Important step I missed in previous submission. We need at least one of
							//them to be non-zero
							continue;
						}
						int b = (a + times_x*x + times_y*y)%10;
						dist[a][b] = min(dist[a][b], times_y+times_x);
					}
				}
			}

			int res = 0;
			for(int i=0; i<10; i++){
				for(int j=0; j<10; j++){
					if(dist[i][j]==INT_MAX && counts[i][j]>0){
						res = -1;
						break;
					}
					res += counts[i][j]*(dist[i][j]-1);
				}
				if(res==-1)
					break;
			}
			cout << res;
			if(y==9)
				cout << endl;
			else
				cout << " ";
		}
	}
	return 0;
}