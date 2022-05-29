/*
https://just4once.gitbooks.io/leetcode-notes/content/leetcode/hash-table/358-rearrange-string-k-distance-apart.html

Given a non-empty string s and an integer k, rearrange the string such that the same characters are at least distance k from each other.

All input strings are given in lowercase letters. If it is not possible to rearrange the string, return an empty string "".

Example:

s = "aabbcc", k = 3

Result: "abcabc"

The same letters are at least distance 3 from each other.
s = "aaabc", k = 3 

Answer: ""

It is not possible to rearrange the string.
s = "aaadbbcc", k = 2

Answer: "abacabcd"

Another possible answer is: "abcabcda"

The same letters are at least distance 2 from each other.
*/
#include <bits/stdc++.h>
using namespace std;

string solve(string s, int k){
    vector<int> freq(26, 0);
    for(int i=0; i<s.length(); i++)
        freq[s[i]-'a']++;
    vector<pair<int, int> > letterFreq;
    for(int i=0; i<26; i++){
        if(freq[i]>0)
            letterFreq.push_back(make_pair(freq[i], i));
    }
    sort(letterFreq.begin(), letterFreq.end());
    reverse(letterFreq.begin(), letterFreq.end());
    int maxFreq = letterFreq[0].first;
    int maxSpacesToBeFilled = (maxFreq-1)*(k-1);
    if(s.length() - maxFreq < maxSpacesToBeFilled)
        return "";
    vector<string> answerParts;
    string empty = "";
    for(int i=0; i<maxFreq; i++){
        empty = "";
        answerParts.push_back(empty.append(1, letterFreq[0].second + 'a'));
    }
    int letterFreqInd = 1;
    int answerPartsInd = 0;
    while(letterFreqInd < letterFreq.size()){
        if(letterFreq[letterFreqInd].first == 0)
            letterFreqInd++;
        else {
            answerParts[answerPartsInd] += char(letterFreq[letterFreqInd].second + 'a');
            letterFreq[letterFreqInd].first--;
            answerPartsInd = (answerPartsInd + 1)%answerParts.size();
        }
    }
    string ans = "";
    for(int i=0; i<answerParts.size(); i++)
        ans += answerParts[i];
    return ans;
}

int main(){
    cout << solve("aabbcc", 3) << endl; //cbacba
    cout << solve("aaabc", 3) << endl; // ""
    cout << solve("aaadbbcc", 2) << endl; //acbacdab
}