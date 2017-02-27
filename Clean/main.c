#include <stdio.h>

FILE *lst;

#define COUNTER 125

void merge(int * lst, int a, int b, int s)
{
     int tmp[10], ti = a, ai = a, bi = b;
     while (ai < b || bi < s)
     {
          if (bi == s)               tmp[ti++] = lst[ai++];
          else if (ai == b)          tmp[ti++] = lst[bi++];
          else if (lst[ai] < lst[bi])     tmp[ti++] = lst[ai++];
          else                    tmp[ti++] = lst[bi++];
     }
     
     for (ti = a; ti < s; ti++)
          lst[ti] = tmp[ti];
}

void mergesort(int * lst, int a, int b)
{
     if (b-a < 2)
          return;

     mergesort(lst, a, a + (b-a)/2);
     mergesort(lst, a + (b-a)/2, b);
     merge(lst, a, a + (b-a)/2, b);
}

int main(int argc, char **argv)
{
     int i=0,pass=0;
     double mean=0,num,sam_var,stnd_dev;
     char c;
     FILE *fp,*fout;
     char output_file[] = "output.txt";

     float *lst = (float *)malloc(sizeof(float)*COUNTER);
     

     while (c=getc(fp) != EOF)
     {
          lst[i] = getfloat(fp);
          fout = openFile(output_file,"w"); 
          mean+=lst[i];
          if (i >= 125)
          {
               pass++;
               
          }               
     }
 
     mergesort(lst, 0, 10);
     for (i = 0; i < 10; i++)
          printf("%d ", lst[i]);

     printf("\n");
     return 0;
}

