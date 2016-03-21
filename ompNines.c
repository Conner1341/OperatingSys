#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 8
#define LENGTH 200000000

int arr[LENGTH];
int count = 0;
int nines(void *param);

int main() {
    int i;
    double start_time, end_time;

    /* intialize random number generator */
    srand((unsigned)time(NULL));

    /* intialize array using random numbers */
    for (i = 0; i < LENGTH; i++)
        arr[i] = rand() % 100;

    /* start the clock */
    start_time = omp_get_wtime();
    count = nines(arr);
    end_time = omp_get_wtime();

    printf("\n");
    printf("The openMP code indicates that there are %d 99s in the array. \n\n", count);
    printf("The openMP used %f seconds to complete the execution.\n\n", end_time - start_time);

    return 0;
}

int nines(void *param) {
    omp_set_num_threads(NUM_THREADS);
    int tid = omp_get_thread_num();
    int num_threads = omp_get_num_threads();
    int begin= tid * (LENGTH / num_threads);
    int end = (tid + 1) * (LENGTH / num_threads) - 1;
    int i, cnt;

    #pragma omp parallel for shared(arr) private(count)
    for (i = begin; i < end; i++) {
        if (arr[i] == 99)
            cnt++;
    }
    return cnt;
}
