#include "getfloat.h"
#include "heapsort.h"

#define CHUNKS 4
#define TOTAL_FLOATS 10000

//#define DEBUG_ENABLED

int TEST_FLAG = 0;


FILE* openFile(char* fileName, char* mode)
  {
      FILE* fp = fopen(fileName, mode);
      if (fp == NULL)
      {
          printf("Error while opening %s in mode =%s \n", fileName, mode);
          exit(EXIT_FAILURE);
      }
      return fp;
  }

int PARENT (int i)
{
    return (i/2);
}

int LEFT ( int i)
{
    return (2*i + 1);
    //return (2*i);
}
int RIGHT ( int i)
{
    return (2*i+2);
    //return (2*i+1);
}    

void swap ( float *px, float *py, FILE **fp1, FILE **fp2)
{
    #ifdef DEBUG_ENABLED
        printf("\nBefore swap index element = %f, largest_index element = %f\n", *px, *py);
    #endif
    
    // swap px and py
    float tmp;

    tmp = *px;
    *px = *py;
    *py = tmp;

    // swap fp1 and fp2
    FILE *fp3;
    
    fp3 = *fp1;
    *fp1 = *fp2;
    *fp2 = fp3;

    #ifdef DEBUG_ENABLED
        printf("\nAfter swap index element = %f, largest_index element = %f\n", *px, *py);
    #endif

} 

/*void swap_FP ( FILE *px, FILE *py)
{
    #ifdef DEBUG_ENABLED
        printf("\nBefore swap File Pointer = %p y = %p", *px, *py);
    #endif
    
    FILE *tmp;

    tmp = px;
    px = py;
    py = tmp;
    
    #ifdef DEBUG_ENABLED
        printf("\nAfter swap File Pointer = %p y = %p", *px, *py);
    #endif

} */


