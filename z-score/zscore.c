 /**
 *  Compute Z-score and sort a textfile of numbers
 *  Sorting is done by Merge sorting
 **/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


 
//************************************************************
// merge() 
// Merge two sorted arrays, A with a  integers and 
// B with b integers, into a sorted array C.
//*************************************************************
void merge (float *A, int a, float *B, int b, float *C) 
{
  int i,j,k;
  i = 0; 
  j = 0;
  k = 0;
  while (i < a && j < b) {
    if (A[i] <= B[j]) {
	  C[k] = A[i];
	  i++;
	  k++;
    }
    else {
      C[k] = B[j];
      j++;
      k++;
    }
  }
  while (i < a) {
    C[k]= A[i];
    i++;
    k++;
  }
  while (j < b)  {
    C[k]= B[j];
    j++;
    k++;
  }
}  

//************************************************************
// merge_sort()
// Sort array A with n integers, using merge-sort algorithm.
////************************************************************
void merge_sort(float *A, int n) 
{
  int i;
  float *A1, *A2;
  int n1, n2;

  if (n < 2)
    return;   
  
  
  n1 = n / 2;  
  n2 = n - n1;  
  A1 = (float*)malloc(sizeof(float) * n1);
  A2 = (float*)malloc(sizeof(float) * n2);
  
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

//******************************
//Compute Mean
//******************************

double compute_mean(float *A,int n)
{
  double mean=0.0;
  int i;
  
  //Loop to compute mean
  
  for (i=0;i<n;i++)
    mean = mean + (A[i] / n);
  
  return(mean);
}

//***********************************
//Compute Sample Variance
//***********************************

double compute_sample_var(double mean,float *A, int n)
{
  double sample_var = 0.0;
  int i;
  
  for (i=0;i<n;i++)
    sample_var = sample_var + pow((A[i] - mean), 2.0) / ( n - 1);
  
  return (sample_var);
}

//***************************************
// Main Function
//***************************************

void main(int argc, char** argv)
{
	int i=0, n=10;
  float num;
  double mean,sample_variance,standard_deviation;
	float *A = (float *)malloc(sizeof(float) * n);
  float *Z = (float *)malloc(sizeof(float)* n);
	//char *c;
  FILE *f;

  if (argc >= 2)
  {
    f = fopen(argv[1], "r");
    if (f == NULL)
    {
      printf("\nInvalid filename entered! Please correct and try again.\n");
      exit(0);
    }
  }
  else
  {
     printf("\nPlease enter the filename where the numbers are written in comma-delimited fashion.\n");
    exit(0);
  }
  
  //printf("\nargv[1] = %s\n",argv[1]);
  //f = fopen(argv[1], "r");
    
    
	while( i < n)
  {
     fscanf(f, "%f,", &num);
    A[i++] = num;
  }
  fclose(f);
  
  //Compute mean, sample variance for the array
  mean = compute_mean(A,n);
  sample_variance = compute_sample_var(mean,A,n); 
  standard_deviation = sqrt (sample_variance); // Standard Deviation is square root of Sample Variance
  //printf("mean = %lf, sample_variance = %lf\n",mean,sample_variance);
  
  //Calculate Z-scores for the sample
  for (i=0;i<n;++i)
    Z[i] = (A[i] - mean) / standard_deviation;
  

	/* print the original array */
	printf("************** Result **************\n");
  printf("The input array is: ");
  for (i = 0; i < n; i++) {
    printf("%.2f ", A[i]);
  }
  printf("\n");
  
  // print z-scores
  printf("The Z-score array is: ");
  for (i = 0; i < n; i++) {
    printf("%.2f ", Z[i]);
  }  
  printf("\n");

  /* merge sort A */
  merge_sort(A, n);

  /* print the sorted array */
  printf("The sorted array is: ");
  for (i = 0; i < n; i++) {
    printf("%.2f ", A[i]);
  }
  printf("\n");
  
 free(A);  
} 