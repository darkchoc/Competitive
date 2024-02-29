/*
Third question in https://leetcode.com/discuss/interview-question/4326333/Amazon-OA

You are given a "number of songs in an album" array, "album size" array and a "genre" array.

No. of songs : {8,4,5,6,7,9}
AlbumSize(in KBs): {100,150,55,75,71,15}
Genre: {"pop","jazz", "country" , "Latin", "Electro" , "jazz"}
Maximum Capacity: 300

Your goal is to maximize the total number of songs within the maximum capacity such that there is no repeated genre (You can select only one album from one particular genre).

So output for above: We can select (8, 100, pop) + (6, 75, Latin) + (7, 71, Electro) + (9, 15, Jazz) = 30 songs with total capacity = 261 KB.

*/

#include <bits/stdc++.h>

using namespace std;

string convertToLower(string original){
    string lower = "";
    for(int i=0; i<original.length(); i++) 
        lower += tolower(original[i]);
    return lower;
}

int getMaxSongs(vector<int> songs, vector<int> albumSize, vector<string> genre, int maxCapacity) {
    unordered_map<string, vector<pair<int, int> > > mp; // key = genre, value = list of (songs, albumSize) for albums of that particular genre.

    map<pair<int, int>, vector<pair<int, int> > > selectedAlbums; // for c (capacity) and i (index of genres considered till now), we store list of albums added to achieve that allow us to have max songs. Album is identified by pair<int, int> giving position of genre in map and position within albums of that particular genre.

    for(int i=0; i<songs.size(); i++){
        string smallGenre = convertToLower(genre[i]);
        mp[smallGenre].push_back(make_pair(songs[i], albumSize[i]));
    }
    int n = mp.size();

    // printing some stuff to make sense of data printed later regarding which album was picked.
    cout << "Unique genres: " << n << endl; 
    int x = 0;
    for(unordered_map<string, vector<pair<int, int> > >::iterator it = mp.begin(); it!=mp.end(); x++, it++){
        cout << x << " " << it->first << endl;
    }


    vector<vector<int> > dp (n, vector<int> (maxCapacity+1, 0));
    // dp[i][j] gives max number of songs that we can have with capacity j and first i (0 indexed) genres.
    int i=0;
    for(unordered_map<string, vector<pair<int, int> > >::iterator it = mp.begin(); it!=mp.end() && i<n; it++, i++){
        for(int j=0; j<=maxCapacity; j++){
            dp[i][j] = (i>0)?dp[i-1][j]:0; // initialising with case where not taking any album of ith genre.
            if(i > 0) selectedAlbums[make_pair(i, j)] = selectedAlbums[make_pair(i-1, j)];
            // Now taking one of the albums of the kth genre.

            for(int k=0; k < it->second.size(); k++){
                if(j < it->second[k].second) continue;
                
                /*
                // the below is fine if we don't want to store which album was picked up.
                dp[i][j] = max(dp[i][j], 
                        it->second[k].first + ((i>0)?dp[i-1][j-it->second[k].second]:0) // taking kth album of the specific ith genre. 
                );
                */
                int numSongsIfIncludingAlbum = it->second[k].first + ((i>0)?dp[i-1][j-it->second[k].second]:0);

                if(dp[i][j] < numSongsIfIncludingAlbum){
                    dp[i][j] = numSongsIfIncludingAlbum;
                    if(i > 0)
                        selectedAlbums[make_pair(i, j)] = selectedAlbums[make_pair(i-1, j-it->second[k].second)];
                    selectedAlbums[make_pair(i, j)].push_back(make_pair(i, k));
                }
            }
        }
    }

    // print which albums were selected
    for(int i=0; i<selectedAlbums[make_pair(n-1, maxCapacity)].size(); i++){
        cout << "(" << selectedAlbums[make_pair(n-1, maxCapacity)][i].first << " " << selectedAlbums[make_pair(n-1, maxCapacity)][i].second << "), ";
    }
    cout << endl;

    return dp[n-1][maxCapacity];
}

int main() {
    /*
    This seems like a modification of knap sack. We are given a capacity, the weight of items (which is size of album here), and the value of items (which is the number of songs here). The modification is that genre. We can only select one album from a particular genre.

    To tackle this, we can create an array where each index gives us a list of albums of a particular genre. Then as we move ahead in this array, we can also iterate on each of the albums of a particular genre and try including each one by one (I mean, including only one of them at a time).
    */

   cout << getMaxSongs({8,4,5,6,7,9}, {100,150,55,75,71,15}, {"pop", "jazz", "country", "Latin", "Electro", "jazz"}, 300) << endl;   // 30
   cout << getMaxSongs({6,14,7,10,15,4,21,13,21,33,5,0,4}, {50,40,100,70,65,70,110,200,150,200,90,30,120}, {"pop", "alternate", "Rock", "Jazz", "jazz", "jazZ", "rock", "Alternate", "Electro", "EDM", "edm", "hiphop", "pop"}, 600) << endl; // 104
   /*
   pop -> (6,50), (4,120)
   alternate -> [(14,40)], (13,200)
   rock -> (7,100), [(21,110)]
   jazz -> (10,70), [(15,65)], (4,70)
   electro -> [(21,150)]
   edm -> [(33,200)], (5,90)
   hiphop -> (0,30)
   [] -> the ones that are picked.
   */
   
} 