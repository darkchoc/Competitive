/*
https://www.reddit.com/r/leetcode/comments/1jhjiw8/google_l4_interview_questions/

Round1: Paint a fence but with twist. We have planks of different heights that we need to paint and width is 1 for all. Brush width is also 1. We can make a stroke either horizontally or vertically. Give the minimum strokes we can make to paint the complete fence.

E.g i/p - [1,1,1,1,1,1] o/p - 1 as can be painted in 1 horizontal stroke.

E.g i/p - [2,5,6,1,7,2,4] o/p- need to check multiple ways by combination of horizontal and vertical strokes. Like on 1st horizontal stroke here. 1 becomes 0. So now we can’t paint over it again and array gets divided into 2 parts. And run logic on these subarrays separately. So keep track if anytime any number becomes 0.
*/

/*
Thoughts:
If we're solving for planks between index i to j, we can check if there is any plank with height = 0, between i and j. If so, we cannot make a horizontal 
storke and must divide the subarray into two, (i,k-1) and (k+1, j). 
Now say (i,j) is all non-zero. We can have one horizontal stroke to decrease each element by 1. Other option is to make vertical stroke and reduce an 
element to 0 straight away. 

Say we have two planks, (3, 5). We can either make 3 strokes first to get to (0, 2) or make 2 strokes to straight away get to (0, 0). So maybe we can see
what the answer would be if we make horizontal strokes and return min of that and number of planks (vertical strokes).
*/

#include <iostream>
using namespace std;

int helper(vector<int> &nums, int start, int end, int horizontalStrokes){
    if(start>end) return 0;
    if(start==end) return 1;
    int minElement = nums[start];
    // find min element in the nums[start..end] subarray.
    for(int i=start; i<=end; i++)
        if(nums[i] < minElement)
            minElement = nums[i];
    // now break the array whenever nums[i]==minElement
    int answerIfWeMakeHorizontalStroke = minElement - horizontalStrokes; // we have already painted 'horizontalStorkes' length of each board
    int startOfRange=-1; // this range is basically the range between two indexes p, q such that nums[p]=nums[q]=minElement and all 
    // elements between nums[p+1...q-1] > minElement. This is basically the subarray that we want to process next. The elements which are
    // equal to minElement will basically break the whole subarray into multiple smaller parts.
    for(int i=start; i<=end; i++){
        if(nums[i]==minElement) {
            if(startOfRange!=-1) {
                answerIfWeMakeHorizontalStroke += helper(nums, startOfRange, i-1, minElement);
                startOfRange=-1;
            }
        } else if(nums[i] > minElement) {
            if(startOfRange==-1) {
                // startRange
                startOfRange=i;
            }
        }
    }
    if(startOfRange!=-1) {
        // means nums[end] != minElement
        answerIfWeMakeHorizontalStroke += helper(nums, startOfRange, end, minElement);
    }
    return min(answerIfWeMakeHorizontalStroke, end-start+1); // min of horizontalStroke , verticalStoke
}

int minStrokes(vector<int> nums){
    int n = nums.size();
    return helper(nums, 0, n-1, 0);
}

int main() {
    cout << minStrokes({1,1,1,1,1,1}) << endl; // 1
    cout << minStrokes({2,5,6,1,7,2,4}) << endl; // 7
    cout << minStrokes({1,2,2,1}) << endl; // 2
    cout << minStrokes({1,2,3,2}) << endl; // 3
    cout << minStrokes({4,5,6,5,4}) << endl; // 5
    cout << minStrokes({1,1,2,4,5,3,2,1,1,2,3,1,1,4,3}) << endl; // 9
    cout << minStrokes({4,4,5,5,5,5,5,5,4}) << endl; // 5
}