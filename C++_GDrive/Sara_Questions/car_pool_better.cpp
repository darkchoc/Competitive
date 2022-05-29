/*
Car Pool Question:
Given n passengers, who want to go to certain distances (1 <= dist <= 10^9)
Given m drivers who are willing to go in the range (x, y) where (1<=x<=y<=10^9)
A driver can satisfy only one passenger, ie. one passenger can be mapped to only one driver and one driver 
can be mapped to only one passenger, provided driver can serve the passenger.
n and m can be different
Find maximum passengers that can be served.

4 4
P: 3, 5, 10 , 15
D: {3,9},{3,15},{4,6},{9,11}
Ans = 4

4 4
P: 3, 5, 10, 15
D: {3,11}, {3,15}, {4,6}, {9,9}
Ans = 3
*/

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>

using namespace std;

int helper(vector<int> &passengers, int n, vector<pair<int, int> > &drivers, int m){
	set<int> numbers;
	for(int i=0; i<n; i++)
		numbers.insert(passengers[i]);
	for(int i=0; i<m; i++){
		numbers.insert(drivers[i].first);
		numbers.insert(drivers[i].second);
	}
	//numbers contains all unique distance values.
	//Max unique values will be 10000*3. Map them to numbers starting from 0, 
	//as we are only concerned if passenger falls within range of driver, not
	// by how long is the range of driver and where the passenger actually wants to go. 

	map<int, int> mp;
	int c=0;
	for(set<int>::iterator it=numbers.begin(); it!=numbers.end(); it++){
		mp[*it]=c;
		c++;
	}
	//c is now 1 more than the last mapping.
	for(int i=0; i<n; i++)
		passengers[i]=mp[passengers[i]];
	for(int i=0; i<m; i++){
		drivers[i].first = mp[drivers[i].first];
		drivers[i].second = mp[drivers[i].second];
	}
	int ans = 0, d=0, p=0;
	multiset<int> available; // multiset as there can be multiple equivalent values. Basically, a min-heap.
	//start passing over the distances one by one. 
	for(int i=0; i<c; i++){
		//remove drivers' end times whose range has ended
		//+1 because end times were inclusive. So in order to remove a driver, we gotta remove it at dist=end+1 and not dist=end
		while(!available.empty() && ((*available.begin())+1)<=i)
			available.erase(available.begin());

		//add drivers whose range is starting from here
		while(d<m && drivers[d].first==i){
			available.insert(drivers[d].second);
			d++;
		}
		while(p<n && passengers[p]==i){
			if(available.empty())
				p++;
			else{
				ans++;
				available.erase(available.begin());
				p++;
			}
		}
	}
	return ans;
}

void terminalinput(){
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
		else{
			sort(drivers.begin(), drivers.end());
			cout << helper(passengers, n, drivers, drivers.size()) << endl;
		}
	}
}

//For testing purpose to read input from file.
void fileinput(int argc, char *argv[]){
	string filein = argv[1];
	ifstream myfile(filein);
	int test;
	if(myfile.is_open()){
		myfile >> test;
		for(int t=0; t<test; t++){
			int n, m;
			myfile >> n >> m;
			vector<int> passengers;
			int x, y;
			for(int i=0; i<n; i++){
				myfile >> x;
				passengers.push_back(x);
			}
			sort(passengers.begin(), passengers.end());
			vector<pair<int, int> > drivers;
			for(int i=0; i<m; i++){
				myfile >> x >> y;
				if(n!=0 && (y<passengers[0] || x>passengers[n-1]))
					continue;
				drivers.push_back(make_pair(x, y));
			}
			if(n==0 || drivers.size()==0)
				cout << 0 << endl;
			else{
				sort(drivers.begin(), drivers.end());
				cout << helper(passengers, n, drivers, drivers.size()) << endl;
			}
		}
		myfile.close();
	}
	return;
}

int main(int argc, char* argv[]){
	//fileinput(argc, argv); //comment out when using terminal to provide input.
	terminalinput(); //comment out when using file to provide input.
	return 0;
}