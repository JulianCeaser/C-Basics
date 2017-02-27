void downheap (int *a, int n, int i)
{
	while(1)
	{
		int j = max(a, n, i, 2*i+1, 2*i+2);
		if ( j == i )
			break;
		int t = a[i];
		a[i] = a[j];
		a[j] = t;
		i = j;
	}
}
