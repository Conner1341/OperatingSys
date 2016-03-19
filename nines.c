#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define LENGTH 200000000

int arr[LENGTH];
int count;
void *nines(void *param);   /* worker thread function */


int main()
{
    int i, rval;
    double start_time, end_time;

    pthread_t workers[NUM_THREADS];
    int threadId[NUM_THREADS];
    pthread_attr_t attr;

    /* intialize random number generator */
    srand((unsigned)time(NULL));

    /* intialize array using random numbers */
    for (i = 0; i < LENGTH; i++)
        arr[i] = rand() % 100;

    /* start the clock */
    start_time = omp_get_wtime();
    /* create worker threads */
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_attr_init(&attr);
        threadId[i] = i;

        pthread_create(&workers[i], &attr, nines, (void *)&threadId[i]);
    }
    for (i = 0; i < NUM_THREADS; i++){
         rval += pthread_join(&workers[i], NULL);
    }
    end_time = omp_get_wtime();
    printf("\n");

    printf("The pthread code indicates that there are %d 99s in the array. \n\n", rval);
    printf("The pthread used %f seconds to complete the execution.\n\n", end_time - start_time);

    return 0;
}


void *nines(void *param) {
    int i, tid, begin, end;
    tid = *(int *)param;

    begin = tid * (LENGTH / NUM_THREADS);
    end = (tid + 1) * (LENGTH / NUM_THREADS) - 1;

    for (i = begin; i < end; i++) {
        if (arr[i] == 99)
            count++;
    }
    pthread_exit(0);
}
