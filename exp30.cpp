#include <stdio.h>
#include <pthread.h>
#include <stdint.h> // For intptr_t

#define NUM_THREADS 3

void *thread_function(void *thread_id) {
    intptr_t tid = (intptr_t)thread_id; // Use intptr_t to avoid precision loss
    printf("Thread %ld created.\n", (long)tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int i;

    for (i = 0; i < NUM_THREADS; i++) {
        // Use intptr_t for casting pointer to integer
        if (pthread_create(&threads[i], NULL, thread_function, (void *)(intptr_t)(i + 1)) != 0) {
            perror("Failed to create thread");
            return 1; // Exit with an error code
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1; // Exit with an error code
        }
        printf("Thread %d terminated.\n", i + 1);
    }

    return 0;
}
