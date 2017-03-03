/* Program to merge k-sorted arrays into a single array
 * 02-03-2017
 */

#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 256

typedef struct heapNode{
    int data;
    int arrayNum;
    int itemNum;
} heapNode;

int leftChild (int i){
    return (i*2)+1;
}

int rightChild (int i){
    return (i*2)+2;
}

heapNode * createNode (int data, int arrayNum, int itemNum){
    heapNode * newNode = (heapNode *)malloc(sizeof(heapNode));
    newNode->data = data;
    newNode->arrayNum = arrayNum;
    newNode->itemNum = itemNum;

    return newNode;
}

void swap(heapNode * a[], int i, int len){
    heapNode * temp = a[i];


    int smallest = i;
    int left,right;

    left = leftChild(i);
    right = rightChild(i);

    if (left <= len && a[i]->data > a[left]->data){
        smallest = left;
    }

    if (right <= len && a[smallest]->data >a[right]->data){
        smallest = right;
    }

    if (smallest != i){
        swap(a,i,smallest);
        minHeapify(a,smallest,len);
    }
}

void buildHeap(heapNode *a[], int len){
    int i = len/2 +1;
    for(;i>=0;i++){
        minHeapify(a,i,len);
    }
}



