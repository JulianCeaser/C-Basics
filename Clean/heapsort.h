#ifndef HEAPSORT_H_INCLUDED
#define HEAPSORT_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CHUNKS 4
#define TOTAL_FLOATS 10000

typedef struct heapNode{
         float *root_element;          //value
         FILE* root_index;            //position of the floating point number in the file
 } heapNode ;
 

//typedef struct heapNode heapNode ;


FILE* openFile(char* fileName, char* mode);

int PARENT (int i);

int LEFT ( int i);

int RIGHT ( int i);

void swap ( float *px, float *py);

void swap_FP ( FILE *px, FILE *py);

void DISPLAY_HEAP(heapNode *A, int len);

void MIN_HEAPIFY (heapNode *A, int index, int len);

void MAX_HEAPIFY (heapNode *A, int index, int len);

void BUILD_MIN_HEAP(heapNode *A, int len);

void BUILD_MAX_HEAP(heapNode *A, int len);

void MIN_HEAPSORT (heapNode *A, int len);

void MAX_HEAPSORT (heapNode *A, int len);

void SORT_HEAP_AND_WRITE_OUTPUT (heapNode *A, FILE *fp_out, int total_chunks, int max_floats);
        
#endif
