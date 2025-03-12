/*
https://leetcode.com/discuss/post/629432/facebook-phone-unique-elements-in-a-sort-ujfr/

Given sorted array, find number of distinct elements.
*/


/*
Initial thoughts: 
Approach 1: 
    Iterate on array and keep counting everytime you encounter a unique element. Initialize count with 1, and start iterating from index 1, 
    and whenever arr[i]!=arr[i-1], we are at a new element so increment count. 
    Time Complexity: O(n), Space complexity: O(1)


Approach 2:
    Start from index 0, instead of iterating to find the the next unique element, apply binary search on remaining array to find first element 
    greater than arr[i]. That should be your next index. Increment count. And then again go to next index by applying binary search.
    Time Complexity: O(KLogN) where K = # unique elements. Space = O(1).  Worst Case Time Complexity: K=N, so NlogN

Approach 3:
    If we look at start and end index, and if arr[start] == arr[end], that means only 1 distinct element between [start, end]. But if arr[start] != arr[end],
    then we break the array into two, [start, mid] and [mid+1, end]. Here itself, we can check if arr[mid]==arr[mid+1], then subtract 1 from the addition of 
    these two recursive calls. We recursing till the time we don't find arr[start]==arr[end]. So if we have K unique elements, and all have nearly equal 
    number of occurrences (eg: 1111222233334444), then we'll have 
                        [1,16]
                    [1,8]    [9,16]
                [1,4] [5,8] [9,12] [13,16]
    i.e at the end level, we have K calls, and the level before, we have K/2 calls, and the level before, we have K/4 calls. So basically, for K unique 
     elements, we have K + K/2 + K/4 + ... K/(2^logK) calls. (going from bottom to top)
      = K(1 + 1/2 + 1/4 + .... 1/(2^logK)) = K(1 * (1 - (1/2)^(logK + 1)) / (1 - 1/2)) = 2K(1  - (1/2)^(logK + log2)) = 2K(1 - (1/2)^(log2K)) = 
      2K (2^(log2K) - 1) / (2^log2K) = 2K * (2K - 1) / 2^(log2K) = 2K (2K - 1) / 2K = 2K - 1 = O(K)

    So: Time Complexity: O(K) in best case, O(N) in worst case. Space complexity: O(logK) = height of recursion stack.

    Actually, I'm wrong. Worst case for the above algo would be say: we have [1 2 2 2...... 2] say this array is of size 1 million. Then first we'll
    divide array in 2, (500K), we futher divide the left half into two of 250K, and so on, till we finally are left with the array [1,2]
    Which we further divide into [1] and [2]. This is logN. So in worst case, for each unique element, we have to divide the array like this and we 
    may have time complexity = O(KlogN).


This makes sense, because consider we have 1 million elements, the first 500k elements are 1 and second half is 2. If we increase the size of array to 10
million (with 5m of each 1 and 2), then Approach 2 will take more time as now binary search is over 10 million elements and not 1 million. 
But approach 3 will take same amount of time as in both cases, it would look at extremes, decide to break the array in half, and will arrive at two halfs
with same value at extremes, and hence return the answer from there.
*/

#include <iostream>
using namespace std;

int approach1(vector<int> &nums) {
    // linear iteration
    if(nums.size() < 2) return nums.size();
    int count = 1;
    for(int i=1; i<nums.size(); i++)
        if(nums[i]!=nums[i-1])
            count++;
    return count;
}

int approach2(vector<int>& nums) {
    // binary search to find next unique element
    if(nums.size() < 2) return nums.size();
    int count = 1;
    int i = 0;
    while(i < nums.size() && nums[i]!=nums[nums.size()-1]){ // adding the second condition ensures we don't go in while loop if nums[i] is the last
        // of the distinct elements

        // do binary search to find first element greater than nums[i]
        int l = i, r = nums.size()-1;
        while(l < r) {
            int mid = (l + r) / 2;
            if(nums[mid]==nums[i]) l = mid + 1;
            else r = mid;
        }
        // l and r point to first index of next element
        i = r;
        count++;
    }
    return count;
}

int helperDivideAndConquer(vector<int> &nums, int start, int end){
    if(nums[start]==nums[end]) return 1;
    int mid = (start + end)/2;
    int distinctElements = helperDivideAndConquer(nums, start, mid) + helperDivideAndConquer(nums, mid+1, end);
    if(nums[mid]==nums[mid+1])
        distinctElements--;
    return distinctElements;
}

int approach3(vector<int> &nums) {
    // divide and conquer
    if(nums.size() < 2) return nums.size();
    return helperDivideAndConquer(nums, 0, nums.size()-1);
}

int findDistinctElements(vector<int> nums){
    int ans1 = approach1(nums);
    int ans2 = approach2(nums);
    int ans3 = approach3(nums);
    if(ans1==ans2 && ans2==ans3) return ans1;
    return -1;
}

int main() {
    cout << findDistinctElements({1,1,1,2,2,3,4,5,5,6}) << endl; // 6
    cout << findDistinctElements({1,2,3,4}) << endl; // 4
    cout << findDistinctElements({1,1,1,1}) << endl; // 1
    cout << findDistinctElements({1,1,2,3,3,4,5,6}) << endl; // 6
    cout << findDistinctElements({1}) << endl; // 1

}