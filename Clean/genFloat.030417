#include <stdio.h>
#include <stdlib.h>
#include <time.h>

# define MAX_FLOATS 1000 



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





/* Generate Floating number */
 
int main(int argc, char *argv[])
{
    // No. of Partitions of input file.

//    printf("Usage : -m <maxsize of floats>\n");
//    printf("argc=%d", argc); 
    char input_file[] = "input.txt";
//    char output_file[] = "output.txt";

    FILE* in = openFile(input_file, "w");

    srand((unsigned int)time(NULL));

    // generate input
    for (int i = 0; i < MAX_FLOATS; i++)
    {    
        float r = 1+(float)rand()/(float)RAND_MAX; 
        fprintf(in, "%1f,", r);
    }
    fclose(in);


    return 0;
}

