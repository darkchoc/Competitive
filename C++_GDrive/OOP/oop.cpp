#include <bits/stdc++.h>

using namespace std;

struct type1{
	int val;
};

typedef struct type1 type1;

struct type2: public type1{
	type2(type1&) {

	}
	type2() {

	}

	int val2;
};

typedef struct type2 type2;

class A{
public:
	virtual type1 &my_func(int x, int y) = 0;

	static void func2(){
		cout << "Class A" << endl;
	}
};

class B: public A {
public:
	// virtual type1 &my_func(int x, int y){
	// 	obj.val = x;
	// 	obj.val2 = y;
	// 	return obj;
	// }

	type1 &my_func(int x, int y, int z){
		cout <<"Called" << endl;
		obj.val = x+y;
		obj.val2 = x+y+z;
		return obj;
	}

	static void func2(){
		cout <<"Class B" << endl;
	}

	type2 obj;
};

class C: public B{
public:
	virtual type1 &my_func(int x, int y){
		obj.val = x;
		obj.val2 = y;
		return obj;
	}

	type2 obj;
};

int main(){
	C objB;
	type2 &obj = static_cast<type2 &> (objB.B::my_func(2,3,4));
	cout << obj.val2 << endl;

	A::func2();
	return 0;
}