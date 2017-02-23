#include<stdio.h>

void merge(int a[], int low, int mid, int high)
{
	int tmp[11];
	int i = low, j = mid+1, k = 0;
	
	while(i <= mid && j <= high)
	{
		if (a[i] <= a[j])
				tmp[k++] = a[i++];
		
		else		
			tmp[k++] = a[j++];	
	}
	
	while ( i <= mid )
		tmp[k++] = a[i++];
	
	while ( j <= high)
		tmp[k++] = a [j++];
	
	k--;
	
	while (k >= 0)
	{
		a[low+k]=tmp[k];
		k--;
	}
	
//	for(k = low; k <= high; k++)
//      a[k] = tmp[k];
	
}

void mergesort(int array[],int low, int high)
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
	int i;
	int array[]= {10,9,8,7,6,5,4,3,2,1};
	mergesort(array,0,10);
	printf("\narray =");
	for(i=0;i<10;i++)
		{
			printf(" %d",array[i]);
		}
	printf("\n");
}