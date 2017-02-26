#include<stdio.h>
#include<stdlib.h>

void main()
{
	int *A,i;
	A = (int *) malloc (10*sizeof(int));
	for(i=0;i<10;++i)
		*(A+i)=75-(3*i);
	for(i=0;i<10;++i)
		printf("A[i] = %d ",A[i]);	
	printf("\n");
}