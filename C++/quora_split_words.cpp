/*
https://leetcode.com/discuss/interview-question/425954/Quora-or-Onsite-or-Split-Words

Given a list L, where each inner list comprises of a list of k strings. You are also given a width, w, to split each string in the inner list into separate rows. For example:
L = [['facebook', 'google', 'uber', 'apple'], ['lyft', 'airbnb', 'paypal', 'yelp']]
w = [4,4,3,2]
k = 4

Output: face | goog | ube   | ap
        book | le   | r     | pl
             |      |       | e
        lyft | airb | pay   | ye
             | nb   | pal   | lp

The total height of output is 5 as there are 5 rows. If given a value x, where x will always be some value >= k, return a width list w where all the values in w sum to x such that the resultant list minimizes the height of the corresponding output. For instance, given x=13, possible width lists include [4,4,3,2], [5,3,2,3], [3,3,3,4], etc. These width list values sum to x=13, so the question becomes finding a width list that minimizes the total height of the output.
*/      

#include <bits/stdc++.h>
using namespace std;

void solve(vector<vector<string> > words, int k){
    int n = words.size();
    int m = words[0].size();
    vector<int> weight (m, 1);
    int sum = m;
    while(sum < k){
        int maxLen = 0, maxCol = -1;
        for(int i=0; i<m; i++){
            int currLen = 0;
            for(int j=0; j<n; j++)
                currLen += ceil((double)words[j][i].length()/weight[i]);
            if(currLen > maxLen){
                maxLen = currLen;
                maxCol = i;
            }
        }
        weight[maxCol]++;
        sum++;
    }
    for(int i=0; i<m; i++)
        cout << weight[i] << " ";
    cout << endl;
}

int main(){
    solve({{"facebook", "google", "uber", "apple"}, {"lyft", "airbnb", "paypal", "yelp"}}, 13);
}