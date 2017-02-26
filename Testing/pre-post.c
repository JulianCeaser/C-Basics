#include <stdio.h>
void main()
{
	int i,j;
	i=1;
	j=++i;
	printf("\ni = %d, j = %d\n",i,j);
	i=1;
	j=i++;
	printf("\ni = %d, j = %d\n",i,j);
}