#include<bits/stdc++.h>
using namespace std;

int minKeyPresses(string s){
    vector<int> freq(26, 0);
    for(int i=0; i<s.length(); i++)
        freq[s[i]-'a']++;
    sort(freq.begin(), freq.end(), greater<int>());
    int ans = 0;
    int keyPressReqd = 1;
    for(int i=0; i<26; i++){
        if(i==9 || i==18) keyPressReqd++;
        ans += freq[i] * keyPressReqd; 
    }
    return ans;
}

int main(){
    cout << minKeyPresses("abcabc") << endl; // 6
    cout << minKeyPresses("aaabbbdddccciiidddioossslleeellaaassddbbeewwqql") << endl;
}