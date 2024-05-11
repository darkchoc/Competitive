/*
https://leetcode.com/discuss/interview-question/1901363/Quora-or-On-site-New-Grad-2022-or-Sequence-of-Strings

https://leetcode.ca/all/1256.html



Given sequence of strings:
n - f(n)
0 - ""
1 - "0"
2 - "1"
3 - "00"
4 - "01"
5 - "10"
6 - "11"
7 - "000"
8 - "001"
9 - "010"
10 - "011"
11 - "100"
12 - "101"
13 - "110"
14 - "111"
15 - "0000"
Write a function that takes n and returns f(n).
*/

#include <bits/stdc++.h>
using namespace std;

string solve(int n){
    string s = "";
    while(n){
        if(n%2 == 0) s += "1";
        else s += "0";
        n = (n-1)/2;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main(){
    for(int i=0; i<17; i++)
        cout << i << " - " << solve(i) << endl; 
}