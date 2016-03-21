#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define LENGTH 200000000

int arr[LENGTH];
int count;

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

    #pragma omp parallel for private (count)
    for (i = 0; i < LENGTH; i++) {
        if (arr[i] == 99)
            count++;
    }

    end_time = omp_get_wtime();
    printf("\n");

    printf("The openMP code indicates that there are %d 99s in the array. \n\n", count);
    printf("The openMP used %f seconds to complete the execution.\n\n", end_time - start_time);

    return 0;
}
