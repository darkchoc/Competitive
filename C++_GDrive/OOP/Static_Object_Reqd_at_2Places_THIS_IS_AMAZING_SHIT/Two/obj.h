#ifndef OBJ_H_
#define OBJ_H_

#include <bits/stdc++.h>

using namespace std;

class Obj{
protected:
	static int* ptr; 
public:
	static int* get_ptr(){
		return ptr;
	}
};

int* Obj::ptr = nullptr;

#endif
