#include <bits/stdc++.h>
using namespace std;

class A {
public:
	A(int x){
 		cout << "value of x is " << x << endl;
	}
};

class B: public A{
public:
	B(string s) : A(5) {
		cout << "String for B is " << s << endl;
	}
};

int main(){
	B* b = new B("Lol");
	return 0;
}
