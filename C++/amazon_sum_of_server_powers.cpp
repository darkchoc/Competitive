//Question: https://leetcode.com/discuss/interview-question/1759431/amazon-oa-sum-of-server-powers
//Question: https://leetcode.com/discuss/interview-question/1736639/solution-to-amazon-oa-2022-problem-sum-of-scores-of-subarray/1255065


/*
We are given an array. For each sub array, find minOfSubarray * sumOfSubarray. Return the sum of this.
Eg: [1,3,4]

min(1) * sum(1) = 1 * 1 =            1
min(1,3) * sum(1,3) = 1 * 4 =        4
min(1,3,4) * sum(1,3,4) = 1 * 8 =    8
min(3) * sum(3) = 3 * 3 =            9
min(3,4) * sum(3,4) = 3 * 7 =        21
min(4) * sum(4) =4 * 4 =             16
1+4+8+9+21+16 =                      59
*/

/*
Approach: For each element, check for how many subarrays will this be the minimum element. To do this, calculate index of element smaller than it on left and right. If current element is at index i, and smaller on left is at l, and smaller on right is at r, then subarrays having arr[i] as min will be (i-l)*(r-i). Basically start of the subarray can be anywhere from l+1 to i. And end of the subarray can be anywhere from i to r-1.

Now comes the complex part. 
The element A[l+1] would be part of (r-i) subarrays. (1 option for start, i.e. l+1 index, and r-i options for end index). Contribution to sum: A[l+1]*(r-i)
A[l+2] will be part of 2*(r-i) subarrays. (2 options for start, i.e l+1 and l+2, and r-i options for end index). Contribution to sum: A[l+2]*(2*(r-i))
...
..
A[i-1] will be part of (i-l-1)*(r-i) subarrays.
A[i] will be part of (i-l)*(r-i) subarrays.
Now,
A[r-1] will be part of (i-l) subarrays (i-l options for start, only one option for end, i.e. r-1)
A[r-2] will be part of (i-l)*2 subarrays (2 options for end: r-1 and r-2)
..
..
A[i+1] will be part of (i-l)*(r-i-1) subarrays.

Total sum of all these subarrays: A[l+1]*(r-i) + A[l+2]*2*(r-i) + A[l+3]*3*(r-i) + ... + A[i-1]*(i-l-1)*(r-i) + A[i]*(i-l)*(r-i) + A[r-1]*(i-l) + A[r-2]*(i-l)*2 + ... + A[i+1]*(i-l)*(r-i-1).

Adding and subtracting A[i]*(r-i)*(i-l)
= (r-i){A[l+1] + 2*A[l+2] + 3*A[l+3] + ... + (i-l-1)*A[i-1] + (i-l)*A[i]} + (i-l){A[r-1] + 2*A[r-2] + ... (r-i-1)*A[i+1] + (r-i)*A[i]} - A[i]*(r-i)*(i-l)

= (r-1){sum(A[i:i]) + sum(A[i-1:i]) + sum(A[i-2:i]) + ... sum(A[l+2:i]) + sum(A[l+1:i])} + (i-l){sum(A[i:i]) + sum(A[i:i+1]) + ... sum(A[i:r-1])} - A[i]*(r-i)*(i-l)

Now, let's define two arrays:
If we first creat a cummulative sum array: cummSumForward. -> cummSumForward[i] = sum(A[0:i])

To get first curly bracket, let's calculate another array: 
xSumForward. xSumForward[i] = 1*A[0] + 2*A[1] + ... (i+1)*A[i].
this can be calculate by doing: xSumForward[i] = xSumForward[i-1] + (i+1)*A[i], and xSumForward[0] = A[0]
When we want first curly bracket, it will be: xSumForward[i] - xSumForward[l] - something(let's call it p).
The xSumForward[i] - xSumForward[l] = (l+2)*A[l+1] + (l+3)*A[l+2] + ... + i*A[i-1] + (i+1)*A[i]
                                    = (l+1)(A[l+1] + A[l+2] + ... A[i-1] + A[i]) + {A[l+1] + 2*A[l+2] + ... (i-l-1)*A[i-1] + (i-l)*A[i]}
                                    = (l+1)(cummSumForward[i] - cummSumForward[l]) + firstCulyBracketSum
so firstCurlyBracketSum = xSumForward[i] - xSumForward[l] - (l+1)(cummSumForward[i] - cummSumForward[l]) . The last term "(l+1)(cummSumForward[i] - cummSumForward[l]" is p.

Now let's define another array:
xSumBackward. xSumBackward[i] = A[n-1] + 2*A[n-2] + 3*A[n-3] + ... (n-i)*A[i]
This can be calculated by doing: xSumBackward[i] = xSumBackward[i+1] + (n-i)*A[i], and xSumBackward[n-1]=A[n-1] 
The second curly bracket will be of the form: xSumBackward[i] - xSumBackward[r] - something(let's call it q).
The xSumBackward[i] - xSumBackward[r] = (A[n-1] + 2*A[n-2] + ... (n-i)*A[i]) - (A[n-1] + 2*A[n-2] + ... (n-r)A[r])
                                      = (n-r+1)*A[r-1] + (n-r+2)*A[r-2] + .. + (n-i-1)*A[i+1] + (n-i)*A[i]
                                      = (n-r)(A[r-1] + A[r-2] + ... A[i+1] + A[i]) + {A[r-1] + 2*A[r-2] + ... (r-i-1)*A[i+1] + (r-i)*A[i]}
                                      = (n-r)(cummSumForward[r-1] - cummSumForward[i-1]) + secondCurlyBracketSum
so secondCurlyBracketSum = xSumBackward[i] - xSumBackward[r] - (n-r)(cummSumForward[r-1] - cummSumForward[i-1]). The last term "(n-r)(cummSumForward[r-1] - cummSumForward[i-1])" is q.

So for every element i, our answer becomes:
    A[i] * totalSumOfSubarraysForWhichA_iIsMin = A[i] * [(r-1)*{xSumForward[i] - xSumForward[l] - (l+1)(cummSumForward[i] - cummSumForward[l])} + (i-l)*{xSumBackward[i] - xSumBackward[r] - (n-r)(cummSumForward[r-1] - cummSumForward[i-1])} - A[i]*(r-i)*(i-l)]


While calculating smaller element's index on left and right, take care of what happens in case of repeated elements. To handle this, we find strictly smaller element on left, and smaller or equal element on right. 

We iterate over the array and add all such sums to get final answer. Take mode at every step. 
*/

