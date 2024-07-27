#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h>
#include <unistd.h>

// Semaphores to control access to the room and chopsticks
sem_t room;
sem_t chopstick[5];

// Function prototypes
void *philosopher(void *num);
void eat(int phil);

int main() {
    int i, a[5];
    pthread_t tid[5];

    // Initialize the room semaphore to allow 4 philosophers at a time
    sem_init(&room, 0, 4);

    // Initialize the chopstick semaphores, one for each chopstick
    for(i = 0; i < 5; i++) 
        sem_init(&chopstick[i], 0, 1);

    // Create philosopher threads
    for(i = 0; i < 5; i++) {
        a[i] = i;
        pthread_create(&tid[i], NULL, philosopher, (void *)&a[i]);
    }

    // Wait for all philosopher threads to finish
    for(i = 0; i < 5; i++) 
        pthread_join(tid[i], NULL);

    return 0;
}

// Philosopher thread function
void *philosopher(void *num) {
    int phil = *(int *)num;

    // Wait to enter the room
    sem_wait(&room);
    printf("\nPhilosopher %d has entered the room", phil);

    // Pick up the chopsticks
    sem_wait(&chopstick[phil]);
    sem_wait(&chopstick[(phil + 1) % 5]);

    // Eat
    eat(phil);
    sleep(2);  // Simulate eating time

    printf("\nPhilosopher %d has finished eating", phil);

    // Put down the chopsticks
    sem_post(&chopstick[(phil + 1) % 5]);
    sem_post(&chopstick[phil]);

    // Leave the room
    sem_post(&room);

    return NULL;
}

// Function to simulate eating
void eat(int phil) {
    printf("\nPhilosopher %d is eating", phil);
}
