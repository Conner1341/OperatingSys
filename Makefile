#makefile for pNines.c
#testing for howmany99s - using pthreads
CC=gcc
TARGET=nines
SRC=pNines.c
OBJ=pNines.o
FLAGS=-Wall -fopenmp -g -lpthread

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(TARGET)

clean:
	rm -r $(TARGET)
