#include <stdlib.h>
#include <stdio.h>
#define EXIT_FAILURE 1
#include "mean.h"
#include "getfloat.h"
#include <string.h>
#include <unistd.h>



#define FLOATSIZE   4   
#define BUFFSIZE 102400     //can hold 102400/4 = 25,600 (4 byte) floating point numbers


FILE *lst;
float *floatList;

#define COUNTER 125
//extern FILE* openFile(char* fileName, char* mode);

void merge(int * lst, int a, int b, int s)
{
     int tmp[10], ti = a, ai = a, bi = b;
     while ((ai < b) || (bi < s))
     {
          if (bi == s)
            tmp[ti++] = lst[ai++];
          else if (ai == b) 
            tmp[ti++] = lst[bi++];
          else if (lst[ai] < lst[bi])
             tmp[ti++] = lst[ai++];
          else 
             tmp[ti++] = lst[bi++];
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




FILE* openFile(char* fileName, char* mode)
 {
     FILE* fp = fopen(fileName, mode);
     if (fp == NULL)
     {   
         perror("Error while opening the file\n");
         exit(EXIT_FAILURE);
     }   
     return fp; 
 }




int main(int argc, char *argv[])
{

    char* in_fname ;    
    char* out_fname ;
    int opt = 0;    
    int buffSize  = BUFFSIZE; //
    

    printf("\nUsage: sort -r [in_filename] -g [out_filename] -b [buffsize] ...\n");
    printf("Options:\n");
    printf("\t-r\t filename\tFile containing Floating point numbers\n");
    printf("\t-g\t filename\tGenerate Floating Point Numbers and write to filename\n");
    printf("\t-b\t buffsize\tSpecify in-memory swap buffsize where floating point numbers will be read at a time\n\n");

    printf("Total input argument counts =%d \n", argc);
    printf("Arguments received are follows \n");

    for (int i = 1; i< argc; i++) 
    {
        char* p;
        printf("arg[%d] = %s\t\n",i, argv[i]);
        // if (argc <2)||(argc >  ++argc 

        printf("strtol[argv[%d] = %ld", i, strtol(argv[i], &p, 10));
    } 

    

    while ((opt= getopt(argc, argv, "i:o:")) != -1) 
    {

        switch(opt) {
 
            case 'r':
                in_fname = optarg;
                printf("\nInput option value=%s", in_fname);
            break;
    
            case 'g':
                out_fname = optarg;
                printf("\nOutput option value=%s", out_fname);
                break;
            case 'b':
                if (optopt == 'i') {
                    printf("\nMissing mandatory input option");
                } else if (optopt == 'o') {
                    printf("\nMissing mandatory output option");
                } else {
                    printf("\nInvalid option received");
                }
            break;
         }
    }

}




/*
int main(int argc, char **argv)
{
     int i=0,pass=0;
     double mean=0,num,sam_var,stnd_dev;
     char c;
     FILE *fp,*fout;
     char output_file[] = "output.txt";

     floatList = (float*)malloc(COUNTER*sizeof(float));
     

     while ((c=getc(fp)) != EOF)
     {
          floatList[i] = getfloat(fp, floatList);
          fout = openFile(output_file,"w"); 
          mean+=floatList[i];
          if (i >= 125)
          {
               pass++;
               
          }               
     }
 
     mergesort(floatList, 0, 10);
     for (i = 0; i < 10; i++)
          printf("%d ", floatList[i]);

     printf("\n");
     return 0;
}
*/

