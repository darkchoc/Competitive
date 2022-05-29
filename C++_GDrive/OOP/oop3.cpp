#include <bits/stdc++.h>

using namespace std;

class A{
protected:
	int data;
	void func(){
		data=1;
		cout << data << endl;
	}
	void func3(){
		cout << "private func" << endl;
	}
public:
	int data2;
	A(){
		data=3;
		data2=5;
	}
	void func2(){
		data2=3;
		cout << data2 << endl;
	}
	void func4(){
		cout << "not private method" << endl;
	}
};

class B: public A{
public:
	void func(){
		cout << data << endl;
	}
	void func2(){
		cout << data2 << endl;
	}
	void func5(){
		func3();
	}
};

int main(){
	B* b = new B();
	b->func();
	b->func2();
	b->func4();
	b->func5();
	return 0;
}