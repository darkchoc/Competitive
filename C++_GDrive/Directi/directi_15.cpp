/*
https://discuss.codechef.com/t/directi-hiring-question/12517
Given two strings with underscore, convert first to second given following constraints:
You can change swap underscore with adjacent letters
You can swap underscore(i) with i+2, if i+1 and i+2 are different.
You can swap underscore(i) with i-2, if i-1 and i-2 are different.
*/

#include <bits/stdc++.h>
using namespace std;

int helper(string A, string B){
	map<string, int> mp;
	queue<pair<string, int> > q;
	int underscore;
	for(int i=0; i<A.length(); i++)
		if(A[i]=='_'){
			underscore=i;
			break;
		}
	q.push(make_pair(A, underscore));
	mp[A]=0;
	while(!q.empty()){
		pair<string, int> p = q.front();
		q.pop();
		string current = p.first;
		int pos = p.second;
		cout << "Current = " << current << " pos=" << pos << endl;
		if(current==B)
			return mp[current];
		//first
		if(pos>0){
			swap(current[pos-1], current[pos]);
			if(mp.find(current)==mp.end()){
				q.push(make_pair(current, pos-1));
				mp[current] = mp[p.first]+1;
			}
			swap(current[pos-1], current[pos]);
		}
		if(pos<A.length()-1){
			swap(current[pos+1], current[pos]);
			if(mp.find(current)==mp.end()){
				q.push(make_pair(current, pos+1));
				mp[current] = mp[p.first]+1;
			}
			swap(current[pos+1], current[pos]);
		}
		if(pos<A.length()-2){
			if(current[pos+1]!=current[pos+2]){
				swap(current[pos], current[pos+2]);
				if(mp.find(current)==mp.end()){
					q.push(make_pair(current, pos+2));
					mp[current] = mp[p.first]+1;
				}
				swap(current[pos], current[pos+2]);
			}
		}
		if(pos>1){
			if(current[pos-1]!=current[pos-2]){
				swap(current[pos], current[pos-2]);
				if(mp.find(current)==mp.end()){
					q.push(make_pair(current, pos-2));
					mp[current] = mp[p.first]+1;
				}
				swap(current[pos], current[pos-2]);
			}
		}
	}
	return -1;
}

int main(){
	string a, b;
	cin >> a >> b;
	cout << helper(a,b) << endl;
	return 0;
}