#include <stdio.h>
#include stdlib.h>
void func(int *a, int *b){
	*a = *a + *b;
}

int main(){
	int *a, *b;
	a =  b = NULL;
	a = (int *)malloc (sizeof (int) ) ;
	b = (int *)malloc (sizeof (int) ) ;
	*a = 5; *b = 10;
	printf( "%d" , *a );

}

