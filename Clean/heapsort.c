#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "getfloat.h"

#define INT_MAX 1000
#define MAX_FLOATS_READ_IN_HEAP 250
#define FIRST_RUN   1


int TEST_FLAG = 1;

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

void minHeapify (heapNode *A, int index, int len)
{
    int i = index;

    heapNode *smallest,*left,*right;
    if (TEST_FLAG) 
    {
        for (int i = 1; i <= len; i++){
            printf("A[%d] contains pointer  = %p\n", i,(A+i-1));
            printf("Inside A[%d] - root_index is  = %p\n",i, ((A+i-1))->root_index);;
            printf("Inside A[%d] - root_element is  = %f\n",i, *((A+i-1)->root_element));

        } 
    
    }

    smallest = (heapNode*)malloc(sizeof(heapNode));
    left = (heapNode *)malloc(sizeof(heapNode));
    right = (heapNode *)malloc(sizeof(heapNode));

    smallest->root_index = (FILE *)malloc(sizeof(FILE));
    smallest->root_element = (float *)malloc(sizeof(float));
     
    smallest->root_index = (A+i)->root_index;

    smallest->root_element =(A+i)->root_element;
     
    if (TEST_FLAG) 
    {
        printf("\nSize allocated for Smallest = %d\n",sizeof(smallest));
        printf("\nSize allocated for left = %d\n",sizeof(left));
        printf("\nSize allocated for right = %d\n",sizeof(right));
        printf("A[%d]>root_index = %p\n",i, smallest->root_index);
        printf("smallest->root_index = %p\n",smallest->root_index);
    } 

    //left = leftChild(i);
    //right = rightChild(i);
    left->root_index = (FILE *)malloc(sizeof(FILE));


    left->root_index = (FILE *)malloc(sizeof(FILE));
    right->root_element = (float *)malloc(sizeof(float));
    right->root_element = (float *)malloc(sizeof(float));
    
    left->root_index = (A+(2*i))->root_index;
    left->root_element =(A+(2*i))->root_element;
    right->root_index = (A+(2*i+1))->root_index;
    right->root_element =(A+(2*i+1))->root_element;
     
    
    printf("\nContext :left index[2*i] = %d, element at left index = %f, file pointer = %p\n",
                            (2*i), // index at 2xi
                            *(left->root_element), 
                            (left->root_index));


    printf("\nContext :right index[2*i+1] = %d, element at right index = %f, file pointer = %p\n",
                            (2*i+1),
                            *(right->root_element),
                            (right->root_index));


    /* Applying Cormen's Algorithm but adjusted for Smallest instead of largest */

    int l, r, smallest_index ;
    l = LEFT(i);
    r = RIGHT(i);
    smallest_index = i;
    
    if ((l <= len ) && (*((A+l)->root_element) < *((A+i)->root_element)))
          smallest_index = l;
    else
         smallest_index = i;

    if ((r<= len) && (*((A+r)->root_element) < *((A+smallest_index)->root_element)))
        smallest_index= r;
    if (smallest_index != i )
    {
        printf("\nBefore swap  A[%d] = %f, A[%d] = %f \n",i, smallest_index, *((A+i)->root_element), *((A+smallest_index)->root_element));
        //void swap ( int *px, int *py)
        swap ((A+i)->root_element, (A+smallest_index)->root_element);
        printf("\nAfter swap  A[%d] = %f, A[%d] = %f \n",i, smallest_index, *((A+i)->root_element), *((A+smallest_index)->root_element));
        minHeapify (A, i, len);

    } 
    
    printf("Inside A[%d] - root_index for min element is  = %p\n",i, ((A+i-1))->root_index);;
    printf("Inside A[%d] - Value of min_element is  = %f\n",i, *((A+i-1)->root_element));

    //lets print the Array A across index 1 to len and see value of each element
    if (TEST_FLAG) 
    {
        printf ("Printing Sorted Heap\n"); 
        for (int i = 1; i <= len; i++){
            printf("A[%d] contains pointer  = %p\n", i,(A+i-1));
            printf("Inside A[%d] - root_index is  = %p\n",i, ((A+i-1))->root_index);;
            printf("Inside A[%d] - root_element is  = %f\n",i, *((A+i-1)->root_element));

        } 
    
    }
    

  /*  //if(left <= len && A[i]->data > A[left]->data)
    if(2*i <= len && (A+i)->root_element > left->root_element)
    {        
        smallest = left;
    }
    if(right <= len && a[smallest]->data > a[right]->data){
        smallest = right;
    }
    if(smallest != i){
        swap(a, i, smallest);
        minHeapify(a, smallest, len);
    }*/
}



