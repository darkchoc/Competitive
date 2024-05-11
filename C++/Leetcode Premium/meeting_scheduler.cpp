/*
https://leetcode.ca/all/1229.html

Slight confusion regarding whether "end" of slot is part of the slot or not. Also, in the returned answer, if day duration is 5, should we return 10,14 or 10,15 ? 

*/

#include <bits/stdc++.h>
using namespace std;

void solve(vector<vector<int> > slot1, vector<vector<int> > slot2, int duration){
    sort(slot1.begin(), slot1.end());
    sort(slot2.begin(), slot2.end());

    int i = 0, j = 0;
    while(i < slot1.size() && j < slot2.size()){
        // check if current slots DONT overlap
        if(slot1[i][1] < slot2[j][0] || slot1[i][0] > slot2[j][1]){
            // increment index for slot that is ending earlier
            if(slot1[i][1] < slot2[j][1]) i++;
            else j++;
            continue;
        }
        // slots overlap
        int overlapDuration = min(slot1[i][1], slot2[j][1]) - max(slot1[i][0], slot2[j][0]) + 1; // +1 since start and end are inclusive
        if(overlapDuration >= duration)  {
            // This is Answer that  should be RETURNED
            int start = max(slot1[i][0], slot2[j][0]); 
            cout << start << " " << start + duration - 1 << endl; 
            return;
        } else {
            // overlap duration is less, so again increment index for slot ending earlier
            if(slot1[i][1] < slot2[j][1]) i++;
            else j++;
        }
    }
} 

int main(){
    solve({{10,50},{60,120},{140,210}}, {{0,15},{60,70}}, 8);
    solve({{10,50},{60,120},{140,210}}, {{0,15},{60,70}}, 12);
}