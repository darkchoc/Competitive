/*
https://www.reddit.com/r/leetcode/comments/19b2h09/really_hard_problem_in_amazon_oa/

The inputs are a string, integer x and integer y.

String is made up of 0, 1 and !, each ! can be either 0 or 1
Every subsequence of 01 in the string can produce error x
Every subsequence of 10 in the string can produce error y
0<=len(string)<=50000, 0<=x<=50000, 0<=y<=50000
Return the minimum error count modulo 10^9.

Example:

string=01!!, x=2, y=3, there're 4 cases:

0100 => errorCount is 2 + 3*2 = 8
0101 => errorCount is 2*3+3 = 9
0110 => errorCount is 2*2+2*3=10
0111 => errorCount is 2*3=6
so the result is 6

Example 2:
string=!!!!, x=2, y=5
we can replace all ! to 0 or 1, so there will be no 01 or 10 in the string, the result is 0.

Example 3:
string = 010!1!00!01!, x=4, y=3
-> 010 0 1 0 00 0 01 0  -> (1*3 + 2*2 + 5*1)*2 + (1*8 + 1*6 + 1*1)*5 = 24 + 75 = 99
-> 010 0 1 0 00 0 01 1  -> (1*4 + 2*3 + 5*2)*2 + (1*7 + 1*5)*5 = 40 + 60 = 100
-> 010 0 1 0 00 1 01 0  -> (1*4 + 2*3 + 3*2 + 1*1)*2 + (1*7 + 1*5 + 1*2 + 1*1)*5 = 34 + 75 = 109
-> 010 0 1 0 00 1 01 1  -> (1*5 + 2*4 + 3*3 + 1*2)*2 + (1*6 + 1*4 + 1*1)*5 = 48 + 55 = 103
-> 010 0 1 1 00 0 01 0  -> (1*4 + 2*3 + 4*1)*2 + (1*7 + 2*5 + 1*1)*5 = 28 + 90 = 118
-> 010 0 1 1 00 0 01 1  -> (1*6 + 2*4)*2 + (1*5 + 2*4 + 4*2)*5 = 28 + 105 = 133
-> 010 0 1 1 00 1 01 0  -> (1*5 + 2*4 + 2*2 + 1*1)*2 + (1*6 + 2*4 + 1*2 + 1*1)*5 = 36 + 85 = 121
-> 010 0 1 1 00 1 01 1  -> (1*6 + 2*5 + 2*3 + 1*2)*2 + (1*5 + 2*3 + 1*1)*5 = 48 + 60 = 108
-> 010 1 1 0 00 0 01 0  -> (1*4 + 1*3 + 5*1)*2 + (1*7 + 2*6 + 1*1)*5 = 24 + 100 = 124
-> 010 1 1 0 00 0 01 1  -> (1*5 + 1*4 + 5*2)*2 + (1*6 + 2*5)*5 = 38 + 80 = 118
-> 010 1 1 0 00 1 01 0  -> (1*5 + 1*4 + 3*2 + 1*1)*2 + (1*6 + 2*5 + 1*2 + 1*1)*5 = 32 + 95 = 127
-> 010 1 1 0 00 1 01 1  -> (1*6 + 1*5 + 3*3 + 1*2)*2 + (1*5 + 2*4 + 1*1)*5 = 44 + 70 = 114
-> 010 1 1 1 00 0 01 0  -> (1*5 + 1*4 + 4*1)*2 + (1*6 + 3*5 + 1*1)*5 = 26 + 110 = 136
-> 010 1 1 1 00 0 01 1  -> (1*6 + 1*5 + 4*2)*2 + (1*5 + 3*4)*5 = 38 + 85 = 123
-> 010 1 1 1 00 1 01 0  -> (1*6 + 1*5 + 2*2 + 1*1)*2 + (1*5 + 3*4 + 1*2 + 1*1)*5 = 32 + 100 = 132
-> 010 1 1 1 00 1 01 1  -> (1*7 + 1*6 + 2*3 + 1*2)*2 + (1*4 + 3*3 + 1*1)*5 = 42 + 70 = 112

so minimum is 99. 

What I can see is that minimum is either attained when we put all 0s or all 1s in place of "!". To verify this, I can generate all permutations for small strings and check their cost.

Well, I tried proving it but wasn't able to. It got proved when x = y, but not otherwise. You can refer calculations below if you ever feel like seeing them, but what I did realize is that we equation would change when values of x and y are very different. So I tried adding more cases where x and y are far apart, and yes, unfortunately the brute force answer was smaller than the answer obtained on substituting all ! with either 0 or 1.

So need to think more. 


EXPLANATION:
I still don't know how the best case scenario is filling 0s followed by 1s when x < y or 
1s followed by 0s when y < x. But the explanation is for finding out cost when we have decided on one of the approaches. 

Let's say we want to fill 0s before 1s (and x < y). 
First thing to understand is that all non-exclamation mark characters will contribute a fixed cost that can be calculated before. Now, when we change an exclamation to 0 or 1, we incur some additional cost.

Say we're at an exclamation mark and make it 0. This means all exclamamtions before it were also converted to 0. So now, all 1s before this exclamation (== original ones before this exclamation) will contribute y cost. All 1s after this exclamation (don't include exclamations after this exclamation at the moment) will contribute x cost as they'll form a 01 pair with the current exclamaition. 
 -> So, if we make current exclamation 0:
    extra cost bcoz of this exclamation interating with other non-exclamation chars = (1s before this) * y + (1s after this) * x
Similaryly, if we make current exclamation 1: 
    extra cost bcoz of this exclamation interacting with other non-exclamation chars = (0s before this) * x + (0s after this) * y

Once we have these two arrays (costIfWePut0, costIfWePut1), we want to see what will be cost if we convert some initial number of exclamations to 0 and set remainging to 1. 
Consider an example: Suppose there are 8 exclamations, we convert first 4 to 0 and next 4 to 1.
So total extra cost would be = cost of converting first 4 to 0 + cost of converting last 4 to 1 + cost incurred when these exclamations interact with each other. 

We can see that first part: cost of converting first 4 to 0, is similar to a prefix sum over the costIfWePut0 array. So let's create array costOfPutting0sTillHere, where costOfPutting0sTillHere[i] gives sum(costOfPutting0[j] for all j <= i where s[j]=='!')

Similarly, cost of converting last 4 exclamations to 1 can be calculated if we keep a suffix array, costOfPutting1sAfterHere, where costOfPutting1sAfterHere[i] will give sum(costOfPutting1[j] for all j >= i where s[j]=='!').

So the first term of total extra cost will be costOfPutting0sTillHere[i]
Second term would be costOfPutting1sAfterHere[i+1]
And now coming to third term. What is the extra cost because of exclamations interacting with each other? It is simply the first 4 exclamations pairing up with next 4, forming 16 sequences in total of 01 type. So this third term can be calculated simply by: countOfExclamationsTillMe[i]*(totalExclamation - countOfExclamationsTillMe[i]) * x.

*/

