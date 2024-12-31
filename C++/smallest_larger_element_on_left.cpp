#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> arr {5, 9, 7, 8, 4, 6, 4, 8, 11};
    set<int> s;
    for(int i=0; i<arr.size(); i++){
        s.insert(arr[i]);
        set<int>::iterator it = s.upper_bound(arr[i]);
        if(it==s.end()){
            cout << -1 << " ";
        } else {
            cout << (*it) << " ";
        }
    }
    cout << endl;
}