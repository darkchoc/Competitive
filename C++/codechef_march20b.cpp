#include<bits/stdc++.h>

using namespace std;

int main(){
	int t; 
	cin >> t;
	for (int tt = 0; tt < t; tt++) {
		int m,n;
		cin >> n>> m;
		vector<int> f;
		vector<int> p;
		vector<int> total (m, 0);
		int x;
		for(int i=0; i<n; i++){
			cin >> x;
			f.push_back(x);
		}
		for(int i=0; i<n; i++){
			cin >> x; 
			p.push_back(x);
		}
		int ans = INT_MAX;
		for(int i=0; i<n; i++)
			total[f[i]-1]+=p[i];
		
		for(int i=0;i<m;i++)
			if(total[i]>0)
				ans = min(ans, total[i]);
			
			
		cout << ans << endl;
	}
	return 0;
}