#include <bits/stdc++.h>
using namespace std;

int getCostOfString(string s, int x, int y){
    int n = s.length();
    int countZeros = 0, countOnes = 0;
    int cost = 0;
    for(int i=n-1; i>=0; i--){
        if(s[i]=='0') {
            cost += x*countOnes;
            countZeros++;
        } else {
            cost += y*countZeros;
            countOnes++;
        }
    }
    return cost;
}

void recurse(string s, int ind, int x, int y, string &ansString, int &cost){
    if(ind == s.length()) {
        int currentCost = getCostOfString(s, x, y);
        if (currentCost < cost){
            cost = currentCost;
            ansString = s;
        }
        return;
    }
    if(s[ind]!='!') recurse(s, ind+1, x, y, ansString, cost);
    else {
        recurse(s.substr(0, ind) + "0" + s.substr(ind+1), ind+1, x, y, ansString, cost); 
        recurse(s.substr(0, ind) + "1" + s.substr(ind+1), ind+1, x, y, ansString, cost);
    }
}

int bruteForceMinErrorCost(string s, int x, int y){
    string ansString;
    int cost = INT_MAX;
    recurse(s, 0, x, y, ansString, cost);
    // cout << ansString << endl;
    return cost;
}

int getMinErrorCost(string s, int x, int y) {
    string allZeros = s;
    string allOnes = s;
    for(int i=0; i<s.length(); i++){
        if(s[i]=='!') {
            allZeros[i]='0';
            allOnes[i]='1';
        } 
    }
    return min(getCostOfString(allZeros, x, y), getCostOfString(allOnes, x, y));  
}

