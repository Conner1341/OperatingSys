# OperatingSys
project 1 for CS4328 - Operating Systems

Part1: Implement Fibonacci Sequence using Pthreads and Win32 threads
Part 1a: is a multithreaded program that generates the Fibonacci sequence using Pthreads. It asks the user to enter the number of Fibonacci numbers that the program will generate.

        It can be compiled with the following:
            gcc -g -Wall -lpthread fibonacci.c -o fibonacci
        and then executed with:
            ./fibonacci

Part 1b: is a multithreaded program same as part 1a, but using Win32 threads.
        It was built in Visual Studio 2015 and run with the "Start without debugging" option.

Part2: Implement Matrix Multiplication using Pthreads
Part 2a: This program uses Pthreads to multiply two matrices, A and B, where matrix A contains M rows and K columns, and matrix B contains K rows and N columns. The product of A and B is another matrix, C. Each element, Cij, is calculated in a separate worker thread.

        It can be compiled with the following:
            gcc -g -Wall -lpthread matrixmult.c -o matrix
        and then executed with:
            ./matrix

Part3: How many 99s (Pthreads and OpenMP)
Part3a: This program uses OpenMP to count the number of times '99' appears in a
        randomly generated array. It also records the execution time of the code. The number of threads the program runs on can be changed by changing the value of set_omp_threads() on line 33

        It can be compiled with the following:
            gcc -g -Wall -fopenmp ompNines.c -o nines
        and the executed with:
            ./nines

Part3b: This program is the same as in part 3a, but uses Pthreads instead.
        The number of threads the program runs on can be changed by changing
            the value of NUM_THREADS

        It can be compiled with:
            gcc -g -Wall -lpthread pNines.c -o nines
        and executed with:
            ./nines
