# Introduction to efficient and performant programming

## Date - 2023

The program implements a convolution operation on a two-dimensional array of size XDIMxYDIM, where a 3x3 convolution filter defined by the kern integer array is applied. The matrix is ​​created using the alloc_matrix() function, which reserves the necessary memory and initializes it with consecutive values. After this, the fill() function is used to fill the matrix with random values ​​between 0 and 99 and then, with the compute() function, the convolution filter is applied to each pixel of the matrix. Finally, using the print() function, the final values ​​of the matrix are printed after applying the convolution filter.

### Authors:
- **Robledo, Valentín**

## Abstract
In this work, a C code was optimized. Tools such as `time` and `valgrind` were used to measure the execution time and to observe which functions take the most time. Then, modifications were made to the code and finally, the execution time of the original program was compared with the optimized program.

## ¿Cómo clonar este repositorio?
Puede clonar este repositorio en el directorio que desee utilizando el siguiente comando:

```console
git clone https://github.com/valentinrb1/c-basics-efficient-programming.git
```

## How to use?
First, we move to the project folder.

```console
cd c-basics-efficient-programming
```

Inside the project directory we are going to create a folder called *build*.

```console
mkdir build
```

We move to that folder.
```console
cd build
```

We run the *cmake* command inside the *build* folder.
```console
cmake ..
```

We run the *make* command, to obtain the binary files that are saved inside the *bin* directory.
```console
make
```

To run both codes and be able to compare the execution time.
```console
time ./bin/lab3
time ./bin/lab3_optimized
```

---
## Operation

### 1. Code analysis

First, the `time` command was used to measure the execution time of the original program.

```console
time ./bin/lab3
```

The following results were observed:

```console
real 0m0.050s
user 0m0.007s
sys  0m0.024s
```

Later, `valgrind` was used with the `callgrind` tool to observe which functions consume the most execution time.

```console
valgrind --tool=callgrind ./bin/lab3

callgrind_annotate --auto=yes callgrind.out.<ID>
```
We can see the output of this command:

```console
        2 ( 0.00%)      arr = alloc_matrix();
  382,456 ( 0.67%)  => /home/valentinrb/SO2/2023---soii---laboratorio-iii-valentinrb/src/laboratorio3.c:alloc_matrix 
        3 ( 0.00%)      fill(arr);
  886,520 ( 1.55%)  => /home/valentinrb/SO2/2023---soii---laboratorio-iii-valentinrb/src/laboratorio3.c:fill (1x)
        5 ( 0.00%)      compute(arr, kern);
20,029,843 (34.91%)  => /home/valentinrb/SO2/2023---soii---laboratorio-iii-valentinrb/src/laboratorio3.c:compute (1x)
        3 ( 0.00%)      print(arr);
35,921,183 (62.61%)  => /home/valentinrb/SO2/2023---soii---laboratorio-iii-valentinrb/src/laboratorio3.c:print (1x)
```
It was observed that the program spent 62.61% of its time in the `print()` function. Then, 34.91% in the `compute()` function where 85.24% of this function was consumed by the `printf()` functions and finally, 1.55% in the `fill()` function and another 0.67% in the `alloc_matrix()` function.

### 2. Code optimization, first modifications
Since the majority of time is consumed by simply displaying what is happening on the screen, it was decided to eliminate the printing functions.

The `time` command was used again to measure the execution time of the modified program.

```console
real 0m0,001s
user 0m0,001s
sys  0m0,000s
```
It was observed that by eliminating the `print()` function and removing the `printf()` from the `compute()` function, the execution time was reduced from 0.050s to 0.001s.

Again, `valgrind` was used to observe that the `compute()` function consumes 82.61% of the execution time.

### 3. Code optimization, second modification
To continue the optimization, the variables XDIM and YDIM were defined with a larger value. This allowed a better view of the program execution time. In addition, the data type was changed from `int` to `uint16_t` to save memory.

```c
__uint16_t XDIM = 10000;
__uint16_t YDIM = 10000;
```
Using `time`.

```console
real	0m8,156s
user	0m7,980s
sys	0m0,176s
```
As mentioned above, the `compute()` function consumes 82.61% of the execution time. Therefore, the optimization approach was carried out on this function.

- First: the variables `tmp_sum[9]`, `dato`, `k` and `l` were removed, this is because as a consequence of the modifications made to the code, they were no longer necessary.

- Second: the `if` condition was removed by modifying the `for` loops.

Original code:
```c
for(i = 0; i < XDIM; i++)
    for(j = 0; j < YDIM; j++)
        if(i >= 1 && j >=1 && i < XDIM-1 && j <YDIM-1)
```

Modified code:
```c
for(i = 0 ; i < XDIM-2 ; i++){
    for(j = 0 ; j < YDIM-2 ; j++){
```

- Third: The double inner loop iterated 9 times, unnecessary operations were performed inside this loop, therefore, it was decided to eliminate it and simply write 9 times the operation that was performed in the inner loop. In addition, the operation was simplified by removing the constant values ​​from it, defining a variable `VAR`.

Original code:
```c
for(k = 0; k < 3; k++){
    for(l = 0; l < 3; l++){
        int x = i + (l-1);
        int y = j + (k-1);
        dato = arr[x][y];
        tmp_sum[l*3+k] = 2*(2*kern[l][k]*dato)/1000 + 1;
    }

    accum = 0;
    for(k = 0; k < 3; k++)
        for(l = 0; l < 3; l++)
            accum = accum + tmp_sum[k*3+l];
}

arr[i][j] = accum;
```

Modified code:
```c
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
```

Furthermore, the iterators *i, j* were defined as variables of type *register* since variables stored in registers can be accessed much faster than variables stored in memory.

Finally, the compute() function looks like this:
```c
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
```

### Results
Once the modifications were made, the `time` command was used again to compare the execution time of the optimized program with the original program. The comparison was made by also removing the print() and printf() functions from the original code.

Original program:
```console
real	0m8,309s
user	0m8,133s
sys     0m0,176s
```

Optimized program:
```console
real	0m3,952s
user	0m3,736s
sys     0m0,216s
```

It can be observed that the execution time of the original program is 8.309s while the execution time of the optimized program is 3.952s. Therefore, the execution time was reduced by 52.4%.
