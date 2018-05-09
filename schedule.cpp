#include <omp.h> 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void dummy(double sec) {
    clock_t start = clock();
    while ((clock() - start) / CLOCKS_PER_SEC <= sec);
    return;
}
int main() {
    printf("schedule, loop, time\n");
    for (int TIMES = 1; TIMES <= 20; ++TIMES) {
        double start = omp_get_wtime();
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < TIMES; ++i) {
            dummy(i);
        }
        printf("static, %d, %lf\n", TIMES, omp_get_wtime() - start);
        fflush(stdout);
        start = omp_get_wtime();
        #pragma omp parallel for schedule(guided)
        for (int i = 0; i < TIMES; ++i) {
            dummy(i);
        }
        printf("guided, %d, %lf\n", TIMES, omp_get_wtime() - start);
        fflush(stdout);
        start = omp_get_wtime();
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < TIMES; ++i) {
            dummy(i);
        }
        printf("dynamic, %d, %lf\n", TIMES, omp_get_wtime() - start);
        fflush(stdout);
    }
}