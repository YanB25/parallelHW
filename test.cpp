#include <omp.h> 
#include <stdio.h>
#include <stdlib.h>
const int  SIZE = 2000;
double A[SIZE][SIZE]; 
double B[SIZE][SIZE];
double R[SIZE][SIZE];
void init() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            A[i][j] = 2.3 * i + 0.4 * j;
            B[i][j] = 1.2 * i + 0.2 * j;
            R[i][j] = 0;
        }
    }
}

void multiple(int size, int testcase) {
    double start = omp_get_wtime();
    #if defined(cacheOptimize)
    for (int i = 0; i < size; ++i) {
        for (int k = 0; k < size; ++k) {
            for (int j = 0; j < size; ++j) {
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    #elif defined(NoneCacheOptimize)
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    #endif
    printf("%d, 0, %d, %lf\n", testcase, size, omp_get_wtime() - start);
    fflush(stdout);
}
void omp_multiple(int size, int testcase) {
    double start = omp_get_wtime();
    #if defined(cacheOptimize)
    #pragma omp parallel for collapse(3)
    for (int i = 0; i < size; ++i) {
        for (int k = 0; k < size; ++k) {
            for (int j = 0; j < size; ++j) {
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    #elif defined(NoneCacheOptimize)
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    #endif
    printf("%d, 1, %d, %lf\n", testcase, size, omp_get_wtime() - start);
    fflush(stdout);
}
void cache_flash() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            A[i][j] = 2.3 * i + 0.4 * j;
            B[i][j] = 1.2 * i + 0.2 * j;
            R[i][j] = 0;
        }
    }
}
int main() {
    printf("testcase, useOMP(1/0), size, time\n");
    fflush(stdout);
    init();
    for (int i = 0; i < 10; ++i) {
        for (int size = 100; size <= 1000; size +=50) {
            init();
            multiple(size, i);
            init();
            omp_multiple(size, i);
        }
    }
}