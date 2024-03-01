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

int recurse(string s, int ind, int x, int y){
    if(ind == s.length())
        return getCostOfString(s, x, y);
    if(s[ind]!='!') return recurse(s, ind+1, x, y);
    return min(
        recurse(s.substr(0, ind) + "0" + s.substr(ind+1), ind+1, x, y), 
        recurse(s.substr(0, ind) + "1" + s.substr(ind+1), ind+1, x, y)
    );
}

int bruteForceMinErrorCost(string s, int x, int y){
    return recurse(s, 0, x, y);
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


int main() {
    cout << getMinErrorCost("01!!", 2, 3) << endl; // 6
    cout << bruteForceMinErrorCost("01!!", 2, 3) << endl; // 6
    cout << getMinErrorCost("!!!!", 2, 5) << endl; // 0 
    cout << getMinErrorCost("010!1!00!01!", 2, 5) << endl; // 99
    cout << bruteForceMinErrorCost("010!1!00!01!", 2, 5) << endl; // 2^4 options, ans = 99
    cout << getMinErrorCost("010!01!!1!!010!00", 3, 2) << endl; // 124
    cout << bruteForceMinErrorCost("010!01!!1!!010!00", 3, 2) << endl; // 2^6 options, ans = 124
    cout << getMinErrorCost("01!!01!!11!!01!0!0!0!1!!", 4, 2) << endl; // 300 
    cout << bruteForceMinErrorCost("01!!01!!11!!01!0!0!0!1!!", 4, 2) << endl; // 2^12 options, ans = 300
}