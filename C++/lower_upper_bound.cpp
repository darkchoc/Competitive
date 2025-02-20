#include <bits/stdc++.h>
using namespace std;

int main(){
    // lower_bound -> gives first element that is not less than given number. Basically, first >= element.
    // upper bound -> gives first element that is greater than given number. Basically, first > element.
    vector<int> a ({1,2,4,5,5,5,6,7});
    cout << (*lower_bound(a.begin(), a.end(), 0)) << endl; // 1 - don't know why
    cout << (lower_bound(a.begin(), a.end(), 0) - a.begin()) << endl; // 0 - don't know why
    cout << (*lower_bound(a.begin(), a.end(), 1)) << endl; // 1
    cout << (lower_bound(a.begin(), a.end(), 1) - a.begin()) << endl; // 0
    cout << (*lower_bound(a.begin(), a.end(), 2)) << endl; // 2
    cout << lower_bound(a.begin(), a.end(), 2) - a.begin() << endl; // 1
    cout << (*upper_bound(a.begin(), a.end(), 2)) << endl; // 4
    cout << upper_bound(a.begin(), a.end(), 2) - a.begin() << endl; // 2
    cout << (*lower_bound(a.begin(), a.end(), 3)) << endl; // 4
    cout << (*upper_bound(a.begin(), a.end(), 3)) << endl; // 4
    cout << (*lower_bound(a.begin(), a.end(), 5)) << endl; // 5
    cout << lower_bound(a.begin(), a.end(), 5) - a.begin() << endl; // 3
    cout << (*upper_bound(a.begin(), a.end(), 5)) << endl; // 6
    cout << upper_bound(a.begin(), a.end(), 5) - a.begin() << endl; // 6
    cout << (*lower_bound(a.begin(), a.end(), 0)) << endl; // 1
    cout << (*upper_bound(a.begin(), a.end(), 0)) << endl; // 1
    cout << (*lower_bound(a.begin(), a.end(), 7)) << endl; // 7
    cout << (*upper_bound(a.begin(), a.end(), 7)) << endl; // a.end()
    cout << (*lower_bound(a.begin(), a.end(), 8)) << endl; // a.end()
    cout << lower_bound(a.begin(), a.end(), 8) - a.begin() << endl; // 8
    cout << (*upper_bound(a.begin(), a.end(), 8)) << endl; // a.end()

}