int PARENT (int i)
{
    return (i/2);
}

int LEFT ( int i)
{
    return 2*i;
}
int RIGHT ( int i)
{
    return (2*i+1);
}    


void swap ( int *px, int *py)
{
    int tmp;
    tmp = *px;
    *px = *py;
    *py = tmp;


} 
 /*
void buildHeap(heapNode *a[], int len){
    int i = len/2 +1;
    for(; i>=0; i--){
        minHeapify(a,i, len);
    }
}
*/
/*
// Merge the K-Sorted Arrays using HeapSort algorithm

//void mergeKSortedArrays(int *a, int N, int K, int result[]){
void mergeKSortedArrays(heapNode *input_node_list, int max_no_of_element_per_chunk, int no_of_chunks, FILE *final_output_file){
   
   
   
    // n = max_no_of_element_per_chunk, k = no_of_chunks){
    int i;
   //heapNode *minHeap[K];
   // Put all elements in an array //
   for(i=0;i<K; i++){
       minHeap[i] = createNode(a[i][0], i, 0);
   }
 
   // Build min heap with those entered elements //
   //buildHeap(minHeap,K-1);

    //Heapify
         
   // Now we have to take every element one by one and replace 
   // root with that and heapify again 
   for(i=0; i<N*K; i++){
      heapNode * minNode = minHeap[0];
                                         
      // Put the root of min heap in result array //
      result[i] = minNode->data;
      // If there are elements to be considered in that array //
        if(minNode->itemNum + 1< N){
            minHeap[0] = createNode(
                                    a[minNode->arrayNum][minNode->itemNum + 1],
                                    minNode->arrayNum, minNode->itemNum + 1
                              );
        }       
        // else put INT_MAX at root //
        else{
            minHeap[0] = createNode(INT_MAX, minNode->arrayNum, 
                         minNode->itemNum + 1);
        }
        // Heapify again 
         minHeapify(minHeap, 0, K-1);
   }       
}*/
/*
void HeapSort(int max_no_of_chunks, heapNode *input_node_list, FILE *final_output_file)
{
    
}
*/

int main(){
 
    int total_chunks = 4, max_floats_read = MAX_FLOATS_READ_IN_HEAP;
    char *filename_chunk;
    FILE *fp_list; //List of file pointer
    FILE **fp_array;

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

        printf("\n Calling Heapify\n");
        printf("\nNode_list pointer at index 1 = %p\n",(Node_list+1));
    }
    

    minHeapify (Node_list, FIRST_RUN, total_chunks);
    

    //float x = 5;

    //for(int i=0;i<run_size;++i){
        
        //Nodelist[0].root_element = x+(30);
    //    Nodelist->root_element = x+(30*i);
    //    printf("\n%f",Nodelist->root_element);
    //    Nodelist++;
   // }

    /*
    int N = 5;
    int K = 4;
    int a[4][5] = { 
            2,3,5,6,7,
                    4,7,8,9,10,
                    3,5,11,13,45,
                    1,4,5,7,8
                  };
 
   int result[K*N];
   mergeKSortedArrays(a, N, K, result);          
 
   for(int i=0; i<N*K; i++){
       printf("%d  ", result[i]);
   }
   */ 
   return 0;
   
}

