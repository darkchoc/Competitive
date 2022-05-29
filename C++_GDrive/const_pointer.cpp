//This article: https://www.geeksforgeeks.org/difference-between-const-int-const-int-const-and-int-const/
//contains a good way at the end to understand what the variable means. Basically, decode from right to left.

#include <bits/stdc++.h>

using namespace std;

int main(){
	const int a_ = 5; // a_ is a constant int variable.

	//compilation error
	//a_ = 4;

	
	int const * pa_ = &a_; //decode from right to left. So pa_ is a pointer to a const int.
	//Compilation error
	// *pa_ = 4;
	const int * pa_2 = &a_; //same as int const * pa_ . That is, pointer to a integer constant.

	int b_ = 10;
	int * const pb_ = &b_; //pb_ is a constant pointer to an integer
	//Valid as pointer is constant, not the integer variable to which it is pointing.
	*pb_ = 15; 

	int c_ = 12;
	//Compilation error
	//pb_ = &c_;

	//Compilation error
	//pb_ = &a_; //because pb_ is a constant pointer to an interger

	int * ptr;
	//compilation error
	//ptr = &a_; //because ptr is pointer to a interger, whereas a_ is a const int.

	//Compilation error
	/*
	int const * const pa_3; //constant poniter to a constant integer
	pa_3 = &a_;
	//Intialization should take place there and then. Otherwise initialized with NULL.
	*/

	//Valid
	int const* const pa_3 = &a_;

	//The below is valid although this seems bit fishy. I thought the c_ would be 
	//typecasted to const, but it doesn't happen.
	int const* const pc_1 = &c_;
	cout << *pc_1 << endl;
	c_=14;
	cout << *pc_1 << endl;
	//This is invalid though.
	//*pc_1 = 16;
	//cout << *pc_1 << endl;



	return 0;

}