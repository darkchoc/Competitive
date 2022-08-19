#include <bits/stdc++.h>
using namespace std;

int rows, cols, obs;
unordered_map<int, vector<int> > obstaclePerRow;
unordered_map<int, vector<int> > obstaclePerCol;

void init(int R, int C, int M, vector<int> &mR, vector<int> &mC){
    rows = R;
    cols = C;
    obs = M;
    for(int i=0; i<M; i++){
        obstaclePerRow[mR[i]].push_back(mC[i]);
        obstaclePerCol[mC[i]].push_back(mR[i]);
    }
    for(auto it = obstaclePerRow.begin(); it!=obstaclePerRow.end(); it++)
        sort(it->second.begin(), it->second.end());
    for(auto it = obstaclePerCol.begin(); it!=obstaclePerCol.end(); it++)
        sort(it->second.begin(), it->second.end());   
}

int binary_search_smaller(vector<int> &arr, int x){
    if(arr[0] > x)
        return -1;
    int low = 0, high = arr.size()-1;
    while(low < high){
        int mid = (low + high + 1)/2;
        if(arr[mid] > x)
            high = mid-1;
        else
            low = mid;
    }
    return low;
}

int binary_search_larger(vector<int> &arr, int x){
    if(arr[arr.size()-1] < x)
        return -1;
    int low = 0, high = arr.size()-1;
    while(low < high){
        int mid = (low + high)/2;
        if(arr[mid] < x)
            low = mid+1;
        else
            high = mid;
    }
    return low;
}

void commonPart(int newx, int newy, int d, map<pair<int, int>, int > &distance, set<vector<int> > &minPq){
    pair<int, int> newPair = make_pair(newx, newy);
    if(distance.find(newPair)!=distance.end()){
        if(distance[newPair] > d + 1){
            minPq.erase({distance[newPair], newx, newy});
            distance[newPair] = d+1;
            minPq.insert({distance[newPair], newx, newy});
        }
    } else {
        distance[newPair] = d+1;
        minPq.insert({distance[newPair], newx, newy});
    }
}

int djikstra(int sx, int sy, int dx, int dy, map<pair<int, int>, int > &distance, set<vector<int> > &minPq){

    distance[make_pair(sx, sy)] = 0;
    minPq.insert({0, sx, sy});

    while(!minPq.empty()){
        vector<int> p = *minPq.begin();
        minPq.erase(minPq.begin());
        int x = p[1], y = p[2], d = p[0];
        //cout << x << " " << y << " " << d << endl;
        //up
        if(obstaclePerCol.find(y)!=obstaclePerCol.end()){
            int ind = binary_search_smaller(obstaclePerCol[y], x);
            if(ind != -1){
                if(dy == y && dx > obstaclePerCol[y][ind])
                    return d; //can go straight up to destination
                int newx = obstaclePerCol[y][ind] + 1;
                int newy = y;
                commonPart(newx, newy, d, distance, minPq);
                
            }
        } else if(dy == y && dx < x) {
            return d; //can go straight up to destination
        }
        //down
        if(obstaclePerCol.find(y)!=obstaclePerCol.end()){
            int ind = binary_search_larger(obstaclePerCol[y], x);
            if(ind != -1){
                if(dy == y && dx < obstaclePerCol[y][ind])
                    return d; //can go straight up to destination
                int newx = obstaclePerCol[y][ind] - 1;
                int newy = y;
                commonPart(newx, newy, d, distance, minPq);
                
            }
        } else if(dy == y && dx > x) {
            return d; //can go straight up to destination
        }
        //right
        if(obstaclePerRow.find(x)!=obstaclePerRow.end()){
            int ind = binary_search_larger(obstaclePerRow[x], y);
            if(ind != -1){
                if(dx == x && dy < obstaclePerRow[x][ind])
                    return d; //can go straight up to destination
                int newx = x;
                int newy = obstaclePerRow[x][ind] - 1;
                commonPart(newx, newy, d, distance, minPq);
                
            }
        } else if(dx == x && dy > y) {
            return d; //can go straight up to destination
        }
        //left
        if(obstaclePerRow.find(x)!=obstaclePerRow.end()){
            int ind = binary_search_smaller(obstaclePerRow[x], y);
            if(ind != -1){
                if(dx == x && dy > obstaclePerRow[x][ind])
                    return d; //can go straight up to destination
                int newx = x;
                int newy = obstaclePerRow[x][ind] + 1;
                commonPart(newx, newy, d, distance, minPq);
                
            }
        } else if(dx == x && dy < y) {
            return d; //can go straight up to destination
        }
    }
    return -1;
}

int minDamage(int sx, int sy, int dx, int dy){
    map<pair<int, int>, int> distance;
    set<vector<int> > minPq;
    if(sx==dx && sy==dy)
        return 0;
    return djikstra(sx, sy, dx, dy, distance, minPq);
}

int main(){
    int r = 6, c = 10, m = 16;
    vector<int> mR = {0, 2, 0, 3, 0, 5, 5, 1, 1, 2, 2, 5, 3, 3, 4, 4};
    vector<int> mC = {1, 4, 5, 4, 6, 8, 5, 3, 8, 3, 5, 4, 0, 9, 2, 7};
    init(r, c, m, mR, mC);
    if(minDamage(5, 0, 5, 2) != 0) cout << "Failed 1" << endl; 
    if(minDamage(2, 7, 2, 7) != 0) cout << "Failed 2" << endl; 
    if(minDamage(5, 9, 2, 7) != 3) cout << "Failed 3"  << endl; 
    if(minDamage(2, 7, 5, 9) != -1) cout << "Failed 4" << endl;
    if(minDamage(3, 8, 2, 2) != 7) cout << "Failed 5" << endl; 
    if(minDamage(0, 4, 2, 9) != 5) cout << "Failed 6" << endl; 
    if(minDamage(2, 1, 2, 7) != -1) cout << "Failed 7" << endl;
    if(minDamage(5, 3, 0, 3) != -1) cout << "Failed 8" << endl;
    if(minDamage(3, 5, 4, 8) != 1) cout << "Failed 9" << endl; 
    if(minDamage(5, 7, 0, 7) != 3) cout << "Failed 10" << endl; 
    if(minDamage(4, 5, 3, 7) != 1) cout << "Failed 11" << endl; 
    if(minDamage(2, 1, 3, 2) != 1) cout << "Failed 12" << endl; 
}