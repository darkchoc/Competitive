/*
You are given an array of N positive integers, A1, A2 ,…, AN.   

Also, given a Q updates of form:

i j: Update Ai = j. 1 ≤ i ≤ N.

Perform all updates and after each such update report mode of the array. Therefore, return an array of Q elements, where ith element is mode of the array after ith update has been executed.

Notes

Mode is the most frequently occuring element on the array.
If multiple modes are possible, return the smallest one.
Update array input is via a Q*2 array, where each row represents a update.
For example,

A=[2, 2, 2, 3, 3]

Updates=    [ [1, 3] ]
            [ [5, 4] ]
            [ [2, 4] ]

A = [3, 2, 2, 3, 3] after 1st update.
3 is mode.

A = [3, 2, 2, 3, 4] after 2nd update.
2 and 3 both are mode. Return smaller i.e. 2.

A = [3, 4, 2, 3, 4] after 3rd update.
3 and 4 both are mode. Return smaller i.e. 3.

Return array [3, 2, 3].
Constraints    

1 ≤ N, Q ≤ 105    

1 ≤ j, Ai ≤ 109

*/


/*
More notes:

https://stackoverflow.com/a/44922917 check this out as well. 
I used a set with custom comparator to make it act like a max heap but without repeatition.

But in the above link, the guy has used priority queue with custom comparator. To tackle the issue of
updating values in priorityqueue as well as erasing faulty ones, he thought a very creative way.
He just fetched the top element of priority queue and sees if it is valid or not, using the map of frequencies.
If it is valid, well and good, otherwise just ignore the entry and pop it from the priority queue. 
What a beautiful way to simplify a problem. 
*/

#include <bits/stdc++.h>

using namespace std;

bool cmp(const pair<int, int> &a, const pair<int, int> &b){
	if(a.first != b.first)
		return a.first > b.first; //frequency more than this element
	else return a.second < b.second; //if equal frequency, then the number that is smaller should be first
}

vector<int> solve(vector<int> &A, vector<vector<int> > &B){
	int n = A.size();
	map<int, int> mp;
	for(int i=0; i<n; i++)
		mp[A[i]]++;
	set<pair<int, int> , decltype(cmp)*> s(cmp); 
	for(map<int, int>::iterator it=mp.begin(); it!=mp.end(); it++)
		s.insert(make_pair(it->second, it->first));
	vector<int> ans;
	for(int i=0; i<B.size(); i++){
		int current_val = A[B[i][0]-1];
		int new_val = B[i][1];
		//update value in A
		A[B[i][0]-1] = new_val;
		//remove values in map and set for old value
		pair<int, int> oldpair = make_pair(mp[current_val], current_val);
		s.erase(oldpair);
		if(mp[current_val]==1)
			mp.erase(current_val);
		else{
			mp[current_val]--;
			s.insert(make_pair(mp[current_val], current_val));
		}
		//remove old value of new value if new value was already present in array
		if(mp.find(new_val)!=mp.end())
			s.erase(make_pair(mp[new_val], new_val));
		//insert new value in map and set
		mp[new_val]++;
		s.insert(make_pair(mp[new_val], new_val));
		ans.push_back((*s.begin()).second);
	}
	return ans;
}

int main(){
	int n;
	cin >> n;
	int x, y;
	vector<int> A;
	for(int i=0; i<n; i++){
		cin >> x;
		A.push_back(x);
	}
	vector<vector<int> > B;
	int q;
	cin >> q;
	for(int i=0; i<q; i++){
		cin >> x >> y;
		vector<int> query;
		query.push_back(x);
		query.push_back(y);
		B.push_back(query);
	}
	vector<int> ans = solve(A, B);
	for(int i=0; i<ans.size(); i++)
		cout << ans[i] << " ";
	cout << endl;
	return 0;
}

