/*
https://leetcode.ca/all/759.html

759. Employee Free Time
We are given a list schedule of employees, which represents the working time for each employee.

Each employee has a list of non-overlapping Intervals, and these intervals are in sorted order.

Return the list of finite intervals representing common, positive-length free time for all employees, also in sorted order.

Example 1:

Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
Output: [[3,4]]
Explanation:
There are a total of three employees, and all common
free time intervals would be [-inf, 1], [3, 4], [10, inf].
We discard any intervals that contain inf as they aren't finite.
 

Example 2:

Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
Output: [[5,6],[7,9]]
 

(Even though we are representing Intervals in the form [x, y], the objects inside are Intervals, not lists or arrays. For example, schedule[0][0].start = 1, schedule[0][0].end = 2, and schedule[0][0][0] is not defined.)

Also, we wouldn't include intervals like [5, 5] in our answer, as they have zero length.

Note:

schedule and schedule[i] are lists with lengths in range [1, 50].
0 <= schedule[i].start < schedule[i].end <= 10^8.
*/

/*
First thought: What if we create one array for start of the shift, and another for end of the shift. We sort both of them. Then, we iterate on both.

If start[i] <= end[j], an employee is starting their shift. Put the start time in a stack. When end[j] < start[i], that means employee is ending
their shift, so pop from the stack. If the stack becomes empty, that means we are starting an interval of free time. So create a new interval and
set it's start time to end[j]. Now, when we get the next starting time of an employee, we must first close this free interval by setting it's end
time to start[i]. Continue like this.


Approach 2: We can first create a list of intervals (by extracting each employee's intervals into one common list). Then sort all of them by start time.
Then we merge overlapping intervals. After this, iterate over intervals and there would be a free interval between any two of the intervals in the merged
intervals list.
*/

#include <iostream>
using namespace std;

struct Interval {
    int start;
    int end;
    Interval(int x, int y): start(x), end(y) {};
};

vector<Interval> findFreeTime(vector<vector<Interval> > employeeShifts) {
    vector<int> startTime;
    vector<int> endTime;
    for(int i=0; i<employeeShifts.size(); i++) {
        for(int j=0; j<employeeShifts[i].size(); j++) {
            startTime.push_back(employeeShifts[i][j].start);
            endTime.push_back(employeeShifts[i][j].end);
        }
    }

    sort(startTime.begin(), startTime.end());
    sort(endTime.begin(), endTime.end());

    stack<int> st; // holds employee's start time
    vector<Interval> freeIntervals;
    Interval freeInterval(-1, -1);
    
    int i = 0, j = 0;
    while(i < startTime.size()){
        if(startTime[i] <= endTime[j]){
            if(st.empty()) {
                // close current free time interval
                if(i!=0) {  // avoid running this logic for the very first shift
                    freeInterval.end = startTime[i];
                    freeIntervals.push_back(freeInterval);
                    freeInterval.start = -1;
                    freeInterval.end = -1;
                }
            }
            st.push(startTime[i]);
            i++;
        } else {
            st.pop();
            if(st.empty()){
                // means a new free interval has started. Moreover, there are no employees that will be starting shift at this very 
                // moment (at time=end[j]) because if there is an employee starting a shift and another employee ending the shift 
                // at the same time, then we are first adding the employee and only then removing other employee.
                freeInterval.start = endTime[j];
            }
            j++;
        }
    }
    return freeIntervals;
}

vector<Interval> findFreeTimeApproach2(vector<vector<Interval> > employeeShifts) {
    vector<Interval> allIntervals;
    // flatten the lists to create one list of intervals
    for(int i=0; i<employeeShifts.size(); i++)
        for(int j=0; j<employeeShifts[i].size(); j++)
            allIntervals.push_back(employeeShifts[i][j]);
        
    // sort this list based on start time and then end time
    sort(allIntervals.begin(), allIntervals.end(), [](Interval &a, Interval &b){ 
            return (a.start==b.start)?(a.end < b.end):(a.start < b.start);
        }
    );

    // merge intervals in a new list
    vector<Interval> mergedIntervals;
    Interval temp = allIntervals[0];
    int i = 1;
    while(i < allIntervals.size()){
        if(allIntervals[i].start <= temp.end) {
            // intervals overlap
            temp.end = max(temp.end, allIntervals[i].end);
        } else {
            mergedIntervals.push_back(temp);
            temp = allIntervals[i];
        }
        i++;
    }
    mergedIntervals.push_back(temp);

    // now construct free time interval array by traversing on merged intervals
    vector<Interval> freeIntervals;
    for(int i=1; i<mergedIntervals.size(); i++) 
        freeIntervals.push_back(Interval(mergedIntervals[i-1].end, mergedIntervals[i].start));
    
    return freeIntervals;
}

void printIntervals(vector<Interval> freeIntervals) {
    cout << "[";
    for(int i=0; i<freeIntervals.size(); i++) {
        cout << "[" << freeIntervals[i].start << "," << freeIntervals[i].end << "]";
        if(i!=freeIntervals.size()-1)
            cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    printIntervals(findFreeTime({{Interval(1,2), Interval(5,6)}, {Interval(1, 3)}, {Interval(4,10)}})); // [[3,4]]
    printIntervals(findFreeTime({{Interval(1,3), Interval(6,7)}, {Interval(2, 4)}, {Interval(2,5), Interval(9, 12)}})); // [[5,6], [7,9]]

    printIntervals(findFreeTimeApproach2({{Interval(1,2), Interval(5,6)}, {Interval(1, 3)}, {Interval(4,10)}})); // [[3,4]]
    printIntervals(findFreeTimeApproach2({{Interval(1,3), Interval(6,7)}, {Interval(2, 4)}, {Interval(2,5), Interval(9, 12)}})); // [[5,6], [7,9]]
}