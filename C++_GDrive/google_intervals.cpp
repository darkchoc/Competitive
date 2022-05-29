/*Given intervals sorted according to start times. Some are important, and some aren't.
Merge the overlapping intervals. If at point there is important as well as 
unimportant interval, then that point should be important.

Example: {1,3},{2,4},{5,9},{6,7},{8,13},{11,14},{13,16},{15,18}
		   0.    0.    1.    0.    0.     1.       1.      0
	Ans: {1,4},{5,9},{10,10},{11,16},{17,18}

Example 2: {1,5},{2,11},{8,9}
			 1.     0.    1.  
	Correct Ans: {1,5},{6,7},{8,9},{10,11}
	My current ans: {1,5},{6,7},{8,9}
	This type of case is not being handled currently where an unimportant interval split in such a way
	that part of it might go on the other side of the important interval.

Example 2: {1,8},{2,5},{6,11},{8,9},{14,17},{17,20},{19,23},{20,28},{24,27},{26,28},{30,34},{33,36},{34,40},{38,41},{43,48},{45,50}
             0.    1.     1.    0.     0.      1.      0.      1.      1.      0.      1.     0.       0.      1.      0.      1. 
     Ans: {1,1},{2,5},{6,11},{14,16},{17,28},{30,34},{35,37},{38,41},{43,44},{45,50}

*/

#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int> > combineImportantIntervals(vector<pair<int, int> > &intervals, vector<bool> &important,
	vector<bool> &imp_intermediate){
	vector<pair<int, int> > ret;
	int n = intervals.size();
	int i=0;
	while(i<n && important[i]==0){
		ret.push_back(intervals[i]);
		imp_intermediate.push_back(false);
		i++;
	} 
	pair<int, int> temp = intervals[i];
	int k = i+1; //interval right after the temp interval created so far
	int j=i+1; //current interval in consideration
	while(j<n){
		while(j<n && important[j]==0)
			j++;
		if(j==n){
			ret.push_back(temp);
			imp_intermediate.push_back(true);
			while(k<n){
				ret.push_back(intervals[k]);
				imp_intermediate.push_back(false);
				k++;
			}
		}	
		else if(temp.second >= intervals[j].first){
			temp.second = max(temp.second, intervals[j].second);
			k=j+1;
			j++;
			if(j==n){
				ret.push_back(temp);
				imp_intermediate.push_back(true);
			}
		}
		else{ //not intersecting
			ret.push_back(temp);
			imp_intermediate.push_back(true);
			temp = intervals[j];
			while(k<j){
				ret.push_back(intervals[k]);
				imp_intermediate.push_back(false);
				k++;
			}
			k=j+1;
			j++;
			if(j==n){
				ret.push_back(temp);
				imp_intermediate.push_back(true);
			}
		}
	}
	return ret;
}

vector<pair<int, int> > mergeIntervals(vector<pair<int, int> > &intermediate, int start, int end){
	vector<pair<int, int> > final;
	if(start==end){
		final.push_back(intermediate[start]);
		return final;
	}
	int i=start;
	pair<int, int> temp = intermediate[i];
	int j=i;
	while(j<=end){
		while(j<=end && temp.second >= intermediate[j].first){
			temp.second = max(temp.second, intermediate[j].second);
			j++;
		}
		final.push_back(temp);
		if(j==end+1)
			return final;
		temp = intermediate[j];
	}
	return final;
}

vector<pair<int, int> > helper(vector<pair<int, int> > &intervals, vector<bool> &important){
	vector<bool> imp_intermediate;
	vector<pair<int, int> > intermediate = combineImportantIntervals(intervals, important, imp_intermediate);
	vector<pair<int, int> > final;
	int n = intermediate.size();
	int i=0, j=0;
	while(j<n){
		while(i<n && imp_intermediate[i]==1){
			final.push_back(intermediate[i]);
			i++;
		}
		if(i==n)
			return final;
		i--;
		j=i+1;
		while(j<n && imp_intermediate[j]==0)
			j++;
		//now i points to left important interval and j points to right important interval. 
		//we want to merge intervals between i and j, truncating whatever is necessary
		if(i==-1 && j==n){
			//all are unimportant 
			final = mergeIntervals(intermediate, 0, n-1);
			return final;
		}
		else if(i==-1){
			//j is first important interval
			vector<pair<int, int> > temp = mergeIntervals(intermediate, 0, j-1);
			int k = temp.size();
			temp[k-1].second = min(temp[k-1].second, intermediate[j].first-1);
			for(int t=0; t<k; t++){
				final.push_back(temp[t]);
			}
			i=j;
		}
		else if(j==n){
			//i is the last important interval
			vector<pair<int, int> > temp = mergeIntervals(intermediate, i+1, n-1);
			int k = temp.size();
			int t=0;
			while(t<k && intermediate[i].second >= temp[t].second)
				t++;
			if(t==k)
				return final;
			temp[t].first = max(temp[t].first, intermediate[i].second+1);
			for(int x=t; x<k; x++)
				final.push_back(temp[x]);
			return final;
		}
		else{
			//merge unimportant intervals between the important i and j intervals.
			//then make i=j, and find next j
			vector<pair<int, int> > temp = mergeIntervals(intermediate, i+1, j-1);
			int k = temp.size();
			int t=0;
			while(t<k && intermediate[i].second >= temp[t].second)
				t++;
			if(t==k){
				i=j;
				continue;
			}
			temp[t].first = max(temp[t].first, intermediate[i].second+1);
			temp[k-1].second = min(temp[k-1].second, intermediate[j].first-1);
			for(int x=t; x<k; x++)
				final.push_back(temp[x]);
			i=j;
		}

	}
	return final;
}

int main(){
	int n;
	cin >> n;
	vector<pair<int, int> > intervals;
	int x, y;
	for(int i=0; i<n; i++){
		cin >> x >> y;
		intervals.push_back(make_pair(x,y));
	}
	vector<bool> important;
	for(int i=0; i<n; i++){
		cin >> x;
		if(x)
			important.push_back(true);
		else
			important.push_back(false);
	}
	vector<pair<int, int> > ans = helper(intervals, important);
	for(int i=0; i<ans.size(); i++){
		cout << "{" << ans[i].first << "," << ans[i].second << "}";
		if(i!=ans.size()-1)
			cout << ",";
	}
	cout << endl;
}