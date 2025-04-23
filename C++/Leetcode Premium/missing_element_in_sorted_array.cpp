/*
https://leetcode.ca/all/1060.html

1060. Missing Element in Sorted Array
Given a sorted array A of unique numbers, find the K-th missing number starting from the leftmost number of the array.

 

Example 1:

Input: A = [4,7,9,10], K = 1
Output: 5
Explanation: 
The first missing number is 5.
Example 2:

Input: A = [4,7,9,10], K = 3
Output: 8
Explanation: 
The missing numbers are [5,6,8,...], hence the third missing number is 8.
Example 3:

Input: A = [1,2,4], K = 3
Output: 6
Explanation: 
The missing numbers are [3,5,6,7,...], hence the third missing number is 6.
 

Note:

1 <= A.length <= 50000
1 <= A[i] <= 1e7
1 <= K <= 1e8

*/

/*
Thoughts:

If we are at arr[i]:
missing numbers: arr[i] - arr[0] - i
eg: in [4,7,9,10], when you are 10, you know that between 4 and 10, total 5 numbers are there, but 2 of them (7 and 9) are not missing. 
So if we subtract 10-4, we get 6. But we also need to subtract the numbers that are there (7 and 9) = (index of 10 - index of 4 = 3 - 0 = 3)
So 6 -3  = 3. So we know 3 numbers are missing till 10. These are (5,6,8).

Now, we need to find the last element where missing numbers < k. Say it's index i.
So missing numbers till i = arr[i] - arr[0] - i < k
But missing numbers till i+1 = arr[i+1] - arr[0] - (i+1) >= k
Now if we need k missing numbers, and have already found (arr[i]-arr[0]-i) missing numbers, we need to add the difference to arr[i]
So missing number = arr[i] + (k - (arr[i]-arr[0]-i)) = arr[i] + k - arr[i] + arr[0] + i = k + arr[0] + i

Now let's think of some edge cases. Would it matter if at arr.size()-1 we still don't have enough missing numbers? No.
So let's code it up.
*/

#include <iostream>
using namespace std;

int missingNumber(vector<int> nums, int k) {
    int l = 0, r = nums.size()-1;
    while(l < r) {
        int mid = l + (r-l+1)/2; // biased towards r 
        int missingTillNow = nums[mid] - nums[0] - mid;
        if(missingTillNow >= k)
            r = mid-1;
        else 
            l = mid;
    }
    // now l points to last element where missing numbers are < k
    return k + nums[0] + l;
}

int main(){
    cout << missingNumber({4,7,9,10}, 1) << endl; // 5
    cout << missingNumber({4,7,9,10}, 3) << endl; // 8
    cout << missingNumber({1,2,4}, 3) << endl; // 6
    cout << missingNumber({2}, 8) << endl; // 10
}