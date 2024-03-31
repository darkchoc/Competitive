/*
https://leetcode.com/discuss/interview-question/341992/Sigma-Computing-or-Online-Assessment-2019 
Question 2 in above link

The number of goals achieved by two football teams in matches in a league is given in the form of two lists. Consider:
- Football team A has played 3 matches and scored {1,2,3} goals in each match respectively.
- Football team B has played 2 matches and scored {2,4} goals in each match respectively.

Your task is to compute for each match of team B, the total number of matched of team A, where team A has scored less than or equal to the number of goals scored by team B in that match. 
In the above case:
    - For two goals scored by team B in the first match, team A has two matches with scores 1 and 2.
    - For four goals scored by team B in its second match, team A has 3 matches with scores 1,2, and 3.
    - Hence the answer is {2,3}
*/

#include <bits/stdc++.h>
using namespace std;

void solve(vector<int> a, vector<int> b){
    vector<int> ans;
    if(a.size()==0){
        for(int i=0; i<b.size(); i++) 
            ans.push_back(0);
    } else {
        sort(a.begin(), a.end());
        for(int i=0; i<b.size(); i++){
            if(a[0] > b[i]){
                ans.push_back(0);
                continue;
            } else if(a[a.size()-1] <= b[i]){
                ans.push_back(a.size());
                continue;
            }
            int low = 0, high = a.size()-1;
            while(low < high){
                int mid = (low + high + 1)/2; // biased towards high
                if(a[mid] <= b[i])
                    low = mid;
                else   
                    high = mid-1;
            }
            ans.push_back(low+1);
        }
    }
    for(int i=0; i<ans.size(); i++)
        cout << ans[i] << ", ";
    cout << endl;
}

int main(){
    solve({1,2,3}, {2,4});
}