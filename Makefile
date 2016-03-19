#makefile for nines.c
#testing for howmany99s
CC=gcc
TARGET=nines
SRC=nines.c
OBJ=nines.o
FLAGS=-Wall -fopenmp -g -lpthread

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(TARGET)

clean:
	rm -r $(TARGET)
