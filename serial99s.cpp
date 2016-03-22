/*********************************************************************
 *  This is the serial code provided by the program specifications
 ********************************************************************/

#include <omp.h>
#include <iostream>
#include <ctime>
using namespace std;

int main() {
    int count = 0, i;
    int const size = 100000;
    int myArray[size];
    double start_time, end_time;

    //initialize random number generator
    srand((unsigned)time(NULL));

    //initialize the array using random numbers
    for (i = 0; i < size; i++) {
        myArray[i] = rand() % 100;
    }

    //serial code
    start_time = omp_get_wtime();
    for (i = 0; i < size; i++) {
        if (myArray[i] == 99)
            count++;
    }
    end_time = omp_get_wtime();

    printf ("The serial code indicates that there are %d 99s in the array. \n\n", count);
    printf ("The serial code used %f seconds to complete the execution. \n\n", end_time - start_time);

    return 0;
}
