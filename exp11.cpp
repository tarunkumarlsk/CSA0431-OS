#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h> 

// Function that will be executed by the thread
void *myThreadFun(void *vargp) {
    sleep(1); // Sleep for 1 second
    printf("Printing GeeksQuiz from Thread \n"); 
    return NULL; 
} 

int main() {
    pthread_t thread_id; // Declare a thread identifier
    printf("Before Thread\n");

    // Create a new thread that will execute myThreadFun
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    
    // Wait for the thread to finish its execution
    pthread_join(thread_id, NULL); 

    printf("After Thread\n");
    exit(0); 
}
