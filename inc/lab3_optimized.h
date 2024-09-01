/**
 * @file lab3_optimized.h
 * 
 * @brief Header file.
 * 
 * @author Robledo, Valentín 
 * @date May 2023
 * @version 1.0
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef __LAB3_OPTIMIZED_H__
#define __LAB3_OPTIMIZED_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define VAR 9.036

__uint16_t XDIM = 10000;
__uint16_t YDIM = 10000;

double **alloc_matrix(void);
void fill(double** arr);
void compute(double** arr, int kern[3][3]);

#endif // __LAB3_OPTIMIZED_H__