int fill0sBefore1s(string s, int x, int y, int answerWhenAllZeroOrOne){
    // we will fill 0s first and then 1s. 
    // x < y is true.
    int fixedCost = 0;
    int countZeros = 0, countOnes = 0;
    int n = s.length();
    for(int i=0; i<n; i++){
        if(s[i]=='0'){
            fixedCost += countOnes*y;
            countZeros++;
        } else if (s[i]=='1'){
            fixedCost += countZeros*x;
            countOnes++;
        }
    }
    int totalZeros = countZeros, totalOnes = countOnes, totalExclamations = n - countOnes - countZeros;

    vector<int> countOf0sTillMe (n); // including me
    vector<int> countOf1sTillMe (n); // including me
    vector<int> countOfExclamationsTillMe (n); // including me
    countOnes = 0, countZeros = 0;
    int countExclamations = 0;
    for(int i=0; i<n; i++){
        if(s[i]=='!') countExclamations++;
        else if(s[i]=='0') countZeros++;
        else countOnes++;
        
        countOf0sTillMe[i] = countZeros;
        countOf1sTillMe[i] = countOnes;
        countOfExclamationsTillMe[i] = countExclamations;
    }

    vector<int> costIfWePut0 (n);
    vector<int> costIfWePut1 (n);
    for(int i=0; i<n; i++){
        if(s[i]=='!'){
            costIfWePut0[i] = countOf1sTillMe[i]*y + (totalOnes - countOf1sTillMe[i])*x;
            costIfWePut1[i] = countOf0sTillMe[i]*x + (totalZeros - countOf0sTillMe[i])*y;
        }
    }
    vector<int> costOfPutting0sTillHere (n);
    for(int i=0; i<n; i++){
        if(s[i]=='!'){
            costOfPutting0sTillHere[i] = costIfWePut0[i] + ((i>0)?costOfPutting0sTillHere[i-1]:0);
        } else {
            costOfPutting0sTillHere[i] = (i>0)?costOfPutting0sTillHere[i-1]:0;
        }
    }
    vector<int> costOfPutting1sFromHere (n);
    for(int i=n-1; i>=0; i--){
        if(s[i]=='!'){
            costOfPutting1sFromHere[i] = costIfWePut1[i] + ((i<n-1)?costOfPutting1sFromHere[i+1]:0);
        } else {
            costOfPutting1sFromHere[i] = (i<n-1)?costOfPutting1sFromHere[i+1]:0;
        }
    }
    int totalCost = answerWhenAllZeroOrOne;
    for(int i=0; i<n; i++){
        if(s[i]=='!'){
            // put 0 here and 1 in all exclamations after this
            int extraCost = costOfPutting0sTillHere[i] + 
                            ((i<n-1)?costOfPutting1sFromHere[i+1]:0) + 
                            (countOfExclamationsTillMe[i] * (totalExclamations - countOfExclamationsTillMe[i]) * x);
            totalCost = min(totalCost, fixedCost + extraCost);
        }
    }
    return totalCost;
}

int getMinErrorCostCorrect(string s, int x, int y){
    // we need to put either 0s first and then 1s, or 1s first and then 0s.
    // If x == y, we can put all 0s or all 1s
    // If x < y, we should put all 0s first and then 1s
    // If x > y, we should put all 1s first and then 0s
    // Now, instead of writing code 2 times for last 2 cases, we can write code for first case, an for second case, we can simply convert all 0s to 1s and 1s to 0s and swap x and y and call the same function again. 
    
    int answerWhenAllZeroOrOne = getMinErrorCost(s, x, y);
    if(x == y){
        // using old function that was incorrect in general but correct for this case.
        return answerWhenAllZeroOrOne;
    }

    if(x < y){
        return fill0sBefore1s(s, x, y, answerWhenAllZeroOrOne);
    } else {
        string new_s = s;
        for(int i=0; i<s.length(); i++){
            if(new_s[i]=='1') new_s[i]='0';
            else if(new_s[i]=='0') new_s[i]='1';
        }
        return fill0sBefore1s(new_s, y, x, answerWhenAllZeroOrOne);
    }
}  


