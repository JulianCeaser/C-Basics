void heapsort (int *a, int n)
{
	int i;
	for (i = (n-2)/2;i>=0;--i)
		downheap(a,n,i);
	for (i=0;i<n;++i)
	{
		int t=a[n-i-1];
		a[n-i-1]=a[0];
		a[0]=t;
		downheap(a,n-i-1,0);
	}
}
