#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "mean.h"
#include "getfloat.h"
//#include "heapsort.h"

#define EXIT_FAILURE 1


//#define FLOATSIZE   4   
#define MAX_FLOATS_READ_IN_HEAP 128

FILE *lst;
float *floatList,*zscorelist;

//#define COUNTER 125
//extern FILE* openFile(char* fileName, char* mode);

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
/*Merge k sorted files. */

/*
void mergeFiles (char *output_file, int n, int k){
    // Array of file pointers to the chunks
    FILE *in[k];    
    for (int i=0; i<k; ++i){
        char fileName[15];
        
        //convert i to string
        sprintf(fileName,"temp%d.dat", i);
        
        // open output file in read mode
        in[i] = openFile(fileName, "r");
        printf("\nin[%d]",i);
    }

    //FINAL OUTPUT FILE
    FILE *out = openFile(output_file,"w");
    
    //Create a min heap with k heap nodes. Every heap node 
    //has first element of scratch output file 
    heapNode *minHeap[k];

    int i;
    for (i=0; i<k; ++i){
        createNode(minHeap[i],);
    }

    //Build min heap with entered elements
    buildHeap(minHeap,k-1);

    // Now one by one get the minimun element from min
    // heap and replace it with the next element.
    // run till all filled input files reach EOF
    
    for(i=0; i<n*k;++i){
        
        //Get the minimun element and store it in output file
        heapNode * minNode = minHeap[0];
        fprintf(out, "%d", minNode->data);

        //Find the next element that will replace current root
        //of heap. The next element belongs to same input
        //file as the current min element.
        if(minNode->itemNum+1 < k){
            minHeap[0] = createNode(in[minNode->arrayNum][minNode->itemNum+1],minNode->arrayNum,minNode->itemNum+1);                    
        }
        else{
            minHeap[0] = createNode(INT_MAX, minNode->arrayNum, minNode->itemNum+1);
        }
        
        //Replace root with next element of input file
        minHeapify(minHeap,0,k-1);
        
    }


    //for closing input and output files
    for(int i=0; i<k; ++i)
        fclose(in[i]);

    fclose(out);
}
*/

void merge(float * lst, int a, int b, int s )
{
    float tmp[s];
    int ti = a, ai = a, bi = b;
     while ((ai < b) || (bi < s))
     {
          if (bi == s)
            tmp[ti++] = lst[ai++];
          else if (ai == b) 
            tmp[ti++] = lst[bi++];
          // enable the below line for ascending order
          //else if (lst[ai] < lst[bi])
          
          // enable the below line for descending order
          else if (lst[ai] > lst[bi])
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




int main(int argc, char **argv)
{
    FILE *fp,*fp1;
    double var;
    int num_of_floats_read,actual_nums_read,i,j,run_size;
    float mean;
    char temp_output[15];
    char output_file[] = "output.txt";

    fp = openFile(argv[1],"r");
    if ( fp == NULL)
    {
        printf("\nUnable to open input file");
        exit(1);
    }
   
    //n = BUFFSIZE/sizeof(float) 
    floatList = (float *)malloc(sizeof(float)*MAX_FLOATS_READ_IN_HEAP );
    //printf("floatList pointer address : = %p, size allocated = %d", floatList, (int)sizeof(floatList));
 
    num_of_floats_read = 0, run_size = 1, actual_nums_read = 0 ;

    do 
    {
        //getfloat(fp,(floatList+i));     // Get each floating point number from input file
        getfloat(fp,(floatList+num_of_floats_read));     // Get each floating point number from input file
        if( feof(fp) )
            break;
        ++num_of_floats_read ;
        
        //If Buffer is filled then write out to temp files
        if(num_of_floats_read  == MAX_FLOATS_READ_IN_HEAP)
        {
            mergesort(floatList,0, num_of_floats_read);
            
            sprintf(temp_output,"temp%d.dat",run_size);
            fp1 = openFile(temp_output,"w");
            
            for(j=0;j<num_of_floats_read;++j)
                fprintf(fp1,"%f\n",*(floatList+j));
        
            actual_nums_read += num_of_floats_read ;
            //reset pointer to floatList to the beginning of the memory
            //printf("floatList = %p\n", floatList);
            //*floatList = *(floatList - num_of_floats_read);
            num_of_floats_read=0;
            run_size++;
            fclose(fp1);
            continue;
        }

        
        //If buffer is not filled then write out the last pass
    
        mergesort(floatList,0,num_of_floats_read-1);
            
        sprintf(temp_output,"temp%d.dat",run_size);
        fp1 = openFile(temp_output,"w");
        
        for(j=0;j<num_of_floats_read;++j)
            fprintf(fp1,"%f\n",*(floatList+j));

        fclose(fp1);

    }while(!feof(fp));
        
    actual_nums_read +=num_of_floats_read-1;
    fclose(fp); 

    //Merge runs using K-way merging
    
//    mergeFiles (output_file,MAX_FLOATS_READ_IN_HEAP,run_size);

//    mergesort(floatList,0,size); //Mergesort the current List

//    mean = compute_mean(floatList,size); // Find mean of the current List

//    var = compute_sample_var(mean,floatList,size); //Sample variance

//    for(

    //Store the current list in output-array (can be temporary file)
    
/*    fp = fopen("output-array.txt","w");
    if ( fp == NULL)
    {
        printf("\nUnable to open file output-array.txt");
        exit(1);
    }
    for(i=0;i<actual_nums_read;++i)
        fprintf(fp,"%f\n",*(floatList+i));
        
    fclose(fp);
*/
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

