#include <stdio.h>
#include <time.h>

int max (int *a, int n, int i, int j, int k)
{
     int m = i;
     if (j < n && a[j] > a[m])
          m = j;
     if (k < n && a[k] > a[m])
          m = k;
     return m;
}

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

int main()
{
     int a[] = {4,65,2,-31,0,99,2,83,782,1};
     int n = sizeof a/sizeof a[0];
     int i;
     clock_t t;
     double cpu_time_used;

     for(i=0;i<n;++i)
          printf("%d%s",a[i],i==n-1 ? "\n" : " ");
     
     t = clock();
     heapsort(a,n);
     t = clock() - t;
     cpu_time_used = ((double)t)/CLOCKS_PER_SEC; // in seconds

     for(i=0;i<n;++i)
          printf("%d%s",a[i],i==n-1 ? "\n" : " ");
     printf("\nHeapsort took %f seconds to execute \n",cpu_time_used);
     return 0;
}
