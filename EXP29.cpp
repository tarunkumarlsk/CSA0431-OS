#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0, count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = rand() % 100;  // Simulate producing an item
        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&empty, &mutex);
        }

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        printf("Produced: %d\n", item);

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);

        while (count == 0) {
            pthread_cond_wait(&full, &mutex);
        }

        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;

        printf("Consumed: %d\n", item);

        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize random number generator
    srand(time(NULL));

    if (pthread_create(&producer_thread, NULL, producer, NULL) != 0) {
        perror("Failed to create producer thread");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&consumer_thread, NULL, consumer, NULL) != 0) {
        perror("Failed to create consumer thread");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(producer_thread, NULL) != 0) {
        perror("Failed to join producer thread");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(consumer_thread, NULL) != 0) {
        perror("Failed to join consumer thread");
        exit(EXIT_FAILURE);
    }

    return 0;
}
