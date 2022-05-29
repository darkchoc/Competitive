#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int main(int argc, char* argv[]){
	char *arr[3];
	arr[0]="one";
	arr[1]="two";
	arr[2]="three";
	char arr_[5];
	strcpy(arr_, "ones");
        printf("%s\n%s\n%s\n%s\n", arr[0], arr[1], arr[2], arr_);
	return 0;
}
