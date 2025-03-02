/*
Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.

Example:

MovingAverage m = new MovingAverage(3);
m.next(1) = 1
m.next(10) = (1 + 10) / 2
m.next(3) = (1 + 10 + 3) / 3
m.next(5) = (10 + 3 + 5) / 3
*/

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param_1 = obj.next(val);
 */

#include <bits/stdc++.h>
using namespace std;

class MovingAverage {
private:
    int windowSize; // size of window
    int sum; // sum of currently added elements
    int count; // how many elements added in nums till now.
    vector<int> nums; // nums currently in the window (maybe partially filled)

public:
    MovingAverage(int windowSize){
        this->windowSize = windowSize;
        sum = 0;
        count = 0;
        nums.clear();
        nums.resize(windowSize, 0);
    }

    double next(int val){
        int idx = count%windowSize; // we are rotating around the array instead of pushing at the end
        // and popping from the front.
        sum += val - nums[idx]; // remove what is present at idx and replace with val.
        nums[idx] = val;
        count++;
        double avg = (double)sum/min(count, windowSize); // if not all elements have been added then we gotta
        // divide by count.

        // finally, before returning, let's try to limit "count" so that it doesn't end up overflowing
        // after a long time
        // if count becomes 2*size, we can change it back to size.
        if(count==2*windowSize) count = windowSize;
        return avg;
    }
};

int main() {
    // Test 1
    MovingAverage mv(3);
    cout << mv.next(1) << " " << mv.next(10) << " " << mv.next(3) << " " << mv.next(5) << " " << mv.next(4) << " " << mv.next(5) << " " << mv.next(10) << " " << mv.next(6) << " " << mv.next(2) << endl;
}
