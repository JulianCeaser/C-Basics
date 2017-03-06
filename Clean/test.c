#include <assert.h>
#include <stdio.h>

void swap(FILE *fp5, FILE *fp6)
{
    FILE *fp_temp;

    fp_temp = fp5;
    fp5 = fp6;
    fp6 = fp_temp;
}

void main()
{
    FILE *fp1,*fp2;
    FILE *fp3,*fp4;
    fp1 = fopen("a","w");
    fp2 = fopen("b","w");

    fprintf(fp1,"\n1.fp1 (fp3=fp1)");
    fp3 = fp1;
    fprintf(fp3,"\n1.fp3 (fp3=fp1)");    
    :wqfp1 = fp2;
    fprintf(fp1,"\n2.fp1 (fp1=fp2)");
    fprintf(fp2,"\n2.fp2 (fp1=fp2)");    
    fp2 = fp3;
    fprintf(fp2,"\n3.fp2 (fp2=fp3)");
    fprintf(fp3,"\n3.fp3 (fp2=fp3)");    

//    swap(*fp3,*fp4); 
    
/*    printf("\nSwap fp3 and fp4");
    printf("\nAddress of fp1 = %p, Address of fp2 = %p",&fp1,&fp2);
    printf("\nValue of fp3 = %p, Value of fp4 = %p\n",*fp3,*fp4); */

    fclose(fp1);
    fclose(fp2);
}
