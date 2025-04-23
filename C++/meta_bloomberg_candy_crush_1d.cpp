/*
https://leetcode.com/discuss/post/380650/bloomberg-phone-candy-crush-1d-by-suprit-r11f/

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

"aaaabbbc" => c
"aabbbacd" => cd
"aabbccddeeedcba" => ""
"aabbbaacd" => cd
"dddabbbbaccccaax" => x
*/

/*
Checked a comment in the above thread.

Maintain a stack with (char, count) elements.
We can use a stack. If current element is same as previous element, increment count in st.top(). 
If current element is different than last element, then check if st.top() should be popped, if it has count > 3. If you pop it, then
you need to see what to do with the new st.top(). If the current character matches the st.top(), add to count, else create a new element on top.

Finally, once you exit loop, check if st.top() has count > 3 and if so, pop it.

Return final answer by appending values from stack.
*/

#include <iostream>
using namespace std;

string candyCrush(string s) {
    if(s.length() < 3) return s;
    stack<pair<char, int> > st;
    st.push(make_pair(s[0], 1));
    int i=1;
    while(i < s.length()) {
        if(s[i]!=s[i-1]) {
            if(st.top().second >= 3) 
                st.pop();
            // now again check what about the new st.top()?  
            if(!st.empty() && st.top().first == s[i]) {
                st.top().second++;
            } else {
                st.push(make_pair(s[i], 1));
            }
        } else {
            st.top().second++;;
        }
        i++;
    }   
    // now check finally if last st.top() needs to be removed
    if(!st.empty() && st.top().second>=3)
        st.pop();
    string ans = "";
    while(!st.empty()){
        pair<char, int> p = st.top();
        st.pop();
        for(int i=0; i<p.second; i++)
            ans.push_back(p.first);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    cout << candyCrush("aaabbbc") << endl; // c
    cout << candyCrush("aabbbacd") << endl; // cd
    cout << candyCrush("aabbccddeeedcba") << endl; // ""
    cout << candyCrush("aaabbbacd") << endl; // acd
    cout << candyCrush("dddabbbbaccccaax") << endl; // x
}