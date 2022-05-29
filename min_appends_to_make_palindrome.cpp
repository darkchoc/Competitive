/*
Use of KMP Algo. Given string, find minimum number of characters that need to be appended to it to convert it into a palindrome. Observe, you can only append at the end of the string.

To do this, I applied a part of KMP algo. If we reverse the string and treat it as the pattern while text is the original string, then when we reach the end of the string, the number of characters of the pattern that have matched till that point give the length of palindrome that is present at the end of the string. The characters not present are the ones that need to be added!

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

string solve(string s){
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

int main(){
    string s; //"aacecaaa"
    cin >> s;
    cout << solve(s) << endl;
}