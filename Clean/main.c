#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <unistd.h>
#include <time.h>

#include "mean.h"
#include "getfloat.h"
#include "heapsort.h"

#define EXIT_FAILURE 1


//#define FLOATSIZE   4   
//#define MAX_FLOATS_READ_IN_HEAP 25000
#define MAX_FLOATS_READ_IN_HEAP 2500

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


int callHeapSort (int total_chunks, int max_floats_read)
{

    //int total_chunks = CHUNKS ;
    //int max_floats_read = TOTAL_FLOATS;
    char *filename_chunk;
    FILE *fp_list; //List of file pointer

    FILE *fp_output; 
    fp_output = openFile("merged_output.txt","w");

   
    heapNode *Node_list;
    
    // create a dynamic array containing list of heapNode
    // size of dynamic array is set to total number of external chunks 
    Node_list = (heapNode*)malloc(sizeof(heapNode)*total_chunks);

    // intialize memory for root_index 
    Node_list->root_index = (FILE *)malloc(sizeof(FILE));
    // intialize memory for root_element 
    Node_list->root_element = (float *)malloc(sizeof(float));

    // List to maintain file descriptors for reading each external chunk
    fp_list = (FILE *)malloc(sizeof(FILE)*total_chunks);
    //fp_array = (FILE **)malloc(sizeof(FILE *)*total_chunks);

    
    filename_chunk = (char *)malloc(sizeof(char*));

     for(int i=1;i<=total_chunks;++i)
    {   
        Node_list->root_index = (FILE *)malloc(sizeof(FILE));
        Node_list->root_element = (float *)malloc(sizeof(float));
    
        sprintf(filename_chunk,"temp%d.dat",i);
        fp_list = openFile(filename_chunk,"r");
    
        //Storing file pointer index in the Nodelist
        Node_list->root_index = fp_list;


        //Getfloat takes the filepointer fp and stores the root element into Nodelist->root_element
        //printf("\nfp_list = %p, Node_list->root_element = %p",fp_list,Node_list->root_element);
        getfloat(fp_list,Node_list->root_element);
        if ((Node_list->root_element) == NULL)
            perror("Root element is null");
            return -1;

        fp_list++;
        Node_list++;
    }



    // Very Important 
    //Now reset the Node_list pointer to the begining of the Node_list
    Node_list = Node_list - total_chunks;




    //First pass of 1 element per chunk sent to Heapify

    #ifdef DEBUG_ENABLED

        printf("\nNode_list pointer = %p,root_index = %p, total_chunks = %d\n",
                                  Node_list,    Node_list->root_index,  total_chunks);

        printf("\nNode_list pointer at index 0 = %p\n",(Node_list));
        printf("\nNode_list pointer at index 1 = %p\n",(Node_list+1));
    #endif


    // Calling Min-HEAPSORT 
    //MIN_HEAPSORT (Node_list, total_chunks);


    // Calling Max-HEAPSORT 
    //MAX_HEAPSORT (Node_list, total_chunks);

    SORT_HEAP_AND_WRITE_OUTPUT (Node_list, fp_output, total_chunks, max_floats_read );

    if(Node_list != NULL )
        free(Node_list);

    return 1;


}

int main(int argc, char **argv)
{
    FILE *fp,*fp1;
    double var;
    int num_of_floats_read,actual_nums_read,i,j,run_size;
    float mean;
    char temp_output[15];
    char output_file[] = "output.txt";
    clock_t t,t1;      // Timer variable
    double cpu_time_used;

    if (argc != 2) 
    {
        printf("Usage : main <input.txt>");  
    }
     
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
    
    
    t = clock(); // Initial Time
    t1 = t;

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
        
            #ifdef TIMER
                t1 = clock() - t1;
                cpu_time_used = ((double)t1)/CLOCKS_PER_SEC; // Time in seconds
                printf("\nMergesort for chunk %d complete. Time taken is %lf \n",run_size,cpu_time_used);
            #endif /* TIMER */

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

        #ifdef TIMER
            t1 = clock() - t1;
            cpu_time_used = ((double)t1)/CLOCKS_PER_SEC; // Time in seconds
            printf("\nMergesort for chunk %d complete. Time taken is %lf\n",run_size,cpu_time_used);
        #endif /* TIMER */
        
        fclose(fp1);

    }while(!feof(fp));
        
    t = clock() - t;    // Final Time
    cpu_time_used = ((double)t)/CLOCKS_PER_SEC; // Time in seconds

    printf("\nTotal Time Taken to generate Sorted chunks using Merge Sort is %lf secs\n",cpu_time_used);
    
    
    actual_nums_read +=num_of_floats_read-1;
    fclose(fp); 

    printf ("Merge Sort of Individual Chunks Complete\n");
    printf ("Calling HeapSort to Merge sorted chunks \n");
    t = clock(); // Initial Time
        callHeapSort (run_size, actual_nums_read );
    t = clock() - t;  // Final Time
    cpu_time_used = ((double)t)/CLOCKS_PER_SEC; // Time in seconds
    printf("\nTotal time taken to HeapSort is %lf secs\n",cpu_time_used);
    
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
