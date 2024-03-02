// just trying to make amazong_song_selection.cpp more efficient in terms of space complexity.

#include <bits/stdc++.h>

using namespace std;

string convertToLower(string original){
    string lower = "";
    for(int i=0; i<original.length(); i++)
        lower += tolower(original[i]);
    return lower;
}

int getMaxSongs(vector<int> songs, vector<int> albumSize, vector<string> genre, int maxCapacity) {
    // if you notice closely, dp[i][] is affected only by dp[i-1][]. So wondering if we can make it efficient in some way.

    // I can imagine that while filling the dp array in previous question, for filling dp[i][j], we may have to look at dp[i-1][j-something]. So now, if we are dealing with 1D array, instead of iterating on j from 0 to maxCapacity, we should iterate from maxCapacity to 0 so that don't use updated value of dp[j-something] when running the ith iteration.

    unordered_map<string, vector<pair<int, int> > > mp;
    for(int i=0; i<songs.size(); i++){
        string smallGenre = convertToLower(genre[i]);
        mp[smallGenre].push_back(make_pair(songs[i], albumSize[i]));
    }

    vector<int> dp (maxCapacity+1, 0);
    // dp[j] gives max songs we can have with j capacity. Number of genres considered depends on number of iterations we have already run.
    for(unordered_map<string, vector<pair<int, int> > >::iterator it = mp.begin(); it!=mp.end(); it++){
        for(int j=maxCapacity; j>=0; j--){
            for(int k=0; k<it->second.size(); k++){
                if(j < it->second[k].second) continue;
                dp[j] = max(dp[j], it->second[k].first + dp[j-it->second[k].second]);
            }
        }
    } 
    return dp[maxCapacity];
}

int main() {
    cout << getMaxSongs({8,4,5,6,7,9}, {100,150,55,75,71,15}, {"pop", "jazz", "country", "Latin", "Electro", "jazz"}, 300) << endl;   // 30
   cout << getMaxSongs({6,14,7,10,15,4,21,13,21,33,5,0,4}, {50,40,100,70,65,70,110,200,150,200,90,30,120}, {"pop", "alternate", "Rock", "Jazz", "jazz", "jazZ", "rock", "Alternate", "Electro", "EDM", "edm", "hiphop", "pop"}, 600) << endl; //
}