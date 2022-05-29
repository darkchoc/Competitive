#include <bits/stdc++.h>
#include "myheader.h"

using namespace std;

class B : public A {
public:
B(){
	cout << "Constructor of B called" << endl;
}

	static void func(){
		cout << "In func of B" << endl;
	}
};

int main(){
	P* ptr_p = new A();
	ptr_p->func3();
	P* ptr_p2 = new B();
	 ptr_p2->func3();
	((B*)ptr_p2)->func3();
	return 0;
}
