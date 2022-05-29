#include <bits/stdc++.h>

using namespace std;

class A{
public:
	A(){}
	static bool flag;
	static bool getflag(){
		return flag;
	}
};

void func(){
	if(A::getflag())
		cout << "flag is true";
	else
		cout << "flag is false";
	cout << endl;
}

bool A::flag = false;

int main(){
	cout << A::getflag() << endl;
	func();
	A::flag = true;
	cout << A::getflag() << endl;
	A* a = new A();
	a->flag = true;
	func();
	a->flag = false;
	func();
	return 0;
}