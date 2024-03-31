#include <bits/stdc++.h>
using namespace std;

int main(){
    
    vector<int> a ({1,2,4,5,5,5,6,7});
    cout << (*lower_bound(a.begin(), a.end(), 2)) << endl; // 2
    cout << (*upper_bound(a.begin(), a.end(), 2)) << endl; // 4
    cout << (*lower_bound(a.begin(), a.end(), 3)) << endl; // 4
    cout << (*upper_bound(a.begin(), a.end(), 3)) << endl; // 4
    cout << (*lower_bound(a.begin(), a.end(), 5)) << endl; // 5
    cout << (*upper_bound(a.begin(), a.end(), 5)) << endl; // 6
    cout << (*lower_bound(a.begin(), a.end(), 0)) << endl; // 1
    cout << (*upper_bound(a.begin(), a.end(), 0)) << endl; // 1
    cout << (*lower_bound(a.begin(), a.end(), 7)) << endl; // 7
    cout << (*upper_bound(a.begin(), a.end(), 7)) << endl; // a.end()
    cout << (*lower_bound(a.begin(), a.end(), 8)) << endl; // a.end()
    cout << (*upper_bound(a.begin(), a.end(), 8)) << endl; // a.end()

}