#include <bits/stdc++.h>

using namespace std;

class Parent {
	public:
		int age;
		Parent(){
			age = 30;
		}
		void print(){
			cout << "This is parent print\n";
		}
		virtual void virtualPrint(){
			cout << "This is parent virtual print\n";
		}
};

class Child: public Parent {
	public:
		int age;
		Child(){
			age=10;
		}
		void print(){
			cout << "This is child print\n";
		}
		void virtualPrint(){
			cout << "This is child virtual print\n";
		}
};

int main(){
	Parent* p = new Parent();
	cout << p->age <<  " " << endl; //30
	p->print(); //This is parent print
	p->virtualPrint(); //This is virtual parent print
 

	Parent* p2 = new Child();
	/*
	base class pointer pointing to derived class object will call base class's functions and access base class's fields,
	but if the function is virtual, then it will call the derived class function.  

	This is because in C++ we have STATIC / COMPILE TIME POLYMORPHISM (EARLY BINDING). So what function will be called is decided at compile time itself. Since pointer is of parent type, it will call functions of parent class, unless it is a virtual function, in which case it will call function of child class. So using "virtual" keyword allows a function to achieve DYNAMIC/RUNTIME PLOYMORPHISM (LATE BINDING), where method to be called is determined at runtime by looking at the object the pointer is pointing to.

	In case of Java, we have RUNTIME/DYNAMIC POLYMORPHISM. All functions are virtual by default. 

	*/
	cout << p2->age << " " << endl; //30
	p2->print(); //This is parent print
	p2->virtualPrint(); //This is child virtual print

	/*
	For being able to access derived class fields or non-virtual functions through base class pointer, we need to typecast.
	Dynamic type cast if you aren't sure, static type cast if you're sure. In case of dynamic type case, nullptr is returned if
	typecast fails.
	*/
	cout << dynamic_cast<Child*>(p2)->age << endl; //10
	static_cast<Child*>(p2)->print(); //This is child print
	static_cast<Child*>(p2)->virtualPrint(); //This is child virtual print

	/*
	A deried class pointer can access base class members and fields like this.
	*/
	Child *c = new Child();
	cout << c->age << endl;//10
	cout << c->Parent::age << endl; //30
	c->Parent::print(); //This is parent print
	c->Parent::virtualPrint(); //This is parent virtual print
	return 0;
}