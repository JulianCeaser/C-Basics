#include<stdio.h>
#include<stdlib.h>

//int* array= {10,9,8,7,6,5,4,3,2,1};

void merge(int* array, int low, int mid, int high)
{
	int tmp[10];
	int i = low, j = mid+1, k = 0;
	
	while(i <= mid && j <= high)
	{
		if (array[i] <= array[j])
				tmp[k++] = array[i++];		
		else		
			tmp[k++] = array[j++];	
	}	
	while ( i <= mid )
		tmp[k++] = array[i++];	
	while ( j <= high)
		tmp[k++] = array[j++];	
	k--;	
	while (k >= 0)
	{
		array[low+k]=tmp[k];
		k--;
	}
	
//	for(k = low; k <= high; k++)
//      a[k] = tmp[k];
	
}

void mergesort(int* array,int low, int high)
{
	if (low < high)
	{
		int mid = (low+high)/2;
		mergesort(array,low,mid);
		mergesort(array,mid+1,high);
		merge(array,low,mid,high);
	}
}

void main()
{
	int i, *array;
	array = (int*) malloc(10*sizeof(int));
	
	for(i=0;i<10;++i)
		*(array+i)=75-(3*i);
	
	mergesort(array,0,10);
	printf("\narray =");
	for(i=0;i<10;i++)
		{
			printf(" %d",array[i]);
		}
	printf("\n");
	free(array);
}