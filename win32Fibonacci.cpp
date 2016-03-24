/***************************************************************************
* name: Conner Herriges
* course: CS 4328 - Operating Systems
* project: Project1, part1b
*      This program generates the Fibonacci sequence using Win32 threads
* status: complete
**************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

#define SIZE 500

int* sequence = new int[SIZE];
DWORD WINAPI Fibonacci(LPVOID Param);

int main() {
	DWORD ThreadId;
	HANDLE ThreadHandle;
	int generate;
	int index;

	printf("Enter the number of Fibonacci numbers to generate: ");
	scanf_s("%d", &generate);

	/* create the thread */
	ThreadHandle = CreateThread(
		NULL,       /* default security attribute */
		0,          /* default stack size */
		Fibonacci,  /* thread function */
		&generate,  /* parameter to thread function */
		0,          /* default creation flags */
		&ThreadId); /* returns the thread identifier */


	/* now wait for the thread to finish */
	WaitForSingleObject(ThreadHandle, INFINITE);

	printf("The Fibonacci sequence for %d digits is:\n", generate);
	for (index = 0; index < generate; index++) {
		printf("%d ", sequence[index]);
	}
	printf("\n");

	/* close the thread handle and exit */
	CloseHandle(ThreadHandle);
	return 0;
}

/* the thread runs in this separate function */
DWORD WINAPI Fibonacci(LPVOID Param) {
	DWORD Upper = *(DWORD*)Param;  /* cast parameter to DWORD */
	DWORD num, fib1 = 0, fib2 = 1;    /* fib1 = (n-2), fib2 = (n-1) */
	unsigned int count;

	for (count = 0; count < Upper; count++) {
		if (count <= 1)
			num = count;
		else {
			num = fib1 + fib2;
			fib1 = fib2;
			fib2 = num;
		}
		sequence[count] = num;
	}
	return NULL;
}
