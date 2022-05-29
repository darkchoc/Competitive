#include <bits/stdc++.h>
#include "topparent.h"

using namespace std;

class A : public P{
public:
	A(){
		cout << "constructor of A called \n";
	}
	void func3(){
		this->func();
	}
	static void func(){
		cout << "In func of A" << endl;
	}
};
