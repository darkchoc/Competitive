/*
Find minimum number of characters that have to be added to the front to make the string a palindrome.

Here, I have used KMP's logic. But what I have done is this. Imagine this in your head to get a better picture. We have a string, and we want to see that what is the longest palindrome at the start of the string. The characters that don't fall in this are the ones that need to be inserted. 

To get longest palindrome, imagine overlapping the string with the reverse of it, such that the overlapping part starts from beginning.
Example: if my string is 
    aabaacde, the reverser would be edcaabaa
    now when I overlap this and orignal, I want it to be like this:
       aabaacde
    edcaabaa

    So basically we are seeing that if I treat reverse of string (srev) as text and original string (s) as pattern, then when I reach end of srev, what is the index in s. Because that many characters match. 

In the case of appending characters to string (see min_appends_to_make_palindrome.cpp), we do opposite because there we want max palindrome at the end of string so we want the overlapping part to be at the end:
    eg: aabaab
    reverse: baabaa
    we want: 
        aabaab
          baabab
    So we are seeing that if we reach end of s (text), then what is the index in pattern (srev). And that is the length of palindrome, remaining letters need to be added to end.


Another option is to use a modified string and calcualte LPS on that. Basically, append the reverse of the string after adding a non-alphanumeric character. And then create LPS array on top of that. Detailed explanation in min_appends_to_make_palindromic.cpp

*/

#include <bits/stdc++.h>
using namespace std;

void computeLpsArray(string &s, vector<int> &lps){
    if(s.length()==0)
        return;
    int len = 0; //length of proper prefix that is matching
    int i = 1;
    lps.push_back(0);
    while(i < s.length()){
        if(s[i]==s[len]){
            len++;
            lps.push_back(len);
            i++;
        } else {
            if(len == 0) {
                lps.push_back(0);
                i++;
            } else
                len = lps[len-1];
        }
    }
}

string solveUsingKMP(string &s){
    string srev = s;
    reverse(srev.begin(), srev.end());

    vector<int> lps;
    computeLpsArray(s, lps);

    //now my pattern is s, and text is srev. 
    int t = 0, p = 0;
    while(t < srev.length()){
        if(srev[t] == s[p]){
            t++;
            p++;
        } else {
            if(p == 0)
                t++;
            else 
                p = lps[p-1];
        }
    }
    cout << "#Characters to insert in front: " << s.length() - p << endl;
    string strToInsertInFront = s.substr(p);
    reverse(strToInsertInFront.begin(), strToInsertInFront.end());
    return strToInsertInFront;
}

int solveUsingModifiedLPS(string s) {
    string revS = s;
    reverse(revS.begin(), revS.end());
    string combined = s + "!" + revS;
    vector<int> lps;
    computeLpsArray(combined, lps);
    int longestPalindromicPrefix = lps[combined.length()-1];
    return (s.length()-longestPalindromicPrefix);
}

int main(){
    string s;
    cin >> s;
    cout << solveUsingKMP(s) << endl;
    cout << solveUsingModifiedLPS(s) << endl;
}