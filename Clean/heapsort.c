#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "getfloat.h"

#define INT_MAX 1000
#define MAX_FLOATS_READ_IN_HEAP 1000
#define FIRST_RUN   0


int TEST_FLAG = 0;

typedef struct heapNode{
        float *root_element;          //value
        FILE* root_index;            //position of the floating point number in the file
} heapNode ;

int run_flag = FIRST_RUN;

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


 /*
void swap(heapNode * a[], int i, int j){
    heapNode * temp = a[i];
    a[i] = a[j];
    a[j] = temp;    
}*/

// len = no_of_chunks,
// A = array_of_elements (Node_list->root_element)
// i = index of current smallest element


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

void swap ( float *px, float *py)
{
    printf("\nBefore swap x = %f y = %f", *px, *py);
    float tmp;
    tmp = *px;
    *px = *py;
    *py = tmp;
    printf("\nAfter swap x = %f y = %f", *px, *py);

} 

void swap_FP ( FILE *px, FILE *py)
{
    printf("\nBefore swap File Pointer = %p y = %p", px, py);
    FILE *tmp;

    tmp = px;
    px = py;
    py = tmp;
    printf("\nAfter swap File Pointer = %p y = %p", px, py);

} 


/* MIN-HEAPIFY as per Cormen's Algorithm */


void DISPLAY_HEAP(heapNode *A, int len)
{
    printf ("Inside DISPLAY_HEAP\n");
    for (int i = 0; i < len; i++)
    {
        //printf("A[%d] contains pointer  = %p\n", i,(A+i));
        //printf("Inside A[%d] - root_index is  = %p\n",i, ((A+i))->root_index);;
        printf("Inside A[%d] - root_element is  = %f\n",i, *((A+i)->root_element));
     } 
    printf ("Exiting DISPLAY_HEAP\n");

}

void MIN_HEAPIFY (heapNode *A, int index, int len)
{

    printf("\nEntering MIN_HEAPIFY \n ");
    printf("\n Received Params : A = %p index = %d  len = %d\n",A, index, len);
    printf("Inside A[%d] - root_element is  = %f\n",index, *((A+index)->root_element));

    /* Applying Cormen's Algorithm but adjusted for Smallest instead of largest */

    int i = index;
    int l, r, smallest_index ;

    l = LEFT(i);
    r = RIGHT(i);
    smallest_index = i;
    
    printf("LEFT = %d\nRIGHT=%d\n smallest_index=%d Heap size = %d\n", l, r, smallest_index, len);
    if ((l < len ) && (*((A+l)->root_element) < *((A+i)->root_element)))
          smallest_index = l;
    else
         smallest_index = i;

    if ((r< len) && (*((A+r)->root_element) < *((A+smallest_index)->root_element)))
        smallest_index= r;
    if (smallest_index != i )
    {
        printf("\nBefore swap  A[%d] = %f A[%d] = %f \n", i, *((A+i)->root_element), smallest_index, *((A+smallest_index)->root_element));
        
        //void swap ( int *px, int *py)
        swap ((A+i)->root_element, (A+smallest_index)->root_element);
        swap_FP ((A+i)->root_index, (A+smallest_index)->root_index);
        
        printf("\nafter swap  A[%d] = %f A[%d] = %f \n", i, *((A+i)->root_element), smallest_index, *((A+smallest_index)->root_element));
        
        printf ("MIN_HEAPIFY Params : A =%p, smallest_index = %d, len = %d", A, smallest_index,len); 
        MIN_HEAPIFY (A, smallest_index, len);
        //minHeapify (A, smallest_index, len);

    } 

    printf("\nExiting MIN_HEAPIFY \n");
}


void MAX_HEAPIFY (heapNode *A, int index, int len)
{

    printf("\nEntering MAX_HEAPIFY \n ");
    printf("\n Received Params : A = %p index = %d  len = %d\n",A, index, len);
    printf("Inside A[%d] - root_element is  = %f\n",index, *((A+index)->root_element));

    /* Applying Cormen's Algorithm  */

    int i = index;
    int l, r, largest_index ;

    l = LEFT(i);
    r = RIGHT(i);
    largest_index = i;
    
    printf("LEFT = %d\nRIGHT=%d\n largest_index=%d Heap size = %d\n", l, r, largest_index, len);
    if ((l < len ) && (*((A+l)->root_element) > *((A+i)->root_element)))
          largest_index = l;
    else
          largest_index = i;

    if ((r< len) && (*((A+r)->root_element) > *((A+largest_index)->root_element)))
        largest_index= r;
    if (largest_index != i )
    {
        printf("\nBefore swap  A[%d] = %f A[%d] = %f \n", i, *((A+i)->root_element), largest_index, *((A+largest_index)->root_element));
        
        //void swap ( int *px, int *py)
        swap ((A+i)->root_element, (A+largest_index)->root_element);
        swap_FP ((A+i)->root_index, (A+largest_index)->root_index);
        printf("\nAfter swap  A[%d] = %f A[%d] = %f \n", i, *((A+i)->root_element), largest_index, *((A+largest_index)->root_element));
        
        
        printf ("MAX_HEAPIFY Params : A =%p, largest_index = %d, len = %d", A, largest_index,len); 
        MAX_HEAPIFY (A, largest_index, len);

    } 

    printf("\nExiting MAX_HEAPIFY \n");
}




void BUILD_MIN_HEAP(heapNode *A, int len)
{
    printf("\nEntering BUILD_MIN_HEAP \n");
    for ( int i = (len)/2-1; i>=0; i--) { 
        printf ("Calling MIN_HEAPIFY from BUILD_MIN_HEAP\n ");       
        printf ("Calling with Params : index = %d \n ", i);       
        MIN_HEAPIFY (A, i, len);
    } 

    printf("\nExiting BUILD_MIN_HEAP \n");
}


