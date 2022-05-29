//Question: https://leetcode.com/discuss/interview-question/1906290/Amazon-or-OA
/*
There are n processors. Each processor has some jobs scheduler already, given in the array jobs. We are required to schedule k more jobs in total. Assign them to the processors such that the difference between max and min jobs that a processor has to execute is minimum. 
Eg: If there are 3 processors and they already have (2, 6, 3) jobs scheduled and we have to schedule k=3 more jobs, we can get: 4,6,4 as final numbers and min diff would be (2).
*/

#include <bits/stdc++.h>
using namespace std;

long long minDifference(int n, vector<int> &jobs, long long k){
    if(n==1)
        return (long long)0;
    sort(jobs.begin(), jobs.end());
    long long jobsRequiredToEqualizeAll = 0;
    for(int i=0; i<n; i++)
        jobsRequiredToEqualizeAll += (long long)(jobs[n-1] - jobs[i]);
    if(k >= jobsRequiredToEqualizeAll){
        //either range will be 0 or 1
        k -= jobsRequiredToEqualizeAll;
        if(k%n)
            return (long long)1;
        else
            return (long long)0;
    }
    //otherwise, our max is fixed to jobs[n-1]
    long long max_ = jobs[n-1];
    //iterate over jobs to increase min
    long long min_ = jobs[0];
    for(int i=0; i<n-1; i++){
        if(jobs[i]==jobs[i+1])
            continue; //both are at same level, continue for the time being, we'll handle them together later
        //if not same
        //now say i=5, then we know that we have 6 processors having jobs[i] jobs scheduled on them.
        long long numJobsRequiredToCoverDiff = (long long)(jobs[i+1] - jobs[i])*(long long)(i+1);
        if(k >= numJobsRequiredToCoverDiff){
            min_ = jobs[i+1];
            k -= numJobsRequiredToCoverDiff; //all processors before i+1 indexed processor get jobs such that their values become equal to jobs[i+1].
        } else {
            //we cannot make all processors have jobs equal to jobs[i+1].
            //But each processor can be assigned at least k/(i+1) jobs. Eg: If we have 8 jobs and 3 processors (i==2), we can assign at least 2 jobs to each of the processor, and 1 additonal job to two of the processors. This means, our min_ would increase by k/(i+1)
            min_ += k/((long long)i + 1);
            return max_ - min_;
        }
    }
    return 0; //just to avoid compilation issues.
}

int main(){
    int numProcessors = 4;
    vector<int> alreadyScheduled = {1,3,5,6};
    long long jobsToBeScheduled = 4;
    cout << minDifference(numProcessors, alreadyScheduled, 1) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 2) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 3) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 4) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 5) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 6) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 7) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 8) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 9) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 10) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 11) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 12) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 13) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 14) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 15) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 16) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 17) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 18) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 19) << endl;
    cout << minDifference(numProcessors, alreadyScheduled, 20) << endl;
}