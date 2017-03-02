#include<stdio.h>
#include<stdlib.h>
#define INT_MAX 1000
 
typedef struct heapNode{
        int data;     //value
        FILE* position; //position of the floating point number in the file
        //int itemNum;  //index of the next element
} heapNode ;
 
int leftChild(int i){
    return (i*2)+1;
}
int rightChild(int i){
    return (2*i)+2;
}


int createNode( heapNode * newNode, int data, FILE* position){
    heapNode * newNode = (heapNode *)malloc(sizeof(heapNode));
    newNode->data = data;
    newNode->arrayNum = position;
         
    return newNode;
}
/*heapNode * createNode( int data, int arrayNum, int itemNum){
    heapNode * newNode = (heapNode *)malloc(sizeof(heapNode));
    newNode->data = data;
    newNode->arrayNum = arrayNum;
    newNode->itemNum = itemNum;
     
    return newNode;
}*/
 
void swap(heapNode * a[], int i, int j){
    heapNode * temp = a[i];
    a[i] = a[j];
    a[j] = temp;    
}
 
void minHeapify(heapNode * a[], int i, int len){
    int smallest =i;
    int left, right;
     
    left = leftChild(i);
    right = rightChild(i);
     
    if(left <= len && a[i]->data > a[left]->data){
        smallest = left;
    }
    if(right <= len && a[smallest]->data > a[right]->data){
        smallest = right;
    }
    if(smallest != i){
        swap(a, i, smallest);
        minHeapify(a, smallest, len);
    }
}
 
void buildHeap(heapNode *a[], int len){
    int i = len/2 +1;
    for(; i>=0; i--){
        minHeapify(a,i, len);
    }
}
