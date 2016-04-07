#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define DIVISOR 10000
#define TRUE 1
#define BUF_SIZE 10

typedef int buf_item;

pthread_mutex_t mutex;
sem_t full, empty;
buf_item buffer[BUF_SIZE];
int counter;
pthread_t tid;
pthread_attr_t attr;

void *producer(void *param);
void *consumer(void *param);
int insert_item(buf_item item);
int remove_item(buf_item *item);


/* initializer function */
void initializeData() {
    /* create mutex lock */
    pthread_mutex_init(&mutex, NULL);

    /* create and initialize full semaphore */
    sem_init(&full, 0, 0);

    /* create and initialize empty semaphore */
    sem_init(&empty, 0, BUF_SIZE);

    /* default thread attributes */
    pthread_attr_init(&attr);

    /* buffer counter */
    counter = 0;
}

/* Producer */
void *producer(void *param) {

    buf_item item;

    while(TRUE) {
        /* slep for random period of time */
        int rand_num = rand() / DIVISOR;
        sleep(rand_num);

        /* generate a random number */
        item = rand();

        /* get empty lock */
        sem_wait(&empty);

        /* acquire mutex lock */
        pthread_mutex_lock(&mutex);

        if(insert_item(item)) {
            fprintf(stderr, "producer report error condition\n");
        }
        else {
            printf("producer %d\n", item);
        }

        /* release mutex lock */
        pthread_mutex_unlock(&mutex);

        /* signal full */
        sem_post(&full);
    }
} //end producer

/* Consumer */
void *consumer(void *param) {
    buf_item item;

    while(TRUE) {
        /* sleep for radom amount of time */
        int rand_num = rand() / DIVISOR;
        sleep(rand_num);

        /* acquire full lock */
        sem_wait(&full);

        /* acquire mutex lock */
        pthread_mutex_lock(&mutex);
        if(remove_item(&item)) {
            fprintf(stderr, "consumer report error condition\n");
        }
        else {
            printf("consumer %d\n", item);
        }

        /* release mutex lock */
        pthread_mutex_unlock(&mutex);

        /* signal empty */
        sem_post(&empty);
    }
}

/* add an item to the buffer */
int insert_item(buf_item item) {
    /* when buffer is not full, add item and increment counter */
    if(counter < BUF_SIZE) {
        buffer[counter] = item;
        counter++;
        exit(EXIT_SUCCESS);
    }
    else {
        exit(EXIT_FAILURE);  /* buffer is full */
    }
}

/* remove an item from the buffer */
int remove_item(buf_item *item) {
    /* when buffer is not empty, remove item and decrement counter */
    if(counter > 0) {
        *item = buffer[(counter - 1)];
        counter--;
        exit(EXIT_SUCCESS);
    }
    else {
        exit(EXIT_FAILURE);  /* buffer is empty */
    }
}

int main (int argc, char *argv[]) {

    if (argc != 4) {
        fprintf(stderr, "too few arguments\n");
    }

    int sleepTime = atoi(argv[1]);     /* time to sleep before terminating */
    int numProducers = atoi(argv[2]);  /* number of producer threads */
    int numConsumers = atoi(argv[3]);  /* number of consumer threads */
    int index;

    /* initialize buffer */
    initializeData();

    /* create producer threads */
    for(index = 0; index < numProducers; index++) {
        pthread_create(&tid, &attr, producer, NULL);
    }

    /* create consumer threads */
    for(index = 0; index < numConsumers; index++) {
        pthread_create(&tid, &attr, consumer, NULL);
    }

    /* sleep */
    sleep(sleepTime);

    /* terminate program on awakening */
    printf("exiting program\n");
    exit(EXIT_SUCCESS);
}
