#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define LENGTH 200000000

int arr[LENGTH];
int count = 0;

int main() {
    int i;
    double start_time, end_time;
    omp_lock_t lock;
    omp_init_lock(&lock);

    /* intialize random number generator */
    srand((unsigned)time(NULL));

    /* intialize array using random numbers */
    for (i = 0; i < LENGTH; i++)
        arr[i] = rand() % 100;

    /* set the number of threads */
    omp_set_num_threads(16);

    /* start the clock */
    start_time = omp_get_wtime();

    #pragma omp parallel for shared(arr) private(count)
    for (i = 0; i < LENGTH; i++) {
        if (arr[i] == 99)
            omp_set_lock(&lock);
            count++;
            omp_unset_lock(&lock);
    }
    end_time = omp_get_wtime();
    printf("\n");

    printf("The openMP code indicates that there are %d 99s in the array. \n\n", count);
    printf("The openMP used %f seconds to complete the execution.\n\n", end_time - start_time);

    omp_destroy_lock(&lock);
    return 0;
}
