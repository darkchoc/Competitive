/*
Question: https://leetcode.com/discuss/interview-question/380650/Bloomberg-or-Phone-or-Candy-Crush-1D
Write a function to crush candy in one dimensional board. In candy crushing games, groups of like items are removed from the board. In this problem, any sequence of 3 or more like items should be removed and any items adjacent to that sequence should now be considered adjacent to each other. This process should be repeated as many time as possible. You should greedily remove characters from left to right.

Example 1:
Input: "aaabbbc"
Output: "c"
Explanation:
1. Remove 3 'a': "aaabbbbc" => "bbbbc"
2. Remove 4 'b': "bbbbc" => "c"

Example 2:
Input: "aabbbacd"
Output: "cd"
Explanation:
1. Remove 3 'b': "aabbbacd" => "aaacd"
2. Remove 3 'a': "aaacd" => "cd"

Example 3:
Input: "aabbccddeeedcba"
Output: ""
Explanation:
1. Remove 3 'e': "aabbccddeeedcba" => "aabbccdddcba"
2. Remove 3 'd': "aabbccdddcba" => "aabbcccba"
3. Remove 3 'c': "aabbcccba" => "aabbba"
4. Remove 3 'b': "aabbba" => "aaa"
5. Remove 3 'a': "aaa" => ""

Example 4:
Input: "aaabbbacd"
Output: "acd"
Explanation:
1. Remove 3 'a': "aaabbbacd" => "bbbacd"
2. Remove 3 'b': "bbbacd" => "acd"

Follow-up:
What if you need to find the shortest string after removal?

Example:

Input: "aaabbbacd"
Output: "cd"
Explanation:
1. Remove 3 'b': "aaabbbacd" => "aaaacd"
2. Remove 4 'a': "aaaacd" => "cd"
*/

#include <bits/stdc++.h>
using namespace std;

string greedy(string s){
    int n = s.length();
    stack<pair<char, int> > st;//holds char and it's freq for a repeated block
    for(int i=0; i<n; i++){
        if(st.empty()){
            st.push(make_pair(s[i], 1));
        } else {
            if(st.top().first != s[i]){
                //first remove last valid sequence
                if(st.top().second >= 3)
                    st.pop();
            }
            if(!st.empty() && st.top().first==s[i]){
                //then check if after removing the valid sequence, do we get same character as s[i]
                pair<char, int> p = st.top();
                st.pop();
                p.second++;
                st.push(p);
            } else {
                //if not, just push this character to stack
                st.push(make_pair(s[i], 1));
            }
        }
    }
    //now it is possible that last sequence is valid
    if(!st.empty() && st.top().second >= 3)
        st.pop();
    //now construct answer
    string ans = "";
    while(!st.empty()){
        pair<char, int> p = st.top();
        st.pop();
        for(int i=0; i<p.second; i++)
            ans += p.first;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

string recurse(string s, map<string, string> &dp){
    if(dp.find(s)!=dp.end())
        return dp[s];
    string currentBest = s;
    //try removing every group
    int i=0;
    while(i < s.length()){
        char c = s[i];
        int j = i;
        while(j<s.length() && s[j]==c)
            j++;
        j--;
        //now s[i] to s[j] is same
        int lengthOfRepeatedChar = j-i+1;
        if(lengthOfRepeatedChar >= 3){
            //we can check what removing this leads to
            string left = s.substr(0, i);
            string right = s.substr(j+1);
            string remaining = left + right;
            string crushed = recurse(remaining, dp);
            if(crushed.length() < currentBest.length())
                currentBest = crushed;
        }
        i=j+1;
    }
    dp[s]=currentBest;
    return currentBest;
}

string optimal(string s){
    /*
    Basically given a string s, we should store what is the best crushed string we can get. We don't want to recalculate it.
    Eg: Consider aaabbbaccdddeee -> Here, if we remove e first or d first, in both cases we'll be left with string aaabbbacc. So we should be calculating crushed string for aaabbbacc only once.
    */
   map<string, string> dp; //dp[original]=crushedString
   return recurse(s, dp);
}

int main(){
    cout << greedy("aaabbbc") << endl;    
    cout << greedy("aabbbacd") << endl;    
    cout << greedy("aabbccddeeedcba") << endl;    
    cout << greedy("aaabbbacd") << endl;  

    cout << optimal("aaabbbacd") << endl;
    cout << optimal("baaabbbabbccccd") << endl;  
}