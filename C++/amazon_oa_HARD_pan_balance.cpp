/*
SUPERBBB QUESTION. Took too long to implement. Had to go through one comment mentioned within the thread.

https://www.reddit.com/r/leetcode/comments/1aqhtty/amazon_oa_pan_balance/

In one of the warehouses of Amazon, a pan balance is used to weigh and load the parcels for delivery. 

A pan balance has 2 pans, and each of the pans can contain one parcel. Due to some defect, one of the pans shows an extra erroneous weight wt. A pair of parcels is said to be balanced if they show the same weight on the pan balance. Since one of our pans is heavier by the amount wt, the absolute difference in parcel weight must be wt. 

Given the weights of n parcels, weight[n], and the erroneous weight wt, find the number of ways to group these parcels into pairs such that every pair of the group is balanced. Since the answer can be large, compute it module 10^9 + 7. Technically, the task is to find out the number of pairs that can be formed from the weight array which have an absolute difference equal to wt. If there are no such pairs, you have to return 0. 

Note:
 - A parcel can not be present in more than one pair in a group
 - Two groups are different if at least one of their pairs contains a different pair of parcels. The pairs at indices (i, j) and (j, i) are considered the same.
 - If there are no such pairs, you have to return 0. 

 Example:
 Input : weight = [4, 5, 5, 4, 4, 5, 2, 3], wt = 1
 Output: 6
 Explanation: We can make following pairings (indices are mentioned): [(1,2),(3,4),(5,6),(7,8)], [(1,2),(3,5),(4,6),(7,8)], [(1,3),(2,4),(5,6),(7,8)], [(1,3),(2,5),(4,6),(7,8)], [(1,6),(2,4),(3,5),(7,8)], [(1,6),(2,5),(3,4),(7,8)]
 In all these groups, the absolute difference in weights of each pair of parcels equals 1.


Example 2:
Input: weight = [4,5,6,3], wt = 1
Output: 1 [(1,4),(2,3)]

Example 3:
Input: weight = [0,1,1,2,2,3], wt = 1
Output: 4
Explanation: [(1,2),(3,4),(5,6)], [(1,2),(3,5),(4,6)], [(1,3),(2,4),(5,6)], [(1,3),(2,5),(3,6)]

Example 4:
Input: weight = [0,1,1,2,2,3,3,4], wt = 1
Output: 8
Explanation: [(1,2),(3,4),(5,6),(7,8)], [(1,2),(3,4),(5,8),(6,7)], [(1,2),(3,5),(4,6),(7,8)], [(1,2),(3,5),(4,7),(6,8)], [(1,3),(2,4),(5,6),(7,8)], [(1,3),(2,4),(5,7),(6,8)], [(1,3),(2,5),(4,6),(7,8)], [(1,3),(2,5),(4,7),(6,8)]

Example 5:
Input: weight = [2,2,3,3,3,4], wt = 1
Output: 6
Explanation: [(1,3),(2,4),(5,6)], [(1,3),(2,5),(4,6)], [(1,4),(2,3),(5,6)], [(1,4),(2,5),(3,6)], [(1,5),(2,3),(4,6)], [(1,5),(2,4),(3,6)] 
*/

#include <bits/stdc++.h>
using namespace std;

long long int mod_ = (long long int)1000000007;

long long int powMod(long long int x, long long int p){
    //gives (x^p)%mod
    long long int result = (long long int)1;
    while(p){
        if(p%2==1)
            result = (result*x)%mod_;
        x = (x*x)%mod_;
        p = p/(long long int)2;
    }
    return result;
}

long long int nCr(int n, int r, vector<int> &factDp){
    int numerator = factDp[n];
    int denominator = (factDp[r]*factDp[n-r])%mod_;
    // now do mod division
    // (A/B)%mod = (A%mod * (B^-1)%mod)%mod
    // Now (B^-1)%mod is modular inverse of B. For prime mod, (B^-1)%mod = (B^(mod-2))%mod.
    // So (A/B)%mod = (A%mod * (B^(mod-2))%mod)%mod;

    // VERY IMPORTANT to convert all of these to long long int as otherwise I was getting wrong answers.
    int ncr =  ((numerator%mod_) * (powMod((long long int)denominator, (long long int)(mod_-2))%mod_))%mod_;
    return ncr;
}

void fillFactDp(vector<int> &factDp){
    factDp[0]=1;
    for(int i=1; i<factDp.size(); i++)
        factDp[i] = (factDp[i-1]*i)%mod_;
}

int findWays(vector<int> weight, int wt) {
    if(weight.size()%2==1) return 0;
    
    map<int, int> freq;
    int maxFreq = 0;

    for(int i=0; i<weight.size(); i++){
        freq[weight[i]]++;
        maxFreq = max(maxFreq, freq[weight[i]]);
    }
    
    vector<int> factDp (maxFreq+1);
    fillFactDp(factDp);
    int ans = 1;

    for(map<int, int>::iterator it=freq.begin(); it!=freq.end(); it++){
        if(it->second == 0) continue; // means these items have already been used for a previous pairing.
        int currentCnt = it->second;
        int currentWt = it->first;
        int itemsOfHigherWeight = freq[currentWt + wt];
        if(itemsOfHigherWeight < currentCnt) return 0;
        int ways = (nCr(itemsOfHigherWeight, currentCnt, factDp) * factDp[currentCnt])%mod_;
        // update count of higher weight items
        freq[currentWt + wt] = freq[currentWt + wt] - currentCnt; 

        ans = (ans*ways)%mod_;
    }
    return ans;
}

int main() {
    cout << findWays({4,5,5,4,4,5,2,3}, 1) << endl; // 6
    cout << findWays({4,5,6,3}, 1) << endl; // 1
    cout << findWays({0,1,1,2,2,3}, 1) << endl; // 4
    cout << findWays({0,1,1,2,2,3,3,4}, 1) << endl; // 8
    cout << findWays({2,2,3,3,3,4}, 1) << endl; // 6
}