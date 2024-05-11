/*
https://leetcode.ca/all/1099.html
*/

#include <bits/stdc++.h>
using namespace std;

int WrongSolutionButCorrectAnswer(vector<int> arr, int sum) {
    /*
    The question said that two elements A[i] and A[j] such that i < j and A[i] + A[j] = S and S < sum and we want to return max S. I thought that we can only consider i and j such that i < j and so cannot sort the array. But this is just me being dumb. How do indexes even matter? If after sorting we find some i, j that have closest sum to given target, that is fine... in the original array, the later element can be j and earlier one can be i. We haven't been asked to return the indices anyway. So we can simply do two pointer.
    */
    map<int, int> mp;
    int ans = -1;
    for(int i=0; i<arr.size(); i++){
        int toFind = sum - arr[i];
        // find number just less than toFind in the numbers seen till now.
        map<int, int>::iterator it = mp.lower_bound(toFind);
        if(mp.size()==0 || it==mp.begin()){
            // don't do anything.
        } else {
            it--;
            int currentSum = arr[i] + it->first;
            ans = max(ans, currentSum); // sum/target is always > 0 so doing this is fine. Had there been possiblity to have negative targets, doing ans = max() wouldn't be right, even initializing ans with -1 wouldn't be right.
        }
        mp[arr[i]]=i;
    }
    return ans;
}

int CorrectSolution(vector<int> arr, int sum) {
    sort(arr.begin(), arr.end());
    int i = 0; 
    int j = arr.size()-1;
    int ans = -1;
    while(i < j){
        int currentSum = arr[i] + arr[j];
        if(currentSum < sum){
            ans = max(ans, currentSum);
            i++;
        } else {
            j--;
        }
    }
    return ans;
}

int main(){
    cout << CorrectSolution({34,23,1,24,75,33,54,8}, 60) << endl;
    cout << CorrectSolution({10,20,30}, 15) << endl;
}