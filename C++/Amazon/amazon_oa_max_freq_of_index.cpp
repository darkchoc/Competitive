/*
https://www.reddit.com/r/leetcode/comments/17vo5tt/amazon_oa_problem_how_to_do_it_in_on/

Given an array, with numbers, every number in the array represents an ID, At every position, there is a number, this means that ID was added or removed, if added, it increases the count of that ID upto that point, and if removed, it reduces the count of that ID upto that point. If the number is positive, means, it means an ID was added, if it is negative it means it was removed.

Lets take an example, Given a array like [6,6,3,-6].
Position 0 - we have a 6, means we added a ID 6
Position 1 - we have a 6, means we added a ID 6
Position 2 - we have a 3, means we added ID 3
Position 3 - we have a -6, mean we removed ID 6

So, the request is at every index, we need to find the number of maximum IDs in the array upto that point.

Lets take an example

Given an array like [6,6,3,-6]
The response should be [1,2,2,1]
This mean, at Position 0, we have added a 6, means, we so far have only one 6, so, the maximum IDs we have so far seen is 1. So at position 0, we have 1 in our answer result.
When we add the second 6, we shall have two 6s, so at position 1 in our answer result, we have a 2.
When we add a 3, we shall have two 6s and one 3, so, at position 2, our answer result will be a 2.
When we add a -6, we shall have removed one 6, means, the number of 6s has reduced by 1, so our maximum at that point will be 1, since we shall have one 6 and one 3.

If our request array is [6,6,3,-6,-3,-6]
Our result array will be [1,2,2,1,1,0]

If our request array is [1, 2, 1, 1, 1, 2, -1, -1, 2, -1, 2, -1, -2, -2, -2, -2]
Our result array is [1,1,2,3,4,4,3,2,3,3,4,4,3,2,1,0]

NOTE: Anything slower than O(n) will result into into a TLE

Constraints
Its guaranteed arr[i] will never be 0
1<=arr.length>=10^7


I followed approach of having 2 maps. One keeping element to frequency count and other keeping track of which frequency has what elements.
One optimization was that instead of storing all elements that have a certain frequency, we can just keep count of how many elements have a certain frequency. 
So instead of using map<int, set<int> > freqToEles, we can use map<int, int> freqToEles.
Because if a certain element has achieved frequency x, it must have achieved x-1. So when we remove an element, we can simply decrement freqToEles[currentFreqOfElementBeingRemoved] and if this becomes 0, we can remove this freq from the map as this is no longer the largest frequency in map.

The commented code is the one that I implemented earlier. Then I modifed it as described above.
*/

#include <bits/stdc++.h>
using namespace std;

void printMaxFreq(vector<int> indices) {
    // map<int, set<int> > freqToEles;
    map<int, int> freqToEles;
    map<int, int> eleToFreq;
    vector<int> ans;
    for(int i=0; i<indices.size(); i++){
        int ele = abs(indices[i]);
        if(indices[i] > 0) {
            // add element
            if(eleToFreq.find(ele)==eleToFreq.end()){
                eleToFreq[ele] = 1;
                // freqToEles[1].insert(ele);
                freqToEles[1]++;
            } else {
                int oldFreq = eleToFreq[ele];
                eleToFreq[ele]++;
                // freqToEles[oldFreq].erase(ele);
                // if(freqToEles[oldFreq].empty())
                //     freqToEles.erase(oldFreq);
                // freqToEles[oldFreq+1].insert(ele);
                freqToEles[oldFreq+1]++;
            }
        } else {
            // remove ele
            int oldFreq = eleToFreq[ele];
            // freqToEles[oldFreq].erase(ele);
            // if(freqToEles[oldFreq].empty())
            //     freqToEles.erase(oldFreq);
            freqToEles[oldFreq]--;
            if(freqToEles[oldFreq]==0)
                freqToEles.erase(oldFreq);

            eleToFreq[ele]--;
            if(eleToFreq[ele]==0)
                eleToFreq.erase(ele);
            else{
                // freqToEles[oldFreq-1].insert(ele);
            }
        }
        // if(freqToEles.size())
        //     ans.push_back(freqToEles.rbegin()->first);
        // else
        //     ans.push_back(0);
        ans.push_back(freqToEles.size());
    }
    for(int i=0; i<ans.size(); i++)
        cout << ans[i] << ", ";
    cout << endl;
}

int main() {
    printMaxFreq({6,6,3,-6}); // 1 2 2 1
    printMaxFreq({6,6,3,-6,-3,-6}); // 1 2 2 1 1 0
    printMaxFreq({1,2,1,1,1,2,-1,-1,2,-1,2,-1,-2,-2,-2,-2}); // 1 1 2 3 4 4 3 2 3 3 4 4 3 2 1 0 
}