#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

	int add,sub,mul, div;
	int i= atoi(argv[1]);
	int j =atoi(argv[2]);
	
	add = i+j;	
	sub = i-j;
	mul = i * j;
	div = i/j;

	printf("%d + %d = %d\n",i,j,add);
 	printf("%d - %d = %d\n",i,j,sub); 
 	printf("%d x %d = %d\n",i,j,mul);  
	printf("%d / %d = %d\n",i,j,div);
//	wait(1);
	sleep(2);
	return 0;

}