int main() {

    cout << "Test 1: " << getMinErrorCost("01!!", 2, 3) << endl; // 6
    cout << getMinErrorCostCorrect("01!!", 2, 3) << endl; // 6
    cout << bruteForceMinErrorCost("01!!", 2, 3) << endl; // 6
    cout << "Test 2: " << getMinErrorCost("!!!!", 2, 5) << endl; // 0 
    cout << getMinErrorCostCorrect("!!!!", 2, 3) << endl; // 6
    cout << bruteForceMinErrorCost("!!!!", 2, 5) << endl;
    cout << "Test 3: " << getMinErrorCost("010!1!00!01!", 2, 5) << endl; // 99
    cout << getMinErrorCostCorrect("010!1!00!01!", 2, 5) << endl; // 99
    cout << bruteForceMinErrorCost("010!1!00!01!", 2, 5) << endl; // 2^4 options, ans = 99
    cout << "Test 4: " << getMinErrorCost("010!01!!1!!010!00", 3, 2) << endl; // 124
    cout << getMinErrorCostCorrect("010!01!!1!!010!00", 3, 2) << endl; // 124
    cout << bruteForceMinErrorCost("010!01!!1!!010!00", 3, 2) << endl; // 2^6 options, ans = 124
    cout << "Test 5: " << getMinErrorCost("01!!01!!11!!01!0!0!0!1!!", 4, 2) << endl; // 300 
    cout << getMinErrorCostCorrect("01!!01!!11!!01!0!0!0!1!!", 4, 2) << endl; // 300 
    cout << bruteForceMinErrorCost("01!!01!!11!!01!0!0!0!1!!", 4, 2) << endl; // 2^12 options, ans = 300
    cout << "Test 6: " << getMinErrorCost("01!!01!!11!!01!0!0!0!1!!", 10, 2) << endl; //  firstApproach(552)
    cout << getMinErrorCostCorrect("01!!01!!11!!01!0!0!0!1!!", 10, 2) << endl; // 520
    cout << bruteForceMinErrorCost("01!!01!!11!!01!0!0!0!1!!", 10, 2) << endl; // 2^12 options, ans =  520
    cout << "Test 7: " << getMinErrorCost("01!!01!!11!!01!0!0!0!1!!", 4, 25) << endl; //  firstApproach(1524)
    cout << getMinErrorCostCorrect("01!!01!!11!!01!0!0!0!1!!", 4, 25) << endl; // 1400
    cout << bruteForceMinErrorCost("01!!01!!11!!01!0!0!0!1!!", 4, 25) << endl; // 2^12 options, ans = 1400
    cout << "Test 8: " << getMinErrorCost("01!!01!!11!!01!0!0!0!1!!", 41, 2) << endl; // firstApproach(1854) 
    cout << getMinErrorCostCorrect("01!!01!!11!!01!0!0!0!1!!", 41, 2) << endl; // 1450 
    cout << bruteForceMinErrorCost("01!!01!!11!!01!0!0!0!1!!", 41, 2) << endl; // 2^12 options, ans = 1450
    cout << "Test 9: " << getMinErrorCost("01!!01!!11!!01!0!0!0!1!!", 4, 29) << endl; // firstApproach(1732)
    cout << getMinErrorCostCorrect("01!!01!!11!!01!0!0!0!1!!", 4, 29) << endl; // 1560
    cout << bruteForceMinErrorCost("01!!01!!11!!01!0!0!0!1!!", 4, 29) << endl; // 2^12 options, ans = 1560
}