void DISPLAY_HEAP(heapNode *A, int len)
{
    //#ifdef DEBUG_ENABLED
        printf ("Inside DISPLAY_HEAP\n");
    //#endif
    
    for (int i = 0; i < len; i++)
        printf("Inside A[%d] - root index = %p, root_element is  = %f\n",i, (A+i)->root_index ,*((A+i)->root_element));
    
    //#ifdef DEBUG_ENABLED
        printf ("Exiting DISPLAY_HEAP\n");
    //#endif

}
/*
void MIN_HEAPIFY (heapNode *A, int index, int len)
{

    #ifdef DEBUG_ENABLED
        printf("\nEntering MIN_HEAPIFY \n ");
        printf("\n Received Params : A = %p index = %d  len = %d\n",A, index, len);
        printf("Inside A[%d] - root_element is  = %f\n",index, *((A+index)->root_element));
    #endif

    // Applying Cormen's Algorithm but adjusted for Smallest instead of largest 

    int i = index;
    int l, r, smallest_index ;

    l = LEFT(i);
    r = RIGHT(i);
    smallest_index = i;
    
    #ifdef DEBUG_ENABLED
        printf("LEFT = %d\nRIGHT=%d\n smallest_index=%d Heap size = %d\n", l, r, smallest_index, len);
    #endif
    
    if ((l < len ) && (*((A+l)->root_element) < *((A+i)->root_element)))
          smallest_index = l;
    else
         smallest_index = i;

    if ((r< len) && (*((A+r)->root_element) < *((A+smallest_index)->root_element)))
        smallest_index= r;
    if (smallest_index != i )
    {
        #ifdef DEBUG_ENABLED
            printf("\nBefore swap  A[%d] = %f A[%d] = %f \n", i, *((A+i)->root_element), smallest_index, *((A+smallest_index)->root_element));
        #endif

        swap ( (A+i)->root_element, (A+smallest_index)->root_element, &(A[i]->root_index), &(A[smallest_index]->root_index );
        //swap_FP (((A+i)->root_index), ((A+smallest_index)->root_index);
        

        #ifdef DEBUG_ENABLED
            printf("\nafter swap  A[%d] = %f A[%d] = %f \n", i, *((A+i)->root_element), smallest_index, *((A+smallest_index)->root_element));
            printf ("\nMIN_HEAPIFY Params : A =%p, smallest_index = %d, len = %d\n", A, smallest_index,len); 
        #endif
            
        MIN_HEAPIFY (A, smallest_index, len);
        //minHeapify (A, smallest_index, len);

    } 

    #ifdef DEBUG_ENABLED
        printf("\nExiting MIN_HEAPIFY \n");
    #endif
}

*/
void MAX_HEAPIFY (heapNode *A, int index, int len)
{

    #ifdef DEBUG_ENABLED
        printf("\nEntering MAX_HEAPIFY \n ");
        printf("\n Received Params : A = %p index = %d  len = %d\n",A, index, len);
        printf("Inside A[%d] - root_element is  = %f\n",index, *((A+index)->root_element));
    #endif

    /* Applying Cormen's Algorithm  */

    int i = index;
    int l, r, largest_index ;

    l = LEFT(i);
    r = RIGHT(i);
    largest_index = i;
    
    #ifdef DEBUG_ENABLED
        printf("LEFT = %d\nRIGHT=%d\n largest_index=%d Heap size = %d\n", l, r, largest_index, len);
    #endif

    if ((l < len ) && (*((A+l)->root_element) > *((A+i)->root_element)))
          largest_index = l;
    else
          largest_index = i;

    if ((r< len) && (*((A+r)->root_element) > *((A+largest_index)->root_element)))
        largest_index= r;
    if (largest_index != i )
    {
        #ifdef DEBUG_ENABLED
            printf("\nBefore swap  A[%d] = %f A[%d] = %f \n", i, *((A+i)->root_element), largest_index, *((A+largest_index)->root_element));
            printf("\n\nBefore swap, (A[i].root_element) = %f, (A[largest_index].root_element) = %f", *(A[i].root_element), *(A[largest_index].root_element));
            printf("\n\nBefore swap, (A[i].root_index) = %p, (A[largest_index].root_index) = %p", (A[i].root_index), (A[largest_index].root_index));
        #endif

        swap ( (A+i)->root_element, (A+largest_index)->root_element, &(A[i].root_index), &(A[largest_index].root_index));
        
        #ifdef DEBUG_ENABLED
            printf("\nAfter swap  A[%d] = %f A[%d] = %f \n", i, *((A+i)->root_element), largest_index, *((A+largest_index)->root_element));
            printf("\n\nAfter swap, (A[i].root_element) = %f, (A[largest_index].root_element) = %f", *(A[i].root_element), *(A[largest_index].root_element));
            printf("\n\nAfter swap, (A[i].root_index) = %p, (A[largest_index].root_index) = %p", (A[i].root_index), (A[largest_index].root_index));
            printf ("MAX_HEAPIFY Params : A =%p, largest_index = %d, len = %d", A, largest_index,len);
        #endif 
        
        MAX_HEAPIFY (A, largest_index, len);

    } 

        
    #ifdef DEBUG_ENABLED
        printf("\nExiting MAX_HEAPIFY \n");
    #endif

}



/*

void BUILD_MIN_HEAP(heapNode *A, int len)
{
    #ifdef DEBUG_ENABLED
        printf("\nEntering BUILD_MIN_HEAP \n");
    #endif

    for ( int i = (len)/2-1; i>=0; i--) { 
        #ifdef DEBUG_ENABLED
            printf ("Calling MIN_HEAPIFY from BUILD_MIN_HEAP\n ");       
            printf ("Calling with Params : index = %d \n ", i);       
        #endif

        MIN_HEAPIFY (A, i, len);
    } 
    
    #ifdef DEBUG_ENABLED
        printf("\nExiting BUILD_MIN_HEAP \n");
    #endif

}
*/

