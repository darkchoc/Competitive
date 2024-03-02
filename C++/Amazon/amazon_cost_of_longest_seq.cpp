/*
https://leetcode.com/discuss/interview-question/4269348/amazon


You are given an array A of length N. You are also given K dollars

You want to buy an increasing subsequence S from the array A where S[i] > S[i-1] for all valid i. The cost of a subsequence S of size L is the sum of S[i]*i*(L-i+1) for all such 1<=i<=L.

Find the length of the longest increasing subsequennce you can buy given that you only have K dollars

Constraints:
1 <= K <= 1e9
1 <= N, A[i] <= 1e5

Examples:
Input
N=3
K=20
A = [1,2,3]

Output: 3

Explanation
N=3, K=20 A=[1,2,3]. You can take the whole array with the cost of (1*1*3) + (2*2*2 ) + (3*3*1) = 20

Input
N=4
K=19
A=[1,7,2,3]

Output: 2

Explanation
N=4, K=19, A=[1,7,2,3]. If you want to take subsequence of size 3 then the [1,2,3] is the cheapest and has a cost of 20, thus you cant take a subsequence longer than length 2

Input
N=6
K=3
A = [4,6,5,8,4,7]

Output: 0

Explanation
N=6 K=3 A=[4,6,5,6,4,7] You can't take any subsequence because the money you have can't affoard any element, and the size of the empty subsequence is 0
*/

#include <bits/stdc++.h>
using namespace std;

int maxLen(vector<int> nums, int k){
    // cost = S[i]*i*(L-i+1) where 1 <= i <= L
    // cost = S[i]*i*L + S[i]*i*(1-i)
    vector<vector<int> > lis;
    lis.push_back({nums[0], nums[0]*1, nums[0]*1*(1-1)});
    for(int i=1; i<nums.size(); i++){
        int low = 0, high = lis.size();
        while(low < high){
            int mid = (low + high)/2;
            if(lis[mid][0] < nums[i])
                low = mid+1;
            else
                high = mid;
        }
        if(low == lis.size()){
            lis.push_back({nums[i], nums[i]*(low+1) + lis[low-1][1], nums[i]*(low+1)*(1-(low+1)) + lis[low-1][2]});
        } else if(low == 0){
            lis[low] = {nums[i], nums[i]*(low+1), nums[i]*(low+1)*(1-(low+1))};
        } else {
            lis[low] = {nums[i], nums[i]*(low+1) + lis[low-1][1], nums[i]*(low+1)*(1-(low+1)) + lis[low-1][2]};
        }
    }
    for(int len = lis.size(); len>0; len--){
        int totalCost = lis[len-1][2] + (len*lis[len-1][1]);
        if(totalCost <= k) return len;
    }
    return 0;
}

int main(){
    /*
    I looked at the constraints first. I understood that algo has to be of type O(NLogN) complexity.
    We can find longest increasing sequence in O(nLogn). Then I tried to see how can I modify it to find the cost of the sequence.

    To be honest, I first forgot that cost is dependent on L (length of sequence). I thought it was just nums[i]*i. So for that, I came up with the modified LIS algorith. Basically, while constructing the LIS, when I'm inserting an element x at a particular index i in LIS array, I will also calculate the cost by adding x*i to the cost upto lis[i-1]. This cost will now be associated with lis[i].

    But then I realised that cost is dependent on length of longest sequence as well. Upon thinking more, I realised that cost can be broken into: S[i]*i*L + S[i]*i*(1-i).

    As you can see, the first term is dependent on L but not the second. Let us call these terms cost1 and cost2.
    cost2 can be calculated in a cumulative fashion as before. Basically everytime we insert element x into LIS at index i, we updated cost2[i] = cost2[i-1] + x*i*(1-i).
    
    cost1 can't be calculated the same way. Now suppose we have a sequence of length L, with elements x1, x2,... x_l . Then 'cost1' for them can be calculated as L*(x1*1 + x2*2 + x3*3... x_l*l)
    So if we keep cumulative sum of S[i]*i, we can multiply it by L to get cost1. 
    So now, with LIS[i], I store one more term: cost1[i] = cost1[i-1] + x*i, x being the element being inserted at index i in LIS.

    With these two values associated with every index of LIS array, I can get min cost of a sequence of length L by doing: cost1[L]*L + cost2[L]. 

    Now in my algorithm, instead of having three separate arrays (LIS, cost1, cost2), I have one 2d array LIS, where LIS[i] will hold 3 numbers: the minimum number used to create the largest increasing sequence of length i, the cost1 term for lis[i], and the cost2 term for lis[i].

    The rest of it is exactly what I wrote above.
    */

    cout << maxLen({1,2,3}, 20) << endl; // 3
    cout << maxLen({1,7,2,3}, 19) << endl; // 2
    cout << maxLen({4,6,5,8,4,7}, 3) << endl; // 0
    cout << maxLen({1,4,3,2,6,5,3,7,4,3,8,4,9}, 120) << endl; // 5
    cout << maxLen({1,4,3,2,6,5,3,7,4,3,8,4,9}, 119) << endl; // 4
}