#include <stdlib.h>
#include <stdio.h>
#define EXIT_FAILURE 1
#include "mean.h"
#include "getfloat.h"
#include <string.h>
#include <unistd.h>



#define FLOATSIZE   4   
#define BUFFSIZE 512     //can hold 102400/4 = 25,600 (4 byte) floating point numbers

FILE *lst;
float *floatList,*zscorelist;

#define COUNTER 125
//extern FILE* openFile(char* fileName, char* mode);

void merge(float * lst, int a, int b, int s)
{
    float tmp[s];
    int ti = a, ai = a, bi = b;
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

void mergesort(float * lst, int a, int b)
{
     if (b-a < 2)
          return;

     mergesort(lst, a, a + (b-a)/2);
     mergesort(lst, a + (b-a)/2, b);
     merge(lst, a, a + (b-a)/2, b);
}


/*

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

 */

int main(int argc, char **argv)
{
    FILE *fp;
    double var;
    int i=0,size;
    float mean;

    fp = fopen(argv[1],"r");
    if ( fp == NULL)
    {
        printf("\nUnable to open input file");
        exit(1);
    }
    
    floatList = (float *)malloc(sizeof(float)*BUFFSIZE);
    
    do 
    {
        getfloat(fp,(floatList+i));
        ++i;
        printf("\ni=%d",i);
        if(i<=BUFFSIZE)
        {
            //mergesort
            //
            //return 1 for success, -1 for failure
            //memstet floatlist
            //continue
        }
    }while(!feof(fp));
    
    size = i-1;
    fclose(fp);

 /*   //create a input file
    
    fp = fopen("inputarray.txt","w");
    if ( fp == NULL)
    {
        printf("\nUnable to open file inputarray.txt");
        exit(1);
    }
    for(i=0;i<size;++i)
        fprintf(fp,"%f\n",*(floatList+i));
    
    fclose(fp); */

    mergesort(floatList,0,size); //Mergesort the current List

//    mean = compute_mean(floatList,size); // Find mean of the current List

//    var = compute_sample_var(mean,floatList,size); //Sample variance

//    for(

    //Store the current list in output-array (can be temporary file)
    
    fp = fopen("output-array.txt","w");
    if ( fp == NULL)
    {
        printf("\nUnable to open file output-array.txt");
        exit(1);
    }
    for(i=0;i<size;++i)
        fprintf(fp,"%f\n",*(floatList+i));
        
    fclose(fp);

  /*  //Store the current variance in output-array (can be temporary file)
    
    fp = fopen("variance-array.txt","w");
    if ( fp == NULL)
    {
        printf("\nUnable to open file variance-array.txt");
        exit(1);
    }
    for(i=0;i<size;++i)
        fprintf(fp,"%f\n",*(var+i)); */


    return 0;
}

/*


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

*/


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

