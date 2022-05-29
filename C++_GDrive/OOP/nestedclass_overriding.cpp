#include <bits/stdc++.h>
using namespace std;

class A{
 public:
  void start(){
    A_inner a;
    a.func();
  }
 protected:
  class A_inner{
   public:
    void func(){
      cout << "Inside A_inner\n";
    }
  };
};

class B : public A{
 public:
  void start(){
    B_inner b;
    b.func();	  
  }
 protected:
  class B_inner : public A::A_inner {
    public:
     void func(){
        cout << "First calling A_inner::func()\n";
	A::A_inner::func();
        cout << "Inside B_inner\n";
     }
  };
};
int main(){
   B* b = new B();
   b->start(); 
   return 0;
}