#include <bits/stdc++.h>
using namespace std;

int mod_ = 1000000007;

int sumOfScoresOfSubarray(vector<int> &A){
    int n = A.size();

    vector<long long> cummSumForward(n, 0);
    vector<long long> xSumForward(n, 0);
    cummSumForward[0] = (long long)A[0];
    xSumForward[0] = (long long)A[0];
    for(int i=1; i<n; i++){
        cummSumForward[i] = cummSumForward[i-1] + (long long)A[i];
        xSumForward[i] = xSumForward[i-1] + (i+1)*(long long)A[i];
    }
    vector<long long> xSumBackward (n, 0);
    xSumBackward[n-1] = (long long)A[n-1];
    for(int i=n-2; i>=0; i--){
        xSumBackward[i] = xSumBackward[i+1] + (n-i)*(long long)A[i];
    }

    vector<int> smallerIndexLeft;
    stack<int> st;
    for(int i=0; i<n; i++){
        while(!st.empty() && A[st.top()] > A[i])
            st.pop();
        if(st.empty())
            smallerIndexLeft.push_back(-1);
        else
            smallerIndexLeft.push_back(st.top());
        st.push(i);
    }
    while(!st.empty())
        st.pop();
    vector<int> smallerIndexRight;
    for(int i=n-1; i>=0; i--){
        while(!st.empty() && A[st.top()] >= A[i])
            st.pop();
        if(st.empty())
            smallerIndexRight.push_back(n);
        else
            smallerIndexRight.push_back(st.top());
        st.push(i);
    }
    reverse(smallerIndexRight.begin(), smallerIndexRight.end());

    long long int ans = 0;
    for(int i=0; i<n; i++){
        long long r = (long long)smallerIndexRight[i];
        long long l = (long long)smallerIndexLeft[i];
        long long xSumForward_l = (l==-1)?0:(long long)xSumForward[l];
        long long cummSumForward_l = (l==-1)?0:(long long)cummSumForward[l];
        long long sumTermOne = (r-i)*(xSumForward[i] - xSumForward_l - (l+1)*(cummSumForward[i] - cummSumForward_l));
        
        long long xSumBackward_r = (r==n)?0:(long long)xSumBackward[r];
        long long cummSumForward_iMinus1 = (i==0)?0:(long long)cummSumForward[i-1];
        long long sumTermTwo = (i-l)*(xSumBackward[i] - xSumBackward_r - (n-r)*(cummSumForward[r-1] - cummSumForward_iMinus1));

        long long sumTermThree = A[i]*(r-i)*(i-l);
        long long sum = (long long)A[i] * (sumTermOne + sumTermTwo - sumTermThree);
        ans += sum;
    }
    return (int)(ans%mod_);
}

int main(){
    vector<int> arr = {1,3,4};
    cout << sumOfScoresOfSubarray(arr) << endl;
}