/*********************************************************************
 *  This is the serial code provided by the program specifications
 ********************************************************************/

#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    int length = 10000000;
    int count = 0, i, *myArray;
    double start_time, end_time;

    //initialize random number generator
    srand((unsigned)time(NULL));

    //initialize the array using random numbers
    myArray = (int*)malloc(length*sizeof(int));
    for (i = 0; i < length; i++) {
        myArray[i] = rand() % 100;
    }

    start_time = omp_get_wtime();
    omp_set_num_threads(8);
    #pragma omp parallel shared(myArray, length) private(i)                     reduction(+:count)
        for (i = 0; i < length; i++) {
            if (myArray[i] == 99)
                count++;
        }
    end_time = omp_get_wtime();

    printf ("The OpenMP code indicates that there are %d 99s in the array. \n\n", count);
    printf ("The OpenMP code used %f seconds to complete the execution. \n\n", end_time - start_time);

    return 0;
}
