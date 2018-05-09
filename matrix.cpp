#include <omp.h> 
#include <stdio.h>
#include <stdlib.h>
const int  SIZE = 2000;
#define LOOPTIME 2000
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
    for(int lp=0; lp < LOOPTIME; ++lp) {
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
    }
    printf("%d, 0, %lf, 1, 0\n", testcase, (omp_get_wtime() - start)/LOOPTIME);
    fflush(stdout);
}
void omp_multiple1(int size, int testcase, int tn) {
    double start = omp_get_wtime();
    for(int lp=0; lp<LOOPTIME; ++lp){
    #if defined(cacheOptimize)
    //omp_set_dynamic(0);     // Explicitly disable dynamic teams
    omp_set_num_threads(tn);
    #pragma omp parallel
    {
        #pragma omp for collapse(1) schedule(dynamic)
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
    }
    printf("%d, 1, %lf, %d, 1\n", testcase, (omp_get_wtime() - start)/LOOPTIME, tn);
    fflush(stdout);
}
void omp_multiple2(int size, int testcase, int tn) {
    double start = omp_get_wtime();
    for (int lp=0; lp<LOOPTIME; ++lp){
    #if defined(cacheOptimize)
    //omp_set_dynamic(0);     // Explicitly disable dynamic teams
    omp_set_num_threads(tn);
    #pragma omp parallel
    {
        #pragma omp for collapse(2) schedule(dynamic)
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
    }
    printf("%d, 1, %lf, %d, 2\n", testcase, (omp_get_wtime() - start)/LOOPTIME, tn);
    fflush(stdout);
}
void omp_multiple3(int size, int testcase, int tn) {
    double start = omp_get_wtime();
    for (int lp = 0; lp < LOOPTIME; ++lp) {
    #if defined(cacheOptimize)
    // omp_set_dynamic(0);     // Explicitly disable dynamic teams
    omp_set_num_threads(tn);
    #pragma omp parallel
    {
        #pragma omp for collapse(3) schedule(dynamic)
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
    }
    printf("%d, 1, %lf, %d, %d\n", testcase, (omp_get_wtime() - start)/LOOPTIME, tn, 3);
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
    printf("testcase, useOMP(1/0), time, threadsnum, collapse\n");
    fflush(stdout);
    init();
    // for (int i = 0; i < 20; ++i) {
    //     init();
    //     multiple(50, i);
    //     init();
    //     omp_multiple(50, i);
    // }
    init();
    multiple(50, 0);
    for (int i = 1; i <= 128; i++) {
        init();
        omp_multiple1(50, 0, i);
        omp_multiple2(50, 0, i);
        omp_multiple3(50, 0, i);
    }
}
