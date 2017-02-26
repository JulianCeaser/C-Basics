/**
 *  Mergesort.c 
 *  Sort the inputted integers, using merge-sort algorithm.
 **/


#include <stdio.h>
#include <stdlib.h>


/**
 * merge() 
 * Merge two sorted arrays, A with a  integers and 
 * B with b integers, into a sorted array C.
 **/
void 
merge (int *A, int a, int *B, int b, int *C) 
{
  int i,j,k;
  i = 0; 
  j = 0;
  k = 0;
  while (i < a && j < b) {
    if (A[i] <= B[j]) {
	  /* copy A[i] to C[k] and move the pointer i and k forward */
	  C[k] = A[i];
	  i++;
	  k++;
    }
    else {
      /* copy B[j] to C[k] and move the pointer j and k forward */
      C[k] = B[j];
      j++;
      k++;
    }
  }
  /* move the remaining elements in A into C */
  while (i < a) {
    C[k]= A[i];
    i++;
    k++;
  }
  /* move the remaining elements in B into C */
  while (j < b)  {
    C[k]= B[j];
    j++;
    k++;
  }
}  

/**
 * merge_sort()
 * Sort array A with n integers, using merge-sort algorithm.
 **/
void 
merge_sort(int *A, int n) 
{
  int i;
  int *A1, *A2;
  int n1, n2;

  if (n < 2)
    return;   /* the array is sorted when n=1.*/
  
  /* divide A into two array A1 and A2 */
  n1 = n / 2;   /* the number of elements in A1 */
  n2 = n - n1;  /* the number of elements in A2 */
  A1 = (int*)malloc(sizeof(int) * n1);
  A2 = (int*)malloc(sizeof(int) * n2);
  
  /* move the first n/2 elements to A1 */
  for (i =0; i < n1; i++) {
    A1[i] = A[i];
  }
  /* move the rest to A2 */
  for (i = 0; i < n2; i++) {
    A2[i] = A[i+n1];
  }
  /* recursive call */
  merge_sort(A1, n1);
  merge_sort(A2, n2);

  /* conquer */
  merge(A1, n1, A2, n2, A);
  free(A1);
  free(A2);
}

/**
 *  main()
 *  The main function for input and output 
 **/
void
main(int argv, char** args)
{
  int i, n;
  int *A;
  char c;

  printf("Please input the number of elements: " );
  scanf("%d", &n);

  A = (int *)malloc(sizeof(int) * n);
  printf("Please input %d integers: ", n);
  for (i = 0; i < n; i++) {
    scanf("%d", &(A[i]));
  }

  /* print the original array */
  printf("************** Result **************\n");
  printf("The input array is: ");
  for (i = 0; i < n; i++) {
    printf("%d ", A[i]);
  }
  printf("\n");

  /* merge sort A */
  merge_sort(A, n);

  /* print the sorted array */
  printf("The sorted array is: ");
  for (i = 0; i < n; i++) {
    printf("%d ", A[i]);
  }
  printf("\n");
  free(A);  
} 