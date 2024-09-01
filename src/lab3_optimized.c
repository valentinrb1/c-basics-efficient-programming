/**
 * @file lab3_optimized.c
 * 
 * @brief Source file.
 * 
 * @author Robledo, Valentín 
 * @date May 2023
 * @version 1.0
 * 
 * @copyright Copyright (c) 2023
 */

#include "../inc/lab3_optimized.h"

// We return the pointer
double **alloc_matrix(void) /* Allocate the array */
{
    /* Check if allocation succeeded. (check for NULL pointer) */
    int i, j, k; 
    double **array;
    array = malloc((size_t)XDIM*sizeof(double *));
    for(i = 0 ; i < XDIM ; i++)
        array[i] = malloc((size_t)YDIM*sizeof(double) );
  
    for(j=0; j<XDIM; j++)
        for(k=0; k<YDIM; k++)
            memset(&array[k][j], j, sizeof(double));
    return array;
}

void fill(double** arr) {
    /* fill the array with random values */
    int i, j;
    time_t t1; 
    srand ( (unsigned) time (&t1));
    for(i = 0 ; i < XDIM ; i++)
        for(j = 0 ; j < YDIM ; j++)
            arr[i][j] = (double)(rand() % 100);
}

void compute(double** arr, int kern[3][3])
{
    register __int16_t i, j;
    double accum;

    for(i = 0 ; i < XDIM-2 ; i++){
        for(j = 0 ; j < YDIM-2 ; j++){
            accum = 0;
            
            accum += kern[0][0] * arr[i+0][j+0];
            accum += kern[0][1] * arr[i+0][j+1];
            accum += kern[0][2] * arr[i+0][j+2];
            accum += kern[1][0] * arr[i+1][j+0];
            accum += kern[1][1] * arr[i+1][j+1];
            accum += kern[1][2] * arr[i+1][j+2];
            accum += kern[2][0] * arr[i+2][j+0];
            accum += kern[2][1] * arr[i+2][j+1];
            accum += kern[2][2] * arr[i+2][j+2];

            accum *= VAR;
            
            arr[i][j] = accum;
        }
    }
}

int main(void)
{
    double **arr;
    int kern[3][3] = {{0, -1, 0},
                      {-1, 5, -1},
                      {0, -1, 0}};
    arr = alloc_matrix();
    fill(arr);
    compute(arr, kern);

    return 0;
}