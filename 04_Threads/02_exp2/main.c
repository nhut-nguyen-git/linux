#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_COUNT 3
#define INCREMENT_TIMES 1000000

pthread_mutex_t counterMutex;  // Mutex for thread synchronization
long counter = 0;  // Shared global variable

// Function executed by each thread
void *incrementCounter(void *arg) {
    for (long i = 0; i < INCREMENT_TIMES; i++) {
        pthread_mutex_lock(&counterMutex);  // Lock before modifying counter
        counter++;
        pthread_mutex_unlock(&counterMutex);  // Unlock after modification
    }
    return NULL;
}

int main() {
    pthread_t threads[THREAD_COUNT];
    pthread_mutex_init(&counterMutex, NULL);  // Initialize mutex

    // Create threads
    for (int i = 0; i < THREAD_COUNT; i++) {
        if (pthread_create(&threads[i], NULL, incrementCounter, NULL) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Wait for threads to complete
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&counterMutex);  // Destroy mutex after use
    printf("Final counter value: %ld\n", counter);
    return EXIT_SUCCESS;
}