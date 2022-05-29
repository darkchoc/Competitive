#include <bits/stdc++.h>
#include <typeinfo>

using namespace std;

int main(){
	char abc[20];
	char *ptr = abc;
	strcpy(abc, "abcdefgh");
	// abc -> pointer to character, value being abcdefgh
	// *abc -> first character, value being a
	// abc[2] -> character
	// &abc[0] -> of type char* and will give complete string from 0th index and not address of oth character coz -- see 2nd line from here regarding &abc[3]. &abc[0] when printed along with printf will be string from 0th character if we use %s, and will give address of 0th character if we use %p
	// &abc -> of type address char *[20], and returns starting address of the char array
	// &abc[3] -> of type char* and will give complete string from 3rd index. The reason it doesn't print the address of 3rd character is because in C++, when printing char*, it will keep printing till it encounter \0, null character. Had the array been of ints, we would have got address of third character. To get address of third character in this case, we have to type case it to (void*) so that c++ forgets that it is of type char*. [cout << (void*)&abc[3] ]. Simply doing &abc[3] will give address of 3rd character in printf if we use %p, and will give string from 3rd character onwards if we use %s
	// abc+4 -> value being char* and will give string from 4th index
	// *(abc+5) -> char type and will give character at 5th index
	// *(abc+5)+2 -> char, will add 2 into the character at 5th index, currently it is f, so will give h. But if we print using cout, we get 104 as answer coz it converts it into int, and f is 102 in int
	// ptr -> char* and will give complete string
	// &ptr -> address of first character of array
	// *ptr -> is char and will give value of 0th character
	

	printf("*ptr %c\n", *ptr);
        printf("ptr %s\n", ptr);
	printf("&abc[0] %p\n", &abc[0]);
        printf("(void*)&abc[0] %p\n", (void*)&abc[0]);
	printf("(void*)&abc[3] %p\n", (void*)&abc[3]);

	cout << "(void*)&abc[3] " << (void*)&abc[3] << endl;
	cout << "&abc " << typeid(&abc).name() << " " << &abc << endl;
	cout << "abc " << typeid(abc).name() << " " << abc << endl;
	cout << "*abc " << typeid(*abc).name() << " " << *abc << endl;
	cout << "abc[2] " << typeid(abc[2]).name() << " " << abc[2] << endl;
	cout << &abc[0] << endl;
	cout << "&abc[3] "  << typeid(&abc[3]).name() << " " << &abc[3] << endl;
	cout << "abc+4 " << typeid(abc+4).name() << " " << abc+4 << endl;
	cout << "*(abc+5) + 2 " << typeid(*(abc+5)+2).name() << " " << (*(abc+5))+2 << endl;
	cout << "*(abc+5) " << typeid(*(abc+5)).name() << " " << (*(abc+5)) << endl;
	cout << "abc[10] " << abc[10] << endl; //typeid(abc[10]) << " " << abc[10] << endl;
//	cout << "abc[12] " << tyepid(abc[12]) << " " << abc[12] << endl;
	cout << "&ptr " << &ptr << endl;//" " << typeid(&ptr) << " " << &ptr << endl; 
	printf("&ptr %p\n", &ptr);
//      printf("&ptr %s\n", &ptr); //error as &ptr is of char** type 
	return 0;
}
