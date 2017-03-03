#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "getfloat.h"

#define INT_MAX 1000
#define MAX_FLOATS_READ_IN_HEAP 250

/*
typedef struct heapNode{
        int data;
        int arrayNum;
        int itemNum;
} heapNode ;
*/

typedef struct heapNode{
        float *root_element;          //value
        FILE* root_index;            //position of the floating point number in the file
} heapNode ;
 
int leftChild(int i){
    return (i*2)+1;
}
int rightChild(int i){
    return (2*i)+2;
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


/*void sortedNode( heapNode * newNode){
    heapNode * newNode = (heapNode *)malloc(sizeof(heapNode));         
}*/

/*heapNode * createNode( int data, int arrayNum, int itemNum){
    heapNode * newNode = (heapNode *)malloc(sizeof(heapNode));
    newNode->data = data;
    newNode->arrayNum = arrayNum;
    newNode->itemNum = itemNum;
     
    return newNode;
}*/
 /*
void swap(heapNode * a[], int i, int j){
    heapNode * temp = a[i];
    a[i] = a[j];
    a[j] = temp;    
}*/

// len = no_of_chunks,
// A = array_of_elements (Node_list->root_element)
// i = index of current smallest element
/*
void minHeapify (heapNode *A, FILE *i, int len)
{
    //int smallest = i;
    FILE *smallest = A->root_index;
    FILE *left, *right;
     
    //left = leftChild(i);
    //right = rightChild(i);
    left = 2 * ;
     
    if(left <= len && A[i]->data > A[left]->data)
    {        
        smallest = left;
    }
    if(right <= len && a[smallest]->data > a[right]->data){
        smallest = right;
    }
    if(smallest != i){
        swap(a, i, smallest);
        minHeapify(a, smallest, len);
    }
}*/

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
    
    Node_list = (heapNode*)malloc(sizeof(heapNode)*total_chunks);
    Node_list->root_index = (FILE *)malloc(sizeof(FILE));
    Node_list->root_element = (float *)malloc(sizeof(float));

    fp_list = (FILE *)malloc(sizeof(FILE)*total_chunks);
    fp_array = (FILE **)malloc(sizeof(FILE *)*total_chunks);
    filename_chunk = (char *)malloc(sizeof(char*));

    //printf("Size of Nodelist = %d",sizeof(Node_list));
    
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
        //    printf("\nroot_element = %f, Node_list pointer = %p\n",*(Node_list->root_element),Node_list);
        
        fp_list++;
        Node_list++;        
    }

    //First pass of 1 element per chunk sent to Heapify
    
    
 //   printf("\nNode_list pointer = %p,root_index = %p, total_chunks = %d\n",Node_list,Node_list->root_index,total_chunks);

//    minHeapify (Node_list, Node_list->root_index, total_chunks);
    

    //void minHeapify (heapNode *A, FILE *i, int len)
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

