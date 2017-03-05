#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "mean.h"
#include "genFloat.h"
#include "getfloat.h"
#include "heapsort.h"

#define EXIT_FAILURE 1


//#define FLOATSIZE   4   
//#define MAX_FLOATS_READ_IN_HEAP 25000
#define MAX_FLOATS_READ_IN_HEAP 2500

FILE *lst;
float *floatList,*zscorelist;

float *chunk_means;

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

    printf("\ncallHeapSort: Received Params: total_chunks =%d max_floats_read=%d\n", total_chunks, max_floats_read);
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
        getfloat(fp_list, Node_list->root_element);
        if ((Node_list->root_element) == NULL)
        {
            perror("Root element is null");
            return -1;
        }
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

void printBanner()
{
    printf("Usage Sequence 1.: main g\n");
    printf("Usage Sequence 2.: main s\n");

    printf("g [ this option generates Floating point Numbers in file input.txt ]\n");
    printf("s [ this option sorts in descending order Floating point Numbers in small chunks using Merge Sort\n");
    printf("     Each sorted chunk is then persisted in files. In the next step, the algorithm performs Heap Sort to merge the externally sorted files]\n\n"); 

}


int main(int argc, char **argv)
{
    FILE *fp,*fp1;
    double var;
    int num_of_floats_read,actual_nums_read,i,j,run_size;
    float mean;
    char temp_output[15];
    char output_file[] = "output.txt";
    char *input_file = "input.txt";
    clock_t t,t1;      // Timer variable
    double cpu_time_used;
    
    
    if (argc != 2) 
    {
        printBanner();
        exit (1); 
    }

    if ((argc == 2 ) && (( !strcmp(argv[1], "g"))))
    {
        genFloat(input_file);
        printf("Floating point numbers generated in %s\n", input_file);    

    }
    else if ((argc == 2 ) && (( !strcmp(argv[1], "s") )))
    {
        //fp = openFile(argv[1],"r");
        fp = openFile(input_file,"r");
        if ( fp == NULL)
        {
            printf("\nUnable to open input file");
            printf("\nTry running with option -g first before selecting option s");
            exit(1);
        }
        else
        {
            printf("\n Now starting to perform External Merge Sort \n"); 
            //
            //n = BUFFSIZE/sizeof(float) 
            floatList = (float *)malloc(sizeof(float)*MAX_FLOATS_READ_IN_HEAP );
            //printf("floatList pointer address : = %p, size allocated = %d", floatList, (int)sizeof(floatList));
 
            num_of_floats_read = 0, run_size = 0, actual_nums_read = 0 ; 
    
    
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
                printf("run_size = %d actual_nums_read=%d", run_size, actual_nums_read);
                //callHeapSort (run_size-1, (actual_nums_read+1) );
                callHeapSort (run_size, actual_nums_read );
            t = clock() - t;  // Final Time
            cpu_time_used = ((double)t)/CLOCKS_PER_SEC; // Time in seconds
            printf("\nTotal time taken to HeapSort is %lf secs\n",cpu_time_used);
   
        } 

    } else 
    {
        printf ("\n**Input Error: Improper usage option\n\n");
        printBanner();

    }

    return 0;
}


