/***************************************************************************
 * name: Conner Herriges
 * course: CS 4328 - Operating Systems
 * project: Project1, part3b
<<<<<<< HEAD
 *      This program uses pthread to count the number of times '99' appears in a randomly generated array. It also records the execution time of the code.
         The number of threads the program runs on can be changed by changing
             the value of NUM_THREADS
 * status: working
 * compile with gcc -g -Wall -lpthread pNines.c -o nines
 * run with ./nines
=======
 *      This program uses pthread to count the number of times '99' appears in a randomly generated array.
         The number of threads the program runs on can be changed by changing
             the value of NUM_THREADS
 * status: working
>>>>>>> 7135a75900c1c73924b691b409f826b33d4bd2ee
 **************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2
#define LENGTH 200000000

int arr[LENGTH];
int count;
void *nines(void *param);   /* worker thread function */
pthread_mutex_t lock;

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

    /* clean up and exit */
    pthread_attr_destroy(&attr);
<<<<<<< HEAD
    return 0;
=======
    pthread_mutex_destroy(&lock);
    pthread_exit(NULL);
>>>>>>> 7135a75900c1c73924b691b409f826b33d4bd2ee
}


void *nines(void *param) {
    int i, tid, begin, end;
    tid = *(int *)param;

    begin = tid * (LENGTH / NUM_THREADS);
    end = (tid + 1) * (LENGTH / NUM_THREADS) - 1;

    for (i = begin; i < end; i++) {
        if (arr[i] == 99)
            pthread_mutex_lock(&lock);
            count++;
            pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}
