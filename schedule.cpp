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
    double start = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < 20; ++i) {
        printf("start dummy\n");
        dummy(i);
        printf("end dummy\n");
    }
    printf("wall time %lf\n", omp_get_wtime() - start);
}