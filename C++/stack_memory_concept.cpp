#include <bits/stdc++.h>
using namespace std;

typedef struct myStruct {
    int val;
} myStruct;

//This function will result in warning: address of stack memory associated with local variable 's' returned.
/*
What this means is that we are creating s in this function, and the memory allocated is on stack and not heap. When the function ends, this memory is freed. Even if it gives correct answer when we do cout << s->val in the main function, it can get corrupted as it is free to be used.
*/
myStruct* func(){
    myStruct s;
    s.val = 10;
    return &s; //returning pointer of local variable which is allocated on stack is wrong!!!
}

/*
this won't give this warning as here we are allocating memory from heap. It would persist. Basically we need to allocate memory dynamically. 
*/
myStruct* func2(){
    myStruct* s = new myStruct();
    s->val = 10;
    return s;
}

int main(){
    myStruct *s;
    s = func(); //gives warning
    cout << s->val << endl; //can be corrupted value too
    s = func2();
    cout << s->val << endl;
}