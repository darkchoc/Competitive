/*
I have come up with an O(nlogn) approach.
The Brute force could be that for every arr[i], we assume arr[i] to be the last shelf and hence take the all books from here. Then we take min(arr[i]-1, arr[i-1]) book from arr[i-1] and then even lesser from i-2 and so on till we either reach start of shelf or we can take only 0 books now. 

Now, if arr[i-1] < arr[i], the max books we can take if arr[i] is the last shelf would simply be maxBooks[i] = maxBooks[i-1] + arr[i].
But now consider case where arr[i-1] >= arr[i]. In this case, we have to take arr[i]-1 books from arr[i-1]. This would further affect how many books we can take from arr[i-2].
Consider the following cases:
    2 5 4 3 8 10 7
    When we're at 10, we calculate maxBooks[at 10] = maxBooks[at 8] + 10 = 24. Also, note that last book was taken from 2nd shelf with 5 books.
    Now coming to 7, we see 10 > 7. We can take 7 books from 7, 6 from 10, 5 from 8. But we can still take all 3 from 3. So in this case, we need to find the largest index k between earliest shelf from where book was taken for arr[i-1] and index i-1) such that arr[k] < (arr[i]-(i-k)). To understand, consider that when we are at 7:
        we want 6 (7-(6-5)) books from 10 (previous shelf): 10 >= (7 - (6-5))
        we want 5 (7-(6-4)) books from 8 which is also possible
        we want 4 (7-(6-3)) books from 3 which is not possible. So we stop. This means, we can take 7+6+5 books and after that, we need to take maxBooks[at 3], so final ans = 7 + 6 + 5 + 6(max at 3) = 24.

    Well well, I was wrong. Binary search won't work. Because it isn't necessariy monotonic funciton. Say at shelf with 3 boxes we cannot take 4 books, but on left of it, at shelf with 4 books, we can take 3 books. And similarly on right, at shelf with 8 books, we can take 5 books. So we get TFT type of sequence (T=True, F=False). But for binary search it should be like TTTTFFF or FFFFTTT .. hope you got it. 

    So we need to think of something else. I tried reading the following links:
    https://walkccc.me/LeetCode/problems/2355/ (check this as this approach relates more to my previous approach)
    https://algo.monster/liteproblems/2355
    But still couldn't exactly understand so trying to write my understanding here:
    I get that monotonic stack works but can't explain how to arrive at that solution. In the monotonic stack, we want to store indices such that after processing the stack for current i, the top element of stack holds index j such that books[j] < books[i] - (i - j). Had books[j] >= books[i]-(i-j), we would have taken j out of stack. We push i into stack now. So current stack: [j, i] .. So current stack tells us that for index k > i, either the condition books[x] >= books[k] - (k-x) where x < k, would fail at index i, or straight away at index j or it won't fail at all.

    For k = i+1,
    Case1: books[k] > books[i] + 1
    In this case, condition would fail at i itself. So we take books[k] and dp[i]. Example:
    2, 3, 6
    k = index 2. We see books[k]=books[2]=6 > 4(books[1]+1), so we must take dp[1] and can't go further in left.

    Case 2: books[i] >= books[k]-1 (the number of books we need at i is books[k]-1).
    In this case, the condition would not fail at i. It may fail at j. Also important thing to note is that now for all indices q > k, condition would not fail at i, rather if it has to fail, it would fail at k itself. And if it doesn't fail at k, then it wouldn't fail at i as well. So if we add k to stack, either condition would fail at k, or k would be popped and j would be the next candidate to check. 


*/

#include <bits/stdc++.h>
using namespace std;

int maxBooks(vector<int> books){
    int n = books.size();
    if(n==0) return 0;
    vector<int> dp (n);
    stack<int> st;
    int ans = 0;
    for(int i=0; i<n; i++){
        while(!st.empty() && books[st.top()] >= books[i] - (i - st.top()))
            st.pop();
        if(st.empty()){
            // we can take books[i] + books[i]-1 + books[i]-2 + ... and so one.. 
            // either we reach till index 0, or we have to stop because we reached a shelf from where we have to take 0 books.
            int minBooksTaken = max(1, books[i] - (i)); // we have taken books starting from index 0 to i. From index 0, we would have picked books[i] - (i - 0).
            dp[i] = ((books[i]*(books[i]+1))/2) - (((minBooksTaken-1)*(minBooksTaken-1+1))/2);
        } else {
            // st.top is where we see that books[st.top()] < books[i] - (i - st.top()). So we take books[i], books[i]-1 ... so on till index st.top+1, and from st.top, we just take dp[st.top()].
            int lastSatisfiedIndex = st.top()+1;
            int booksTakenFromAboveIndex = books[i] - (i - lastSatisfiedIndex);
            dp[i] = ((books[i]*(books[i]+1))/2) - (((booksTakenFromAboveIndex-1)*(booksTakenFromAboveIndex-1+1))/2);
            dp[i] += dp[st.top()];
        }
        st.push(i);
        ans = max(ans, dp[i]);
    }
    return ans;
}

int main(){
    cout << maxBooks({4,5,4,3,6,2}) << endl; // 12
    cout << maxBooks({8,5,2,7,9}) << endl; // 19
    cout << maxBooks({7,0,3,4,5}) << endl; // 12
    cout << maxBooks({8,2,3,7,3,4,0,1,4,3}) << endl; // 13
}