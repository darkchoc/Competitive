/*
https://leetcode.com/discuss/interview-question/4220651/Amazon-OA

Amazon Prime Video has movies in the category 'comedy' or 'drama'. Determine the earliest time you can finish at least one movie from each category. The release schedule and durations of the movies are provided.You can start watching a movie at the time it is released or later.If you begin a movie at time t, it ends at time t + duration.If a movie ends at time t + duration, the second movie can start at that time, t + duration, or later.The movies can be watched in any order.
Example:
comedyReleaseTime = [1, 4]
comedyDuration = [3, 2]
dramaReleaseTime = [5, 2]
dramaDuration = [2, 2]
Duration and release times are aligned by index.
Two of the best ways to finish watching one movie from each category at the earliest time are as follows:
Start watching comedy movie1 at time t = 1 and until t = 1 + 3 = 4. Then, watch the drama movie2 from time t = 4 to t = 4 + 2 = 6. Start watching drama movie2 at time t = 2 and until t = 2 + 2 = 4.Then, watch the comedy movie2 from time t = 4 to t = 4 + 2 = 6.
The earliest finish time and also the answer is 6.

Example 2:
comedyReleaseTime = {1,2};
comedyDuration = {10,5};
dramaReleaseTime = {4,8};
dramaDuration = {6,3};
Output: 11
Explanation: Pick movie 2 from comedy (ends at 7). Then pick movie 2 from drama (ends at 11).
*/

#include <bits/stdc++.h>
using namespace std;

int getMinTime(vector<int> firstReleaseTime, vector<int> firstDuration, vector<int> secondReleaseTime, vector<int> secondDuration) {
    int minTimeWhenFirstMovieEnds = INT_MAX;
    for(int i=0; i<firstReleaseTime.size(); i++)
        minTimeWhenFirstMovieEnds = min(minTimeWhenFirstMovieEnds, firstReleaseTime[i] + firstDuration[i]);

    // now we need to check which movie from second genre should we see to get min time overall.
    int ans = INT_MAX;
    for(int i=0; i<secondReleaseTime.size(); i++){
        int overallEndTime;
        if(secondReleaseTime[i] <= minTimeWhenFirstMovieEnds)
            overallEndTime = minTimeWhenFirstMovieEnds + secondDuration[i];
        else
            overallEndTime = secondReleaseTime[i] + secondDuration[i];
        ans = min(ans, overallEndTime);
    }
    return ans;
}

int minMovieTime(vector<int> comedyReleaseTime, vector<int> comedyDuration, vector<int> dramaReleaseTime, vector<int> dramaDuration) {
    int watchComedyFirst = getMinTime(comedyReleaseTime, comedyDuration, dramaReleaseTime, dramaDuration);
    int watchDramaFirst = getMinTime(dramaReleaseTime, dramaDuration, comedyReleaseTime, comedyDuration);
    return min(watchComedyFirst, watchDramaFirst);
}

int main() {
    /*
    Initially I thought something complex. I thought that first I'll take the case of watching comedy movie first, and then I'll take case of watching drama movie first.
    Case 1: I'll calculate when each comedy movie ends and sort it. Then while iterating over these end times of comedy movies, I'll check which all drama movies have released (basically check dramaRelease <= comedyMovieEnd). To do this, I can push release time and duration of drama movies into a vector of pairs and sort it. Then I can maintain a pointer on this vector and keep incrementing it as we go further ahead in time.
    All drama movies that have been released before the ending of a particular comedy movie, we add their duration to a minheap. So basically, when we are at comedyEndTime[i], in the heap we have all drama movies that have released till that time sorted according to duration. We take the min duration (heap top) drama movie and add it to comedy movie's end time.

    This approach was wrong for three reasons.
    1. If we have decided to watch comedy movie first, then why iterate on comedy movies that are ending later? Just pick the comedy movie that ends the first.
    2. If we only need the min duration of drama movie among the drama movies present in heap, there is no need for heap and we can maintain a minDramaDuration variable that will contain the minDuration of drama movie that has been released till now. 
    3. The 3rd very important reason is: if we watch a comedy movie, it might be better to wait for a bit for the release of a drama movie and then watch that instead of watching a drama movie that has released within the time duration in which our comedy movie ended. Also, there can be a case that comedy movie ends but no drama movie got released yet. 

    After coding this and seeing my answer fail, I released that question is much simpler. We again have 2 cases.
    Case 1: comedy followed by drama
    Case 2: drama followed by comedy.

    Case 1: -> get comedy movie that ends first. This now remains fixed. Then iterate over drama movies and check that if you were to watch that drama movie, what would be the overall ending time. 
    Similarly for case 2.

    Min of these two cases will be our answer.
    */
    cout << minMovieTime({1,4}, {3,2}, {5,2}, {2,2}) << endl; // 6
    cout << minMovieTime({1,2}, {10,5}, {4,8}, {6,3}) << endl; // 11
    cout << minMovieTime({3,6,4,8,2,4,5}, {10,7,5,9,9,11,14}, {5,2,8,4,6}, {11,14,4,8,9}) << endl; // 13
}