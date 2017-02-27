#include <stdio.h>
#include <time.h>
#include "functions.h"

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