void BUILD_MAX_HEAP(heapNode *A, int len)
{
    printf("\nEntering BUILD_MAX_HEAP \n");
    for ( int i = (len)/2-1; i>=0; i--) { 
        printf ("Calling MAX_HEAPIFY from BUILD_MAX_HEAP\n ");       
        printf ("Calling with Params : index = %d \n ", i);       
        MAX_HEAPIFY (A, i, len);
    } 

    printf("\nExiting BUILD_MAX_HEAP \n");
}


void MIN_HEAPSORT (heapNode *A, int len)
{
    printf("\nEntering MIN_HEAPSORT \n");
    BUILD_MIN_HEAP(A, len);
    for ( int i = len-1; i>=0; i--)
    { 
        printf ("Calling swap from MIN_HEAPSORT\n ");
        printf("Pointer to (A) = %p (A+i)= %p \n", (A), (A+i));       
        swap(((A)->root_element),((A+i)->root_element));
        swap_FP(((A)->root_index),((A+i)->root_index));
        len = len -1;
         
        MIN_HEAPIFY (A, 0, len);
    }

    printf("\nExiting MIN_HEAPSORT \n");
}



void MAX_HEAPSORT (heapNode *A, int len)
{
    printf("\nEntering MAX_HEAPSORT \n");
    BUILD_MAX_HEAP(A, len);
    for ( int i = len-1; i>=0; i--)
    { 
        printf ("Calling swap from MAX_HEAPSORT\n ");
        printf("Pointer to (A) = %p (A+i)= %p \n", (A), (A+i));       
        swap(((A)->root_element),((A+i)->root_element));
        swap_FP(((A)->root_index),((A+i)->root_index));
        len = len -1;
         
        MAX_HEAPIFY (A, 0, len);
    }

    printf("\nExiting MAX_HEAPSORT \n");
}

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

        //manual run    
        getfloat((A+j)->root_index,(A+j)->root_element);
        if ( feof((A+j)->root_index) )
        {
            //perror("Root element is null");
            total_chunks--;
        }
        //else    
            //printf("\nContext : File pointer = %p, Next value = %f\n",(A->root_index),*(A->root_element));

        //BUILD_MAX_HEAP(A, total_chunks);
        //DISPLAY_HEAP(A, total_chunks);
        //fprintf(fp_out,"%f\n ",*(A->root_element));
        }
}
        




 /*
*/

int main(){
 
    int total_chunks = 8, max_floats_read = MAX_FLOATS_READ_IN_HEAP;
    char *filename_chunk;
    FILE *fp_list; //List of file pointer
    FILE **fp_array;

    FILE *fp_output; 
    fp_output = openFile("merged_output.txt","w");

   
    heapNode *Node_list;
    
    //inputNode = (heapNode*)malloc(sizeof(heapNode));
   
    // create a dynamic array containing list of heapNode
    // size of dynamic array is set to total number of external chunks 
    Node_list = (heapNode*)malloc(sizeof(heapNode)*total_chunks);

    // intialize memory for root_index 
    Node_list->root_index = (FILE *)malloc(sizeof(FILE));
    // intialize memory for root_element 
    Node_list->root_element = (float *)malloc(sizeof(float));

    // List to maintain file descriptors for reading each external chunk
    fp_list = (FILE *)malloc(sizeof(FILE)*total_chunks);
    fp_array = (FILE **)malloc(sizeof(FILE *)*total_chunks);

    
    filename_chunk = (char *)malloc(sizeof(char*));

    
    for(int i=1;i<=total_chunks;++i)
    {
        Node_list->root_index = (FILE *)malloc(sizeof(FILE));
        Node_list->root_element = (float *)malloc(sizeof(float));
        
        sprintf(filename_chunk,"temp%d.dat",i);
      //  printf("\nfilename = %s",filename_chunk);
        fp_list = openFile(filename_chunk,"r");
        
        //Storing file pointer index in the Nodelist
        Node_list->root_index = fp_list;
        fp_array[i] = Node_list->root_index;
        

      //  printf("Node_list->root_index = %p",Node_list->root_index); 

    //    memset(Node_list->root_element,'0',sizeof(Node_list)); 
    //    printf("\nmemset succesfull");
        
        //Getfloat takes the filepointer fp and stores the root element into Nodelist->root_element
        //printf("\nfp_list = %p, Node_list->root_element = %p",fp_list,Node_list->root_element);
        getfloat(fp_list,Node_list->root_element);
        if ((Node_list->root_element) == NULL)
            perror("Root element is null");
        else    
        printf("\nContext : %s, fp_array[%d] = %p, root->element = %f\n",filename_chunk,i,fp_array[i],*(Node_list->root_element));
        
        fp_list++;
        Node_list++;        
    }
    


    // Very Important 
    //Now reset the Node_list pointer to the begining of the Node_list
    Node_list = Node_list - total_chunks;

    


    //First pass of 1 element per chunk sent to Heapify
    
    if (TEST_FLAG) 
    {   
        printf("\nNode_list pointer = %p,root_index = %p, total_chunks = %d\n",
                                  Node_list,    Node_list->root_index,  total_chunks);

        //printf("\n Calling Heapify\n");
        printf("\nNode_list pointer at index 0 = %p\n",(Node_list));
        printf("\nNode_list pointer at index 1 = %p\n",(Node_list+1));
    }
    

    // Calling Min-HEAPSORT 
    //MIN_HEAPSORT (Node_list, total_chunks);
    

    // Calling Max-HEAPSORT 
    //MAX_HEAPSORT (Node_list, total_chunks);
   
    SORT_HEAP_AND_WRITE_OUTPUT (Node_list, fp_output, total_chunks, max_floats_read );

    return 0;
   
}

