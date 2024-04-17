/*
https://leetcode.com/discuss/interview-question/416376/Quora-Phone-Screen%3A-Given-a-pair-of-integers-min-operations-to-reach-target

Given a pair (A, B), you can perform operations to make it (A+B, B) or (A, A+B). (A,B) is initialized to (1,1).
Given N > 0, find minimum number of operations needed to perform on (A,B) until A=N or B=N

Approach:
// So it's basically we have (1,1) and want to convert one of the nubmers to N
Worst case is to do N-1 operations by doing (A+B, B) everytime so that A eventually becomes N
We can also do some sort of BFS
In first go we can have (2,1). Then in two steps we can have either (3,1) or (3,2). Instead of having (2,3) as a pair, we can always sort them and keep larger number first to limit the number of possible states as (A,B) is same as (B,A) for practical purposes.

In third step we can reach (4,1), (4,3), (5,2), or (5,3)
In fourth step -> (5,1), (5,4), (7,3), (7,4), (7,2), (7,5), (8,3), (8,5)


This will give TLE. The question on leetcode is: https://leetcode.com/problems/reaching-points/description/

Check submissions.

Bascially, we need to realise 2 things:
1. We cannot interchange (x,y) as I was thinking earlier that I'll change all pairs to have x > y. This I think is fine if we are starting from 1,1 but not otherwise. If we start from say (4,2) and our target is (2,4), it is not possible to reach it. 

2. Now that x,y can't be swapped, one state can be reached in only one way. Since we are always adding, either x would increase, or y would increase. We cannot reach a certain (p,q) in 2 ways.

Given second observation, we should start from (tx,ty) and try to reach till (sx, sy)
Now, instead of doing tx = tx-ty, we can do tx = tx%ty. To understand this, check this: https://leetcode.com/problems/reaching-points/solutions/114856/java-c-python-modulo-from-the-end/comments/1452444

and this: https://leetcode.com/problems/reaching-points/solutions/816596/explanation-for-math-dummies-like-me/

*/

#include <bits/stdc++.h>
using namespace std;

bool solve(int sx, int sy, int tx, int ty){
    while(tx > sx && ty > sy){
        if(tx > ty) tx = tx%ty;
        else ty = ty%tx;
    }
    return (tx == sx && ty > sy && (ty - sy)%tx == 0) || (ty == sy && tx > sx && (tx - sx)%ty == 0);
}

int main(){
    cout << solve(4, 2, 2, 4) << endl;
    cout << solve(1, 1, 3, 5) << endl;
    cout << solve(1, 1, 2, 2) << endl;
    cout << solve(1, 1, 1, 1) << endl;
}