void BUILD_MAX_HEAP(heapNode *A, int len)
{
    #ifdef DEBUG_ENABLED
        printf("\nEntering BUILD_MAX_HEAP \n");
    #endif

    for ( int i = (len)/2-1; i>=0; i--) { 
        #ifdef DEBUG_ENABLED
            printf ("Calling MAX_HEAPIFY from BUILD_MAX_HEAP\n ");       
            printf ("Calling with Params : index = %d \n ", i);       
        #endif
        
        MAX_HEAPIFY (A, i, len);
    } 

    #ifdef DEBUG_ENABLED
        printf("\nExiting BUILD_MAX_HEAP \n");
    #endif
}

/*
void MIN_HEAPSORT (heapNode *A, int len)
{
    #ifdef DEBUG_ENABLED
        printf("\nEntering MIN_HEAPSORT \n");
    #endif

    BUILD_MIN_HEAP(A, len);
    for ( int i = len-1; i>=0; i--)
    { 
        #ifdef DEBUG_ENABLED
            printf ("Calling swap from MIN_HEAPSORT\n ");
            printf("Pointer to (A) = %p (A+i)= %p \n", (A), (A+i));       
        #endif

        swap( (A->root_element), ((A+i)->root_element), (A->root_index), ((A+i)->root_index));
//      swap_FP(((A)->root_index),((A+i)->root_index));
        len = len -1;
         
        MIN_HEAPIFY (A, 0, len);
    }

    #ifdef DEBUG_ENABLED
        printf("\nExiting MIN_HEAPSORT \n");
        DISPLAY_HEAP(A, len);
    #endif
}

*/

void MAX_HEAPSORT (heapNode *A, int len)
{
    #ifdef DEBUG_ENABLED
        printf("\nEntering MAX_HEAPSORT \n");
    #endif
    
    BUILD_MAX_HEAP(A, len);
    for ( int i = len-1; i>=0; i--)
    { 
        #ifdef DEBUG_ENABLED
            printf ("Calling swap from MAX_HEAPSORT\n ");
            printf("Pointer to (A) = %p (A+i)= %p \n", (A), (A+i));       
        #endif

        swap( (A->root_element), ((A+i)->root_element), &(A[0].root_index), &((A[0]).root_index));
//      swap(((A)->root_element),((A+i)->root_element));
//      swap_FP(((A)->root_index),((A+i)->root_index));

        len = len -1;
         
        MAX_HEAPIFY (A, 0, len);
    }

    #ifdef DEBUG_ENABLED
        printf("\nExiting MAX_HEAPSORT \n");
        DISPLAY_HEAP(A, len);
    #endif
}
/*
void SORT_HEAP_AND_WRITE_OUTPUT (heapNode *A, FILE *fp_out, int total_chunks, int max_floats)
{
    for (int i=0;i<max_floats;i++)
    {
        
        // Build max-heap returns the highest element in  
        //BUILD_MAX_HEAP(A, total_chunks);
        
        MAX_HEAPSORT(A, total_chunks);

        int j = total_chunks-1;

        // Build min-heap returns the highest element in  
        //BUILD_MIN_HEAP(Node_list, total_chunks);
    
        //Display Heap
        //DISPLAY_HEAP(A, total_chunks);
    
        //After Build Heap has returned, the first location of A ( i.e Node_list) has the hightest value
        // We start writing the highest value in the output file ( this will contain merge result of all sorted chunks )    

        //for(j=0;j<num_of_floats_read;++j)
        fprintf(fp_out,"%f\n",*((A+j)->root_element));

        //Reading the next floating point number to replace the max number
        getfloat((A+j)->root_index, (A+j)->root_element);
        if ( feof((A+j)->root_index) )
        {
            fclose((A+j)->root_index);
            total_chunks--;
        }
    }
}*/
        

/*
int main()
{
 
    int total_chunks = CHUNKS ;
    int max_floats_read = TOTAL_FLOATS;
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

    return 0;
   
} */


