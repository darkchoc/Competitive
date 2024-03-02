/*
https://www.reddit.com/r/leetcode/comments/196jfmj/amazon_oa/
AWS stores grayscale images as an array of white and black pixels. The image is stored as a binary string where a white pixel is represented by 1 and a black pixel is represented by 0. The reverse of the image is represented as the reverse of this binary representation. For example, the reverse of "11010" is "01011". They want to store the reverse of each image as a backup. In order to reproduce the reverse from the original, the following operation can be performed any number of times: remove any character from the string and append it to the end of the string, i.e., choose any pixel and shift it to the end of the string. 

Given the binary representation of pixels denoted by the image, find the minimum number of operations needed to produce it's reverse.

Example:
The pixel representation of image = "0100110"
Output: 3
Explanation: 01(0)0110 -> 0(1)01100 -> (0)011001 -> 0110010 

Example 2:
Input: 00110101
Output: 3
Explanation: 00(1)10101 -> 0(0)101011 -> (0)1010110 -> 10101100

Approach: I think it is similar to min appends to make string palindromic question on interviewbit: https://www.interviewbit.com/problems/minimum-characters-required-to-make-a-string-palindromic/

*/

#include <bits/stdc++.h>
using namespace std;

int minOps(string s) {
    // we want to apply KMP. The main string would be s, the pattern would rev_s. Then we want to see that when we reach end of s, how much of rev_s is covered. 
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    
    // construct lps on rev_s.
    vector<int> lps (rev_s.length(), 0);
    int len = 0, i=1;
    while(i < rev_s.length()) {
        if(rev_s[i]==rev_s[len]){
            len++;
            lps[i] = len;
            i++;
        } else {
            if(len == 0){
                lps[i] = 0;
                i++;
            } else {
                len = lps[len-1];
            }
        }
    }

    // start matching
    i = 0;
    int j = 0;
    while(i < s.length()) {
        if(s[i]==rev_s[j]){
            i++;
            j++;
        } else {
            if(j==0) i++;
            else j = lps[j-1];
        }
    }
    // now j gives number of characters matched.
    return s.length() - j; 
}

int approach2(string s){
    int i = 0, j = s.length()-1;
    int count = 0;
    while(i < s.length()-1) {
        if(s[i] == s[j]){
            i++;
            j--;
        } else {
            i++;
            count++;
        }
    }
    return count;
}

int main() {
    cout << minOps("0100110") << endl; // 3
    cout << approach2("0100110") << endl;
    cout << minOps("00110101") << endl; // 3
    cout << approach2("00110101") << endl; 
    cout << minOps("0101011010") << endl; // 2
    cout << approach2("0101011010") << endl;
    cout << minOps("101") << endl; // 0
    cout << approach2("101") << endl;
}