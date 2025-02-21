/*
Use of KMP Algo. Given string, find minimum number of characters that need to be appended to it to convert it into a palindrome. Observe, you can only append at the end of the string.

To do this, I applied a part of KMP algo. If we reverse the string and treat it as the pattern while text is the original string, then when we reach the end of the string, the number of characters of the pattern that have matched till that point give the length of palindrome that is present at the end of the string. The characters not present are the ones that need to be added!

There is also an other way to solve this, that can work if we are given that characters are say, alphanumeric only. Then, if we append original string to reverse of string to original string, but after appending a non-alpha-numeric character (For example: string=cdaba, rev=abadc, combined=abadc!cdaba. Here we added orignal string after a "!"), then we can just calculate LPS for this and the value at the end, signifying the longest prefix that is also the suffix, will tell us how much of the string is palindromic at the end. We added "!" so that it never happens that first half of string overlaps with second half (the reverse of string). Basically the prefix and suffix won't overlap.
 

Check min_appends_to_make_palindrome.cpp!!!!!
*/

#include <bits/stdc++.h>
using namespace std;

void computeLpsArray(string &s, vector<int> &lps){
    if(s.length()==0)
        return;
    lps.push_back(0);
    int len = 0;
    int i=1;
    while(i < s.length()){
        if(s[i]==s[len]){
            len++;
            i++;
            lps.push_back(len);
        } else {
            if(len==0){
                lps.push_back(0);
                i++;
            } else {
                len = lps[len-1];
            }
        }
    }
}

string solveUsingKMP(string s){
    string srev = s;
    reverse(srev.begin(), srev.end());

    vector<int> lps;
    computeLpsArray(srev, lps);

    //consider pattern = srev, text = s
    int p = 0, t = 0;
    while(t < s.length()){
        if(s[t]==srev[p]){
            t++;
            p++;
        } else {
            if(p==0){
                t++;
            } else {
                p = lps[p-1];
            }
        }
    }
    //p characters of srev matched the last part of s. Means we are having a p character palindrome at end.
    //So characters that need to be appeneded are s.length() - p.
    cout << "#Characters to append: " << s.length() - p << endl;
    string strToAppend = s.substr(0, s.length() - p); 
    reverse(strToAppend.begin(), strToAppend.end());
    return strToAppend;
}

int solveUsingModifiedLPS(string s) {
    string revS = s;
    reverse(revS.begin(), revS.end());
    string combined = revS + "!" + s;
    vector<int> lps;
    // use the same lps function as earlier
    computeLpsArray(combined, lps);
    int longestPalindromixSuffix = lps[combined.length()-1]; // means these many characters matched.
    // min appends
    int minAppends = s.length()-longestPalindromixSuffix;
    return minAppends;
}

int main(){
    string s; //"aacecaaa"
    cin >> s;
    cout << solveUsingKMP(s) << endl;
    cout << solveUsingModifiedLPS(s) << endl;
}