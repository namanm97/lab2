/*12. Write a program to Multiply a matrix by a vector and get the result of the //operation. */

#include <stdio.h> 
#include <omp.h> 

/* Main Program */ 
main() 
{ 
int NoofRows, NoofCols, Vectorsize, i, j; 
/*float **Matrix, *Vector, *Result, *Checkoutput;*/ 
double **Matrix, *Vector, *Result, *Checkoutput; 

printf("Read the matrix size noofrows and columns and vectorsize\n"); 
scanf("%d%d%d", &NoofRows, &NoofCols, &Vectorsize); 

if (NoofRows <= 0 || NoofCols <= 0 || Vectorsize <= 0) 
{ 
printf("The Matrix and Vectorsize should be of positive sign\n"); 
exit(1); 
} 

/* Checking For Matrix Vector Computation Necessary Condition */ 
if (NoofCols != Vectorsize) 
{ 
printf("Matrix Vector computation cannot be possible \n"); 
exit(1); 
} 

/* Dynamic Memory Allocation And Initialization Of Matrix Elements */ 
/* Matrix = (float **) malloc(sizeof(float) * NoofRows); */ 

Matrix = (double **) malloc(sizeof(double) * NoofRows); 
for (i = 0; i < NoofRows; i++)
 { 
    /* Matrix[i] = (float *) malloc(sizeof(float) * NoofCols); */ 
    Matrix[i] = (double *) malloc(sizeof(double) * NoofCols); 
    for (j = 0; j < NoofCols; j++) 
      Matrix[i][j] = i + j; 
} 

/* Printing The Matrix */ 
printf("The Matrix is \n"); 
for (i = 0; i < NoofRows; i++)
{ 
  for (j = 0; j < NoofCols; j++) 
  printf("%lf \t", Matrix[i][j]); 
  printf("\n"); 
} 
printf("\n"); 

/* Dynamic Memory Allocation */ 
/*Vector = (float *) malloc(sizeof(float) * Vectorsize);*/ 
Vector = (double *) malloc(sizeof(double) * Vectorsize); 

/* vector Initialization */ 
for (i = 0; i < Vectorsize; i++) 
Vector[i] = i; 
printf("\n"); 

/* Printing The Vector Elements */ 
printf("The Vector is \n"); 
for (i = 0; i < Vectorsize; i++) 
printf("%lf \t", Vector[i]); 

/* Dynamic Memory Allocation */ 
/* Result = (float *) malloc(sizeof(float) * NoofRows); 
Checkoutput = (float *) malloc(sizeof(float) * NoofRows); */ 
Result = (double *) malloc(sizeof(double) * NoofRows); 
Checkoutput = (double *) malloc(sizeof(double) * NoofRows); 
for (i = 0; i < NoofRows; i = i + 1) 
{ 
Result[i]=0; 
Checkoutput[i]=0; 
} 



/* OpenMP Parallel Directive */ 
omp_set_num_threads(32); 
#pragma omp parallel for private(j) 
for (i = 0; i < NoofRows; i = i + 1) 
for (j = 0; j < NoofCols; j = j + 1) 
Result[i] = Result[i] + Matrix[i][j] * Vector[j]; 

/* Serial Computation */ 
for (i = 0; i < NoofRows; i = i + 1) 
for (j = 0; j < NoofCols; j = j + 1) 
Checkoutput[i] = Checkoutput[i] + Matrix[i][j] * Vector[j]; 

/* Checking with the serial calculation */ 
for (i = 0; i < NoofRows; i = i + 1) 
if (Checkoutput[i] == Result[i]) 
continue; 
else 
{ 
printf("There is a difference from Serial and Parallel Computation \n"); 
exit(1); 
} 
printf("\nThe Matrix Computation result is \n"); 
for (i = 0; i < NoofRows; i++) 
printf("%lf \n", Result[i]); 

/* Freeing The Memory Allocations */ 
free(Vector); 
free(Result); 
free(Matrix); 
free(Checkoutput); 
} 

