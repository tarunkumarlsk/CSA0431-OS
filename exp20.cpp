#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Semaphores and shared variables
sem_t mutex, writeBlock;
int data = 0, readersCount = 0;

void *reader(void *arg) {
    int i = 0;
    while (i < 10) {
        sem_wait(&mutex);
        readersCount++;
        if (readersCount == 1) {
            sem_wait(&writeBlock);
        }
        sem_post(&mutex);

        // Reading data
        printf("Reader reads data: %d\n", data);

        sem_wait(&mutex);
        readersCount--;
        if (readersCount == 0) {
            sem_post(&writeBlock);
        }
        sem_post(&mutex);

        i++;
    }
    return NULL;
}

void *writer(void *arg) {
    int i = 0;
    while (i < 10) {
        sem_wait(&writeBlock);

        // Writing data
        data++;
        printf("Writer writes data: %d\n", data);

        sem_post(&writeBlock);

        i++;
    }
    return NULL;
}

int main() {
    pthread_t readers, writers;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);

    // Create reader and writer threads
    pthread_create(&readers, NULL, reader, NULL);
    pthread_create(&writers, NULL, writer, NULL);

    // Wait for the threads to finish
    pthread_join(readers, NULL);
    pthread_join(writers, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&writeBlock);

    return 0;
}
