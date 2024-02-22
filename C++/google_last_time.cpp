#include <bits/stdc++.h>
using namespace std;

void printMatrixDiagonally(){
    vector<vector<int> > mat {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    int r = mat.size(); 
    int c = mat[0].size();
    for(int start_j=0; start_j<c; start_j++){
        for(int i=0, j=start_j; i<r && j<c; i++, j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    for(int start_i=r-1; start_i>0; start_i--){
        for(int i=start_i, j=0; i<r && j<c; i++, j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

double helper(int r, int b, vector<vector<double> > &dp){
    if(r==0)
        return 0.0;
    else if(b==0)
        return r;
    if(dp[r][b]!=-1)
        return dp[r][b];
    //Let helper give expected value of current state. Then if I draw a red card right now, my earned value would be 1 + expectedValue(r-1, b). If I draw black card, my earned value would be -1 + expectedValue(r, b-1). 
    //But now, probability of reaching state 1 is r/(r+b), and that of state 2 is b/(r+b)
    //Also, if for a particular state, I'm getting negative value, it makes sense to stop game.
    double redCardDrawNextState = 1.0 + helper(r-1, b, dp);
    double blackCardDrawNextState = -1.0 + helper(r, b-1, dp);
    double currentStateExpectedEarning = ((double)r/(r+b))*(redCardDrawNextState) + ((double)b/(r+b))*(blackCardDrawNextState);
    //check if currentStateEarning is negative, if so, stop game and return 0 rather.
    currentStateExpectedEarning = max(0.0, currentStateExpectedEarning);
    dp[r][b] = currentStateExpectedEarning;
    return currentStateExpectedEarning;
}

void expectedValueOnDrawingRedBlackCards(){
    int r = 1;
    int b = 3;
    vector<vector<double> > dp_recursive(r+1, vector<double> (b+1, -1));
    double recursiveAnswer = helper(r, b, dp_recursive);

    //iterative code
    vector<vector<double> > dp (r+1, vector<double> (b+1, 0));
    for(int i=0; i<=r; i++){
        for(int j=0; j<=b; j++){
            if(i==0)
                dp[i][j]=0;
            else if(j==0)
                dp[i][j] = i;
            else{
                dp[i][j] = ((double)i/(i+j))*(1.0 + dp[i-1][j]) + ((double)j/(i+j))*(-1.0 + dp[i][j-1]);
                dp[i][j] = max(0.0, dp[i][j]);
            }
        }
    }

    double iterativeAnswer = dp[r][b];  
    cout << "expected val: " << recursiveAnswer << " "  << iterativeAnswer << endl; 
}

int query(vector<int> &reqdArr, int l, int r){
    int min_ = l;
    for(int i=l+1; i<=r; i++){
        if(reqdArr[i] < reqdArr[min_])
            min_ = i;
    }
    return min_;
}

void helper2(vector<int> &reqdArr, int callsTillNow, int start, int end, int &finalAns){
    if(start > end)
        return;
    if(start==end){
        finalAns += reqdArr[start] - callsTillNow;
        return;
    }
    int x = query(reqdArr, start, end);
    finalAns += reqdArr[x] - callsTillNow;
    helper2(reqdArr, reqdArr[x], start, x-1, finalAns);
    helper2(reqdArr, reqdArr[x], x+1, end, finalAns);
}

void convertArrayOfZerosToRequiredArray(){
    vector<int> reqdArr = {3,2,5,0,4,3,6,4,8,2,4};
    //we are given a function f(l,r) that increments the initial all 0 array by 1 for all indices l...r
    //assume function query(l,r) gives index of minimum element between l...r
    int finalAns = 0;
    helper2(reqdArr, 0, 0, reqdArr.size()-1, finalAns);
    cout << finalAns << endl;
}

int main(){
    printMatrixDiagonally();
    expectedValueOnDrawingRedBlackCards();
    convertArrayOfZerosToRequiredArray();
}