// https://leetcode.com/discuss/interview-question/4754212/amazon-OA

/*
Amazon Web Services (AWS) is a cloud computing platform with multiple servers. One of the servers is assigned to serve customer requests. There are n customer requests placed sequentially in a queue, where the ith request has a maximum waiting time denoted by wait[i]. That is, if the ith request is not served within wait[i] seconds, then the request expires and it is removed from the queue. The server processes the request following the First In First Out (FIFO) principle. The 1st request is processed first, and the nth request is served last. At each second, the first request in the queue is processed. At the next second, the processed request and any expired requests are removed from the queue.

Given the maximum waiting time of each request denoted by the array wait, find the number of requests present in the queue at every second until it is empty.

Note:

If a request is served at some time instant t, it will be counted for that instant and is removed at the next instant.
The first request is processed at time = 0. A request expires without being processed when time = wait[i]. It must be processed while time < wait[i].
The initial queue represents all requests at time = 0 in the order they must be processed.
Function Description

Complete the function findRequestsInQueue in the editor.

findRequestsInQueue has the following parameter:

int wait[n]: the maximum waiting time of each request
Returns

int[]: the number of requests in the queue at each instant until the queue becomes empty.

Example 1:

Input: wait = [2, 2, 3, 1]
Output: [4, 2, 1, 0]
Explanation:

  - time = 0 seconds, the 1st request is served. The number of requests in the queue is 4. queue = [1, 2, 3, 4].

  - time = 1 second, request 1 is removed because it is processed, request 4 (wait[3] = 1) is removed because time = wait[3] = 1 which exceeds its maximum waiting time. Also, request 2 is served. The number of requests in the queue at time = 1 seconds is 2. queue = [2, 3].

  - time = 2 seconds, request 2 is removed because it is processed, request 3 is served. The number of requests in the queue is 1. queue = [3].

  - time = 3 seconds, request 3 is removed because it is processed. The number of requests in the queue is 0. queue = [empty].
The answer is [4, 2, 1, 0].

Constraints:
1 ≤ n ≤ 10^5
1 ≤ wait[i] ≤ 10^5

*/

#include <bits/stdc++.h>

using namespace std;

vector<int> fifo_queue(vector<int> wait) {
    /*
    My approach is:

    At any point of time t, we need to identify two things: all tasks with wait[i] <= current time, and the task that is going to be processed. Also, pay attention to the fact the tasks are only processed in even seconds (0-indexed). So at t=0 we process a task, t=2 we process a task, and so on. 

    To meet these requirements, we can maintain two ordered sets.
    -> First set: Stores (wait[i], i). At any point in time t, we can iterate over the set and remove all those tasks where wait[i] <= t. 
    -> Second set: Store indices of tasks. From here, we can quickly see what is the beginning element of set as that will be the task we process. (of course after removal of those indices for which wait[i] <= current time). 

    Now for even seconds (t=0, 2...):
        -> from first set, remove set_one.begin() as long as wait[i] <= current time. Remove i from set_two along side.
        -> push set_one.size() to answer vector.
    For odd seconds (t=1,3...)
        -> remove set_two.begin() as this is the task that was being processed in previous second. remove it from set_one as well. 
        -> from first set, remove set_one.begin() as long as wait[i] <= current time. Remove i from set_two along side.
        -> push set_one.size() to answer.
    */

    set<pair<int, int> > set_one; // holds wait[i], i
    set<int> set_two; // holds i

    for(int i=0; i<wait.size(); i++){
        set_one.insert(make_pair(wait[i], i));
        set_two.insert(i);
    }

    vector<int> ans;
    for(int t=0; t<wait.size() && !set_one.empty(); t++){
        if(t%2==0){
            while(!set_one.empty() && (*set_one.begin()).first <= t){
                set_two.erase((*set_one.begin()).second);
                set_one.erase(set_one.begin());
            }
            // the least index in set_two is now picked up for processing
            ans.push_back(set_one.size());
        } else {
            // remove task that was picked up in previous second. Nothing is picked for processing in this second.
            int taskId = *set_two.begin(); // the set won't be empty as we're already putting that check in for loop.
            set_two.erase(taskId);
            set_one.erase(make_pair(wait[taskId], taskId));

            // remove other expired tasks
            while(!set_one.empty() && (*set_one.begin()).first <= t){
                set_two.erase((*set_one.begin()).second);
                set_one.erase(set_one.begin());
            }
            ans.push_back(set_one.size());
        }
    }
    return ans;
}

void print(vector<int> x) {
    for(int i=0; i<x.size(); i++)
        cout << x[i] << ", ";
    cout << endl;
}

int main() {
    print(fifo_queue(vector<int> {2,2,3,1})); // 4,2,1,0
    print(fifo_queue(vector<int> {3,2,1,4,0,3,0,5})); // 6,4,3,1,1,0
    /*
    Explanation for second example.
    At t=0, tasks 4 and 6 get expired. So we have 6 tasks remaining, and taks at index 0 gets picked up. [3,2,1,4,3,5]
    At t=1, 0th task gets completed and hence removed. Task at index 2 expires. So total tasks remaining: [2,4,3,5]
    At t=2, task at index 1 (of original array) gets expired. Task at index 3 gets picked for processing. [4,3,5]
    At t=3, task at index 3 completed processing. Task at index 5 gets expired. [5]
    At t=4, task at index 7 gets picked for processing. [5]
    At t=5, task at index 7 completes processing and hence pushed out. []
    */
    print(fifo_queue(vector<int> {1,1,1,3,2,1,4,5,5,7,8,0,9})); // 12,8,7,6,5,3,3,2,1,0 
}