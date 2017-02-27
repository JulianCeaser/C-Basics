int max (int *a, int n, int i, int j, int k)
{
	int m = i;
	if (j < n && a[j] > a[m])
		m = j;
	if (k < n && a[k] > a[m])
		m = k;
	return m;
}
