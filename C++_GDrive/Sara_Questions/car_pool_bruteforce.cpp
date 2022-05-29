#include <bits/stdc++.h>

using namespace std;

void recurse(vector<pair<int, int> > &drivers, vector<int> &passengers, vector<bool> &occupied, int &ans,
	         int curr_pass, int curr_ans, int &flag){
	if(flag==1)
		return;
	if(curr_pass == passengers.size()){
		if(ans==passengers.size()) flag=1;
		return;
	}
	for(int i=0; i<occupied.size() && flag==0; i++){
		if(drivers[i].first > passengers[curr_pass]){
			//no need to check further, as all will have starting dist greater than passenger_dist
			recurse(drivers, passengers, occupied, ans, curr_pass+1, curr_ans, flag);
			break;
		}
		else if (occupied[i]==true){ //drivers[i].first <= passengers[curr_pass]
			//move ahead in this case, check next driver as this already occupied
			continue;
		}
		else if(drivers[i].second < passengers[curr_pass]) { //drivers[i].first <= passengers[curr_pass], occupied[i]==false
			//move ahead as ending dist of driver is less than reqd dist, check next driver
			continue;
		}
		else{ //passenger dist within range of this driver, and driver not occupied
			occupied[i]=true;
			ans = max(ans, curr_ans+1);
			recurse(drivers, passengers, occupied, ans, curr_pass+1, curr_ans+1, flag);
			occupied[i]=false;
		}
	}
	return;
}

int helper(vector<pair<int, int> > &drivers, vector<int> &passengers){
	vector<bool> occupied(drivers.size(), false);
	int ans = 0, flag=0;
	recurse(drivers, passengers, occupied, ans, 0, 0, flag);
	return ans;
}

int main(){
	int test;
	cin >> test;
	for(int t=1; t<=test; t++){
		int n, m;
		cin >> n >> m;
		vector<int> passengers;
		vector<pair<int, int> > drivers;
		int x, y;
		for(int i=0; i<n; i++){
			cin >> x;
			passengers.push_back(x);
		}
		sort(passengers.begin(), passengers.end());
		for(int i=0; i<m; i++){
			cin >> x >> y;
			if(n!=0 && (x>passengers[n-1] || y<passengers[0])) continue;
			drivers.push_back(make_pair(x,y));
		}
		sort(drivers.begin(), drivers.end());
		if(n==0 || drivers.size()==0)
			cout << 0 << endl;
		else{
			cout << helper(drivers, passengers) << endl;
		}
	}
	return 0;
}