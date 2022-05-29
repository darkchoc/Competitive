/*
Wrong code as doesn't work for cases like:
P: 3, 5, 10 , 15
D: {3,9},{3,15},{4,6},{9,11}
Ans = 4

P: 3, 5, 10, 15
D: {3,11}, {3,15}, {4,6}, {9,9}
Ans = 3
*/

#include <bits/stdc++.h>

using namespace std;

int helper(vector<int> &passengers, int n, vector<pair<int, int> > &drivers, int m){
	vector<pair<int, int> > all;
	for(int i=0; i<n; i++){
		all.push_back(make_pair(passengers[i],1));
	}
	for(int i=0; i<m; i++){
		all.push_back(make_pair(drivers[i].first, 0));
		all.push_back(make_pair(drivers[i].second, 2));
	}
	sort(all.begin(), all.end());
	stack<pair<int, int> > st;
	int i=1;
	int s = all.size();
	st.push(all[0]);
	int to_remove_extra_open_drivers=0;
	int ans = 0;
	while(i<s){
		if(all[i].second==0){
			//opening of driver
			st.push(all[i]);
			i++;
		}
		else if(all[i].second==1){
			//passenger
			st.push(all[i]);
			i++;
		}
		else{
			//closing of driver
			pair<int, int> p = st.top();
			if(p.second==1){
				st.pop();
				ans++;
				if(st.top().second==1)
					to_remove_extra_open_drivers++;
				else{
					while(to_remove_extra_open_drivers && st.top().second==0){
						st.pop();
						to_remove_extra_open_drivers--;
					}
					if(st.top().second==1)
						to_remove_extra_open_drivers++;
					else
						st.pop();
				}
			}
			else if(p.second==0){
				st.pop();
			}
			else{
				//not possible
				continue;
			}
			i++;
		}
	}
	return ans;
}


int main(){
	int test;
	cin >> test;
	for(int t=1; t<=test; t++){
		int n, m;
		cin >> n >> m;
		vector<int> passengers;
		int x, y;
		for(int i=0; i<n; i++){
			cin >> x;
			passengers.push_back(x);
		}
		sort(passengers.begin(), passengers.end());
		vector<pair<int, int> > drivers;
		for(int i=0; i<m; i++){
			cin >> x >> y;
			if(n!=0 && (y<passengers[0] || x>passengers[n-1]))
				continue;
			drivers.push_back(make_pair(x, y));
		}
		if(n==0 || drivers.size()==0)
			cout << 0 << endl;
		else
			cout << helper(passengers, n, drivers, drivers.size()) << endl;
	}
	return 0;
}