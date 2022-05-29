#include <bits/stdc++.h>
using namespace std;
int main(){
 string str = "Lol";
 vector<string> v;
 v.push_back(std::move(str));
 vector<string> v4;
 v4.push_back(str);
 vector<string> v3;
 vector<string> v2;
 v2 = std::move(v);
 v3 = v;
 cout << str << endl;
 cout << &str << endl;
 cout << &v[0] << endl;
 cout << &v2[0] << endl;
 cout << &v3[0] << endl;
 cout << &v4[0] << endl;
 return 0;
}
