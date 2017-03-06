#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*void swap(FILE *fp5, FILE *fp6)
{
    FILE *fp_temp;

    fp_temp = fp5;
    fp5 = fp6;
    fp6 = fp_temp;
}*/

typedef struct heapNode{
        FILE *root_index;              //position of the floating point number in the file
        float *root_element;           //value
} heapNode;

void change_address (heapNode **x, heapNode **y)
{
    printf("\nInside function, p value = %p, p1 value = %p\n",*x,*y);
    
    heapNode *pp;
    pp = (heapNode *)malloc(sizeof(heapNode));
    
    pp = *x;
    *x = *y;
    *y = pp;
    
    printf("\nInside function, p value = %p, p1 value = %p\n",*x,*y);
}

void main()
{
    heapNode *Node_list;

    Node_list = (heapNode*)malloc(sizeof(heapNode)*2);
    Node_list->root_index = (FILE *)malloc(sizeof(FILE));
    Node_list->root_element = (float *)malloc(sizeof(float));


    heapNode *p,*p1;
    p = (heapNode*)malloc(sizeof(heapNode));
    p1 = (heapNode*)malloc(sizeof(heapNode));

    p = &Node_list[0];
    p1 = &Node_list[1];

    printf("\nNode_list address = %p, Node_list[0] address = %p, Node_list[1] = %p\n",&Node_list, &Node_list[0], &Node_list[1]);
    printf("\np value = %p, p1 value = %p\n",p,p1);
    
    printf("\nSwapping address of p & p1\n");
    
    change_address(&p,&p1);

    
    printf("\nNode_list address = %p, Node_list[0] address = %p, Node_list[1] = %p\n",&Node_list, &Node_list[0], &Node_list[1]);
    printf("\np value = %p, p1 value = %p\n",p,p1);
}
