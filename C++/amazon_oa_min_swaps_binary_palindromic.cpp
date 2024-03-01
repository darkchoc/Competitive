/*

Was asked this Amazon OA in 2022.

Min swaps required to make binary string palindromic.
eg: 
1010000 -> 1 swap (take second 1 to end)
1010 -> 1 swap (take second 1 to end)
000110100 -> 1 swap (shift last 1 the left by one place)\
010110100 -> 001110100 -> 001101100 => 2 swaps required.
01011010010101 -> -1 as we can't make it palindromic.
*/

#include <bits/stdc++.h>
using namespace std;

int minSwaps(string binStr) {
    int ones = 0, zeros = 0;
    for(int i=0; i<binStr.length(); i++){
        if(binStr[i]=='0') zeros++;
        else ones++;
    }
    if(zeros%2==1 && ones%2==1) return -1;
    int diff = 0;
    for(int l=0, r=binStr.length()-1; l < r; l++, r--){
        if(binStr[l]!=binStr[r]) diff++;
    }
    return (diff+1)/2;
}

int main(){
    /*
    Approach: 
    First, we cannot make a string palindromic if there odd number of 1s and 0s.

    I can see, that if keep pointer at each end and start moving towards center, we can count how many times the elements differ. Then number of swaps required are (diff+1)/2. Not sure how to prove it though. Maybe we can think on the lines that we have only two types of characters.
    Let's say characters differ twice, then it must be like: 
    xxx..0..yyy..0..zzz..1..yyy..1..xxx
    or xxx..0..yyy..1..zzz..0..yyy..1..xxx
    or xxx..1..yyy..1..zzz..0..yyy..0..xxx
    or xxx..1..yyy..0..zzz..1..yyy..0..xxx

    All these cases can be resolved in 1 swap and converted to xxx..1..yyy..0..zzz..0..yyy..1..xxx

    Similarly, if there are 3 diffs:

    W..0..X..0..Y..0..Z..1..Y..1..X..1..W
    W..1..X..0..Y..0..Z..0..Y..1..X..1..W
    W..1..X..0..Y..1..Z..0..Y..1..X..0..W and so on...

    010110100
    W..1..X..0..Y..1..Z..0..Y..1..X..0..W
    In one swap we get: W..1..X..0..Y..1..Z..0..Y..0..X..1..W
    Now consider 1..Z..0 
    Z is palindromic we know. Also, we know that Z cannot have even number of 0s and 1s as in that case 1..Z..0 will have odd number of 0s and 1s and we cannot make it palindromic. 
    So possibilities for Z are of the form: 0, 1, 010, 101, 1100011. (You can see Z cannot even have odd number of 1s and 0s as we cannot ever have a palindrome with odd 1s and 0s anyway, so Z must be of odd length.)
    In each of these cases, we make make 1..Z..0 palindromic in 1 swap. If middle element of Z is 0, swap it with the 1 outside of Z (if -> 1..Z..0, I'm talking about the 1 before ".."). If middle element of Z is 1, swap it with 0 present outside Z (in 1..Z..0, talking about the last 0).
    Eg: 1..1100011..0 -> middle element is 0, swap with 1 to get -> 011010110

    So basically if diff is even, we can do diff/2 swaps.
    If diff is odd, we can do diff/2 swaps first and then last 1 remaining swap.
    */
    cout << minSwaps("1010000") << endl; // 1 (differs 2 times)
    cout << minSwaps("1010") << endl; // 1 (differs 2 times)
    cout << minSwaps("0011") << endl; // 1 (differs 2 times) -> 1001
    cout << minSwaps("000110100") << endl; // 1 (differs 2 times)
    cout << minSwaps("010110100") << endl; // 2 (differs 3 times) -> 001110100 -> 001101100
    cout << minSwaps("01011010010101") << endl; // -1 (odd number of 1s and 0s)
    cout << minSwaps("01101000") << endl; // -1 (odd number of 1s and 0s)
    cout << minSwaps("00101000001") << endl; // 2 (differs 3 times)
    cout << minSwaps("001011001000001") << endl; // 3 (differs 5 times)
    // 001011001000001 -> 001011011000000 -> 000011011100000 -> 000011010110000
    cout << minSwaps("001") << endl; // 1 (differs 1 time)
}

