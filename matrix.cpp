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
    printf("%d, 0, %d, %lf, 1\n", testcase, size, omp_get_wtime() - start);
    fflush(stdout);
}
void omp_multiple(int size, int testcase, int tn) {
    double start = omp_get_wtime();
    #if defined(cacheOptimize)
    omp_set_dynamic(0);     // Explicitly disable dynamic teams
    omp_set_num_threads(tn);
    #pragma omp parallel 
    {
        #pragma omp for collapse(1)
        for (int i = 0; i < size; ++i) {
            for (int k = 0; k < size; ++k) {
                for (int j = 0; j < size; ++j) {
                    R[i][j] += A[i][k] * B[k][j];
                }
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
    printf("%d, 1, %d, %lf, %d\n", testcase, size, omp_get_wtime() - start, tn);
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
    printf("testcase, useOMP(1/0), size, time, treadsnum\n");
    fflush(stdout);
    init();
    // for (int i = 0; i < 20; ++i) {
    //     init();
    //     multiple(50, i);
    //     init();
    //     omp_multiple(50, i);
    // }
    for (int t = 0; t <= 10; ++t) {
        for (int i = 1; i <= 8; i++) {
            init();
            omp_multiple(200, t, i);
            init();
            multiple(200, t);
        }
    }
}