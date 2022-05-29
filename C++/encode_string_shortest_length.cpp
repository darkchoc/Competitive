/*
Question: https://www.cnblogs.com/lz87/p/14372590.html
Given a non-empty string, encode the string such that its encoded length is the shortest.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.

Note:

k will be a positive integer.
If an encoding process does not make the string shorter, then do not encode it. If there are several solutions, return any of them.
 

Example 1:
Input: s = "aaa"
Output: "aaa"
Explanation: There is no way to encode it such that it is shorter than the input string, so we do not encode it.

Example 2:
Input: s = "aaaaa"
Output: "5[a]"
Explanation: "5[a]" is shorter than "aaaaa" by 1 character.

Example 3:
Input: s = "aaaaaaaaaa"
Output: "10[a]"
Explanation: "a9[a]" or "9[a]a" are also valid solutions, both of them have the same length = 5, which is the same as "10[a]".

Example 4:
Input: s = "aabcaabcd"
Output: "2[aabc]d"
Explanation: "aabc" occurs twice, so one answer can be "2[aabc]d".

Example 5:
Input: s = "abbbabbbcabbbabbbc"
Output: "2[2[abbb]c]"
Explanation: "abbbabbbc" occurs twice, but "abbbabbbc" can also be encoded to "2[abbb]c", so one answer can be "2[2[abbb]c]".
 

Constraints:

1 <= s.length <= 150
s consists of only lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

string helper(string s, map<string, string> &dp){
    if(s.length() < 3)
        return s;
    if(dp.find(s)!=dp.end())
        return dp[s];
    string ans = s;
    for(int i=0; i<s.length(); i++){
        for(int l=1; l<=(s.length()-i)/2; l++){
            if(s[i]==s[i+l] && s[i+l-1]==s[i+l+l-1]){
                //the above are just some quick checks to avoid heavy computation for cases which are outright invalid
                string pattern = s.substr(i, l);
                int startInd = i+l;
                int repeatCount = 1;
                while(startInd <= s.length()-l && pattern == s.substr(startInd, l)){
                    repeatCount++;
                    startInd += l;
                }
                string encodedStr = s.substr(0, i) + to_string(repeatCount) + "[" + helper(s.substr(i, l), dp) + "]" + helper(s.substr(i + l*repeatCount), dp);
                if(encodedStr.length() < ans.length())
                    ans = encodedStr;
            }
        }
    }
    dp[s] = ans;
    return ans;
}

string encode(string s){
    if(s.length() < 4)
        return s;
    int n = s.length();
    map<string, string> dp;
    return helper(s, dp);
}

void constructLpsArray(string s, vector<int> &lps){
    int len = 0;
    lps.push_back(len);
    int i=1;
    while(i < s.length()){
        if(s[i]==s[len]){
            len++;
            lps.push_back(len);
            i++;
        } else {
            if(len==0){
                lps.push_back(len);
                i++;
            } else {
                len = lps[len-1];
            }
        }
    }
}

int indexOf(string text, string pattern, int n){
    //give nth occurence
    vector<int> lps;
    constructLpsArray(pattern, lps);
    int t=0, p=0;
    int occurenceNumber = 0;
    while(t < text.length()){
        if(text[t]==pattern[p]){
            t++;
            p++;
            if(p==pattern.length()){
                occurenceNumber++;
                if(occurenceNumber == n){
                    return t-pattern.length();
                }
                p = lps[p-1];
            }
        } else {
            if(p==0)
                t++;
            else
                p = lps[p-1];
        }
    }
    return -1;
}

string encodeIterative(string s){
    int n = s.length();
    vector<vector<string> > dp(n, vector<string> (n, ""));
    for(int l=1; l<=n; l++){
        for(int start=0; start+l<=n; start++){
            string current = s.substr(start, l);
            dp[start][start+l-1] = current;
            //now to check if there is any repeating sequence in current, what we can do is create another string current+current. And then search for the second time current is present in this. Eg: if current = abcabc. Then current+current = abcabcabcabc. Second time abcabc repeating is at index 4 and not 6. So if second time repetition starts before current.length(), we have a repeating sequence.
            int secondTimeRepeatIndex = indexOf(current+current, current, 2); //won't ever be -1 as we know current is ofcourse there at current.length() index.
            string encoded = current;
            if(secondTimeRepeatIndex < current.length()){
                //means repeat
                string repeatedSequence = dp[start][start+secondTimeRepeatIndex-1];
                int repetitions = current.length()/repeatedSequence.length();
                encoded = to_string(repetitions) + "[" + repeatedSequence + "]";
            }
            if(encoded.length() < current.length()){
                dp[start][start+l-1] = encoded;
                continue;//important optimization. If we can encode the whole string, no need to split string in two and encode separate parts.
            }

            for(int k=start; k<start+l-1; k++){
                encoded = dp[start][k] + dp[k+1][start+l-1];
                if(encoded.length() < dp[start][start+l-1].length())
                    dp[start][start+l-1]=encoded;
            }
        }
    }
    return dp[0][n-1];
}

int main(){
    cout << encode("aaa") << endl; //aaa
    cout << encode("aaaaa") << endl; //5[a]
    cout << encode("aaaaaaaaaa") << endl; //10[a], 9[a]a, a9[a]
    cout << encode("aabcaabcd") << endl; //2[aabc]d
    cout << encode("abbbabbbc") << endl; //2[abbb]c
    cout << encode("abbbabbbcabbbabbbc") << endl; //2[2[abbb]c]
    cout << encode("defaaabbbaaabbbgh") << endl; //def2[aaabbb]gh

    cout << encodeIterative("aaa") << endl; //aaa
    cout << encodeIterative("aaaaa") << endl; //5[a]
    cout << encodeIterative("aaaaaaaaaa") << endl; //10[a], 9[a]a, a9[a]
    cout << encodeIterative("aabcaabcd") << endl; //2[aabc]d
    cout << encodeIterative("abbbabbbc") << endl; //2[abbb]c
    cout << encodeIterative("abbbabbbcabbbabbbc") << endl; //2[2[abbb]c]
    cout << encodeIterative("defaaabbbaaabbbgh") << endl; //def2[aaabbb]gh
}