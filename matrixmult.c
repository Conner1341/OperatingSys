/***************************************************************************
 * name: Conner Herriges
 * course: CS 4328 - Operating Systems
 * project: Project1, part2a
 *    This program uses Pthreads to multiply two matrices, A and B, where matrix A contains M rows and K columns, and matrix B contains K rows and N columns. The product of A and B is another matrix, C.
 * status: complete
 * compile with gcc -g -Wall -lpthread matrixmult.c -o matrix
 **************************************************************************/
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

#define M 3
#define N 3
#define K 2
#define NUM_THREADS 10

int A [M][K] = {{1, 4}, {2, 5}, {3, 6}};
int B [K][N] = {{7, 2, 9}, {4, 8, 1}};
int C [M][N];
void *mult(void *param);

/* data structure to pass matrix data to threads */
struct values {
    int i;  /* row */
    int j;  /* column */
};

int main() {
    int r, s, count;
    pthread_t tid;              /* the thread identifier */
    pthread_t workers[NUM_THREADS];
    pthread_attr_t attr;        /* set of attributes for the thread */

    /* create worker threads */
    for (r = 0; r < M; r++) {
        for (s = 0; s < N; s++) {
            /* allocate sufficient memory */
            struct values *data = (struct values*)malloc(sizeof(struct values));
            data->i = r;
            data->j = s;
            pthread_attr_init(&attr);   /* get the default attributes */

            /* create the thread passing data as a paramter */
            pthread_create(&tid, &attr, mult, data);

            count++;
        }
        /* wait for threads to finish */
        pthread_join(workers[r], NULL);
    }

    /* print out matric C  */
    for (r = 0; r < M; r++) {
        for (s = 0; s < N; s++) {
            printf("%d ", C[r][s]);
        }
        printf("\n");
    }
    return 0;
}

/* worker thread calculates each element Cij */
void *mult(void *param) {
   struct values *data = param;
   int count, sum = 0;

   /* multiply row of A by column of B */
   for(count = 0; count < K; count++){
      sum += A[data->i][count] * B[count][data->j];
   }

   /* assign sum to position ij in matrix C */
   C[data->i][data->j] = sum;

   pthread_exit(0);
}