/*

[A(0), B(1)] ! [C(0), D(1)] 
if 0 -> By + Dx
if 1 -> Ax + Cy 

[A(0), B(1)] ! [C(0), D(1)] ! [E(0), F(1)]
if 0, 0 -> By + Dx + Fx + By + Dy + Fx = (2B + D)y + (2F + D)x  ---- 1
if 0, 1 -> By + Dx + Fx + Ax + Cx + x + Ey = (B + E)y + (D + F + A + C + 1)x ---- 2
if 1, 0 -> Ax + Cy + y + Ey + By + Dy + Fx = (A + F)x + (C + E + B + D + 1)y ---- 3
if 1, 1 -> Ax + Cy + Ey + Ax + Cx + Ey = (2A + C)x + (2E + C)y ---- 4

We want to prove that min(1,4) < min(2, 3)
Let's say eq 1 < eq 4. 
-> (2B + D)y + (2F + D)x < (2A + C)x + (2E + C)y
2By + Dy + 2Fx + Dx < 2Ax + Cx + 2Ey + Cy
(B + D - E)y + (B - E - C)y + (F - A - C - 1)x + (F + D - A + 1)x < 0
(B + D - E)y + (F - A - C - 1)x + (B - E - C)y + (F + D - A + 1)x < 0

(B + D - E)y + (F - A - C - 1)x  < (E + C - B)y + (A - F - D - 1)x  --- 5

We can also get from above:
(F + D - A)x + (F - A - C)x + (B - C - E - 1)y + (B + D - E + 1)y < 0
(F + D - A)x + (B - C - E - 1)y < (A + C - F)x + (E - B - D - 1)y --- 6


Now let's calculate 1 - 2
(2B + D)y + (2F + D)x - (B+E)y - (D + F + A + C + 1)x = 
(2B + D - B - E)y + (2F + D - D - F - A - C - 1)x = 
(B + D - E)y + (F - A - C - 1)x --- 7


Now let's calculate 1 - 3
(2B + D)y + (2F + D)x - (A + F)x - (C + E + B + D + 1)y = 
(2B + D - C - E - B - D - 1)y + (2F + D - A - F)x = 
(F + D - A)x + (B - C - E - 1)y --- 8

We need to prove that given relation 5 and 6, equation 7 and 8 are negative.
(B + D - E)y + (F - A - C - 1)x  < (E + C - B)y + (A - F - D - 1)x  --- 5

Let's say equation 7 is greater than 0 (meaning eq 1 > eq 2)
 -> (B + D - E)y + (F - A - C - 1)x > 0
     (B + D - E)y > (A + C + 1 - F)x
     (A + C - F + 1)x - (B + D - E)y < 0
     (A + C - F)x + (E - B - D)y + x < 0
     (A + C - F)x + (E - B - D - 1)y + (x + y) < 0
     if the above is true, then (A + C - F)x + (E - B - D - 1)y < 0 (as x + y is positive)
     and plugging this into eq 6, we get:
     (F + D - A)x + (B - C - E - 1)y < ( A + C - F)x + (E - B - D - 1)y < 0
     so , (F + D - A)x + (B - C - E - 1)y < 0 -> so we proved eq 8 < 0, meaning  eq 1 < eq 3.
     -> (A - F - D)x + (C + E + 1 - B)y > 0
      (A - F - D - 1)x + x + (C + E - B)y + y > 0 
      (A - F - D - 1)x + (C + E - B)y + (x + y) > 0


     Till now 2 < 1 < 3 and 2 < 1 < 4

     Unable to prove :(

****

If we put x and y = 1
eq 1 becomes: 2(B + D + F)  ---- a
eq 2 becomes: A + B + C + D + E + F + 1    ----- b
eq 3 becomes: A + B + C + D + E + F + 1    ----- b
eq 4 becomes: 2(A + C + E) ------ c

Let's say (a < c): B + D + F < A + C + E
Now we want to see if it is possible to have (b < a): A + B + C + D + E + F + 1 < 2(B + D + F)
A + B + C + D + E + F + 1 < 2B + 2D + 2F
A + C + E + 1 < B + D + F -> This can never be possible because we know A + C + E > B + D + F, so adding 1 to A + C + E should only make it larger.
So here we can prove that if (a < c), a will be less than b, and similarly, if c < a, c will be less than b. So answer will be min(a, c).

But now tricky part is how to prove this when x and y are not equal (if x and y are equal, not necessarily equal to 1, the above results would hold).

*/