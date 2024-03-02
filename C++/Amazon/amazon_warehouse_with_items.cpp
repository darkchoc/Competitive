//Question: https://leetcode.com/discuss/interview-question/1904966/Amazon-orOAorset-7
//Similar to: https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/


/*
Basically find how many subarrays are there for which max(subarray) - min(subarray) <= threshold.

Approach: We will keep two dequeus. One will maintain minimum between our two pointers, and one will maintain maximum. For every index r, we will add how many subarrays would be valid which end at index r. The start pointer would only be moved if difference between min and max is greater than threshold.

Eg: 8 3 4 3 9 6
Ind:0 1 2 3 4 5

r=0, l=0;
Min: 0
Max: 0 -> max-min valid => ans += (r-l+1) -> (8)

r=1
Min: 1
Max: 0 1 -> max-min not valid => move l
--> Min: 1
    Max: 1 => valid, ans+= (r-l+1) -> (3)

r=2, l=1
Min: 1 2
Max: 2 => valid, ans+=(r-l+1) -> (4, 3 4)

r=3, l=1
Min: 3
Max: 2 3 => valid, ans+=(r-l+1) -> (3, 4 3, 3 4 3)

r=4, l=1
Min: 3 4
Max: 4 => not valid, move l till the time invalid
--> Min: 4
    Max: 4 => valid, ans+=(r-l+1) -> (9)

r=5, l=4
Min: 5
Max: 4, 5 -> valid, ans += (r-l+1) -> (6, 9 6)
*/

#include <bits/stdc++.h>
using namespace std;

int solve(vector<int> &arr, int k){
    int n = arr.size();
    deque<int> minInd;
    deque<int> maxInd;
    int l = 0;
    int ans = 0;
    for(int r=0; r<n; r++){
        while(!minInd.empty() && arr[minInd.back()] >= arr[r])
            minInd.pop_back();
        while(!maxInd.empty() && arr[maxInd.back()] <= arr[r])
            maxInd.pop_back();
        minInd.push_back(r);
        maxInd.push_back(r);

        while(arr[maxInd.front()] - arr[minInd.front()] > k){
            if(maxInd.front()==l)
                maxInd.pop_front();
            if(minInd.front()==l)
                minInd.pop_front();
            l++;
        }
        ans += (r - l + 1);
    }  
    return ans;
}

int main(){
    vector<int> arr = {8, 3, 4, 3, 9, 6};
    cout << solve(arr, 4) << endl;
}