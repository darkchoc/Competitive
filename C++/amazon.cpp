#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > solve(int maxTravelDist, vector<vector<int> > &forwardRouteList, vector<vector<int> > &returnRouteList){
 	int nForward = forwardRouteList.size();
 	int nReturn = returnRouteList.size();
 	// for(int i=0; i<nForward; i++){
 	// 	swap(forwardRouteList[i].first, forwardRouteList[i].second);
 	// }
 	for(int i=0; i<nReturn; i++){
 		swap(returnRouteList[i][0], returnRouteList[i][1]);
 	}
 	//sort(forwardRouteList.begin(), forwardRouteList.end());
 	sort(returnRouteList.begin(), returnRouteList.end());
 	vector<vector<int> > ans;
 	int maxTillNow = 0;
 	for(int i=0; i<nForward; i++){
 		int currentForwardDist = forwardRouteList[i][1];
 		int currentForwardRoute = forwardRouteList[i][0];
 		if(currentForwardDist + returnRouteList[0][0] > maxTravelDist)
 			continue;
 		int left = 0, right = nReturn-1;
 		//T T T T F F F F -> T = less than equal to maxTravelDist, F = greater than maxTravelDist. 
 		//We want index of last T.
 		while(left < right){
 			int mid = left + (right - left + 1)/2; //biased towards right
 			if(currentForwardDist + returnRouteList[mid][0] > maxTravelDist){
 				right = mid-1;
 			} else {
 				left = mid;
 			}
 		}
 		//now check elements starting from index left_, and those which have value equal to the value of element at index left_ and are on left of left_.
 		if(currentForwardDist + returnRouteList[left][0] > maxTillNow){
 			ans.clear();
 			maxTillNow = currentForwardDist + returnRouteList[left][0];
 		} else if(currentForwardDist + returnRouteList[left][0] < maxTillNow){
 			continue;
 		}
 		vector<int> p;
 		p.push_back(currentForwardRoute);
 		p.push_back(returnRouteList[left][1]);
 		ans.push_back(p);
 		left--;
 		while(left >= 0 && returnRouteList[left][0] == returnRouteList[left+1][0]){
 			vector<int> p;
 			p.push_back(currentForwardRoute);
 			p.push_back(returnRouteList[left][1]);
 			ans.push_back(p);
 			left--;
 		}
 	}
 	return ans;
}

int main(){
	int maxTravelDist;
	cin >> maxTravelDist;
	int nForward, nReturn;
	cin >> nForward >> nReturn;
	vector<vector<int> > forwardRouteList (nForward);
	vector<vector<int> > returnRouteList (nReturn);
	int x, y;
	for(int i=0; i<nForward; i++){
		cin >> x >> y;
		forwardRouteList[i].push_back(x);
		forwardRouteList[i].push_back(y);
	}
	for(int i=0; i<nReturn; i++){
		cin >> x >> y;
		returnRouteList[i].push_back(x);
		returnRouteList[i].push_back(y);
	}
	vector<vector<int> > ans = solve(maxTravelDist, forwardRouteList, returnRouteList);
	for(int i=0; i<ans.size(); i++){
		cout << ans[i][0] << "," << ans[i][1] << "  "; 
	}
	cout << endl;
	return 0;
}

We keep the forwardRoutes as it. But we sort the return routes in ascending order, according to the distance. 
Now, for every forward route, we apply binary search on return routes list to find the largest return route that can be combined with the forward route. This complexity of this 
step is O(log(n)). After finding that route, we check whether the combination of this return route and forward route is maximum uptil now. If it is, we clear our answer vector 
and start populating it freshly. If the combined distance is less than the maximum uptil now, we ignore this combination and continue with next forward route.

In the case when the route is maximum uptil now, we also check if there are other return routes which are equivalent to the one that got selected by the binary search. If there are,
we add them too in the answer vector.  

Since we are performing binary search on return routes list for every route in the forward routes list, the complexity will be O(nLogn).