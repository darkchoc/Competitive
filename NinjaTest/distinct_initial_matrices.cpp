/*
For a A * B matrix of all distinct numbers from 1 to A * B, we first sort each column and then concatenate all columns in increasing order of indices to form an array of size A * B. Columns are numbered in increasing order from left to right.

For example, if matrix is

[1 5 6]
[3 2 4]

We first sort all columns to get

[1 2 4]
[3 5 6]

Now, we concatenate columns in increasing order of indices to get an array

[1, 3, 2, 5, 4, 6]
Given this final array, you have to count how many distinct initial matrices are possible. Return the required answer modulo 10^9+7.

Two matrices are distinct if:

Either their dimensions are different.
Or if any of the corresponding row in two matrices are different.
Example:

If input array is [1, 3, 2, 4], distinct initial matrices possible are:

[1 3 2 4]
-----------------------
[1 2]
[3 4]
-----------------------
[1 4]
[3 2]
-----------------------
[3 2]
[1 4]
-----------------------
[3 4]
[1 2]
-----------------------

that is, a total of 5 matrices.

*/


#include <bits/stdc++.h>

using namespace std;

int mod_ = 1000000007;

long long int factorial(long long int n){
    if(n==1)
        return 1;
    else return (n * (factorial(n-1)%mod_))%mod_;
}

long long int powmod(long long int n, long long int p){
    long long int result = 1;
    long long int val = n;
    while(p){
        if(p&1){
            result = (result*val)%mod_;
        }
        p = p/2;
        val = (val*val)%mod_;
    }
    return result%mod_;
}

int solve(vector<int> &A) {
    if(A.size()==1)
        return 1;
    int n = A.size();
    vector<int> increasingSeq (n, 1);
    for(int i=1; i<n; i++){
        if(A[i] > A[i-1]){
            increasingSeq[i] = increasingSeq[i-1]+1; 
        }
    }
 
    long long int ans = 1; //consider case when there are n columns. 
    for(int elementsInEachColumn=2; elementsInEachColumn<=n/2; elementsInEachColumn++){
        if(n%elementsInEachColumn == 0){
            //possible configuration
            long long int numColumns = (long long int)n/(long long int)elementsInEachColumn;
            //now verify that given array has increasing sequence of size elementsInEachColumn
            bool flag = true;
            for(int i=elementsInEachColumn-1; i<n; i=i+elementsInEachColumn){
                if(increasingSeq[i] < elementsInEachColumn){
                    flag = false;
                    break;
                }
            }
            if(flag==false)
                continue;
            ans = (ans + powmod(factorial((long long int)elementsInEachColumn), (long long int)numColumns)%mod_)%mod_;
        }
    }
    if(increasingSeq[n-1]==n){
    	//last case when complete array is sorted so there can be just 1 column.
        ans = (ans + factorial((long long int)n)%mod_)%mod_;
    }
    return ans%mod_;
}

int main(){
	int n;
	int x;
	cin >> n;
	vector<int> A;
	for(int i=0; i<n; i++){
		cin >> x;
		A.push_back(x);
	}
	cout << solve(A);
	return 0;
}