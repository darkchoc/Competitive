/*Given intervals sorted according to start times. An additional array is given which tells whether an interval is important or not. If important[i]=1, interval i is important.
Merge the overlapping intervals. If at point there is important as well as 
unimportant interval, then that point should be important. An unimportant interval gets split into two by an important interval.

Example: intervals = {1,3},{2,4},{5,9},{6,7},{8,13},{11,14},{13,16},{15,18}
		important  =  0,    0,    1,    0,    0,     1,       1,      0
	Ans: {1,4},{5,9},{10,10},{11,16},{17,18}

Example 2: intervals = {1,5},{2,11},{8,9}
		    important =  1,     0,    1  
	Correct Ans: {1,5},{6,7},{8,9},{10,11}
	This type of case is now being handled, where an unimportant interval split in such a way
	that part of it might go on the other side of the important interval.

Example 2: intervals = {1,8},{2,5},{6,11},{8,9},{14,17},{17,20},{19,23},{20,28},{24,27},{26,28},{30,34},{33,36},{34,40},{38,41},{43,48},{45,50}
          important =   0,    1,     1,    0,     0,      1,      0,      1,      1,      0,      1,     0,       0,      1,      0,      1 
     Ans: {1,1},{2,5},{6,11},{14,16},{17,28},{30,34},{35,37},{38,41},{43,44},{45,50}

*/

#include <bits/stdc++.h>

using namespace std;

typedef vector<pair<int, int> > VPII;
// 0 start of important interval
// 1 end of important interval
// 2 start of unimportant interval
// 3 end of important interval
// If all are at same time, start of an important interval should be given higher preference
// If end of imp interval and start+end of unimportant interval at same time, then end of imp interval to be given prefernce
// If start and end of unimp interval at same time, start of unimp interval to be given preference.
// Hence the 0,1,2,3 types encoding.

VPII helper(VPII &intervals, vector<bool> &imp){
	VPII points;
	int n = intervals.size();
	for(int i=0; i<n; i++){
		if(imp[i]){
			points.push_back(make_pair(intervals[i].first, 0));
			points.push_back(make_pair(intervals[i].second, 1));
		}
		else{
			points.push_back(make_pair(intervals[i].first, 2));
			points.push_back(make_pair(intervals[i].second, 3));
		}
	}
	sort(points.begin(), points.end());
	stack<pair<int, int> > st;
	int imp_open=0;
	int unimp_open=0;
	for(int i=0; i<points.size(); i++){
		if(i==0){
			st.push(points[i]);
			if(points[i].second==0)
				imp_open++;
			else
				unimp_open++;
		} else{
			pair<int, int> p = st.top();
			if(p.second==0){
				if(points[i].second==0)
					imp_open++;
				else if(points[i].second==1){
					imp_open--;
					if(imp_open==0)
						st.push(points[i]);
				}
				else if(points[i].second==2){
					unimp_open++;
				}
				else{
					unimp_open--;
					continue;
				}
			} else if(p.second==1){
				if(points[i].second==0){
					if(unimp_open>0){
						if(p.first+1<=points[i].first-1){
							st.push(make_pair(p.first+1, 2));
							st.push(make_pair(points[i].first-1, 3));
						}
					}
					st.push(points[i]);
					imp_open++;
				} else if(points[i].second==1){
					//not possible
					continue;
				} else if(points[i].second==2){
					if(unimp_open>0){
						st.push(make_pair(p.first+1, 2));
						unimp_open++; //to account for points[i]
					}
					else{
						st.push(points[i]);
						unimp_open++;
					}
				} else{
					unimp_open--;
					if(unimp_open==0){
						if(p.first+1<=points[i].first){
							st.push(make_pair(p.first+1, 2));
							st.push(points[i]);
						}
					}
				}
			} else if(p.second==2){
				if(points[i].second==0){
					st.push(make_pair(points[i].first-1, 3));
					st.push(points[i]);
					imp_open++;
				} else if(points[i].second==1){
					//not possible
					continue;
				} else if(points[i].second==2){
					unimp_open++;
				} else{
					unimp_open--;
					if(unimp_open==0)
						st.push(points[i]);
				}
			} else{
				if(points[i].second==0){
					st.push(points[i]);
					imp_open++;
				} else if(points[i].second==1){
					//not possible
					continue;
				} else if(points[i].second==2){
					st.push(points[i]);
					unimp_open++;
				} else{
					//not possible
					continue;
				}
			}
		}
	}
	VPII stack_content;
	while(!st.empty()){
		stack_content.push_back(st.top());
		st.pop();
	}
	reverse(stack_content.begin(), stack_content.end());
	VPII ans;
	for(int i=0; i<stack_content.size(); i=i+2){
		ans.push_back(make_pair(stack_content[i].first, stack_content[i+1].first));
	}
	return ans;
}

int main(){
	int n;
	cin >> n; 
	VPII intervals;
	int x, y;
	for(int i=0; i<n; i++){
		cin >> x >> y;
		intervals.push_back(make_pair(x,y));
	}
	vector<bool> imp;
	for(int i=0; i<n; i++){
		cin >> x;
		imp.push_back(x);
	}
	VPII ans = helper(intervals, imp);
	for(int i=0; i<ans.size(); i++){
		cout << "{" << ans[i].first << "," << ans[i].second << "}";
		if(i!=ans.size()-1)
			cout << ","; 
	}
	cout << endl;
}