/*
https://www.reddit.com/r/leetcode/comments/1jhjiw8/google_l4_interview_questions/

There is a stream of values coming. Window size is M and a value K is given. Values are coming one by one. Return average of values that remain after topK and bottomK values are not being included. Until window has M values, return -1 from the function. As soon as size becomes = M. Return the average. 1- start pushing new value and and removing least recent value in window if window already M sized. 2- Return average of values remaining after topK and bottomK values are not included. E.g- M =5 and K=1 Curr window- [4,3,3,6,1],

topK- 6 and bottomK-1 So return 3+3+4/3
*/

/*
Thoughts:

This is somewhat similar to median of streams. This problem, can be broken into 3 parts that run in parallel. 
It's like saying that in a window,
 => can you find out the min k elements
 => can you find out the max k elements
 => then just do (sum of all elements - sum of min k elements - sum of max k elments) / num_elements - 2k

 Now, to keep top k elements, we would need a minHeap. And to keep bottom k elements, we woud need a maxHeap. Why that? So let's say we add an element
 to the top K element heap. If size exceeds k, we want to remove the smallest of the top k elements. Now, we can only pop the top of the heap, so we
 need minHeap to store top k if we want to be able to remove the minimum of the top K elements if size exceeds k. Similarly, for bottom k, we need
 max heap.
*/

#include <iostream>
#include <set>
using namespace std;


int main(){
    // avgAfterRemovingTopAndBottomK({1,4,3,2,5,6,3,4,5,6,7}, 3, 1); // -1 -1 3 3 3 5 5 4 4 5 6
    // avgAfterRemovingTopAndBottomK({1,4,3,7,5,6,2,4,5,7,2,9}, 5, 1); // -1 -1 -1 -1 4 5 4.66 5 4.66 5 3.66 5.33
    // avgAfterRemovingTopAndBottomK({5,3,4,6,4,5,7,2,4,3,5,3,6,7}, 6, 2); // -1 -1 -1 -1 -1 4.5 4.5 4.5 4.5 4 4.5 3.5 3.5 4.5
    // avgAfterRemovingTopAndBottomK({1,4,3,5,6}, 4, 2); // 2*k >= window_size
    // avgAfterRemovingTopAndBottomK({3,4,2,6,3,4,6,8}, 3, 0); // -1 -1 3 4 3.66 4.33 4.33 6
}

