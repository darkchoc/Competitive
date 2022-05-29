#include <stdio.h> 
#include <string.h> 
#include <time.h> 
#include <stdlib.h>

/*   
char *get_date() 
{ 
    char    buf[80]; 
    time_t  now = time(0); 
    strcpy(buf, ctime(&now)); 
    return buf; 
} 
*/

int* get_arr(){
    //int arr[10];
    int* arr = (int*)calloc(10, 4);
    for(int i=0; i<10; i++)
	arr[i] = i;
    return arr;
}

int main(int argc, char *argv[]) 
{ 
    //char *date = get_date(); 
    //printf("date=%s\n", date); 
    int * arr = get_arr();
    for(int i=0; i<10; i++)
	printf("%d ", arr[i]);
    printf("\n");
    return 0; 
}
