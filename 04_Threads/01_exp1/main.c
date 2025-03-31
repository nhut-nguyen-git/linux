#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_COUNT 2  // Number of threads to create

// Function executed by each thread
void *threadTask(void *arg) {
    long threadId = (long)arg;
    printf("Thread %ld: Hello from thread!\n", threadId);
    pthread_exit(NULL);
}

int main() {
    pthread_t threadHandles[THREAD_COUNT];  // Array to store thread handles
    int threadStatus;
    long threadIndex;

    // Create threads
    for (threadIndex = 0; threadIndex < THREAD_COUNT; threadIndex++) {
        threadStatus = pthread_create(&threadHandles[threadIndex], NULL, threadTask, (void *)threadIndex);
        if (threadStatus != 0) {
            fprintf(stderr, "Error creating thread %ld, error code: %d\n", threadIndex, threadStatus);
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to complete
    for (threadIndex = 0; threadIndex < THREAD_COUNT; threadIndex++) {
        threadStatus = pthread_join(threadHandles[threadIndex], NULL);
        if (threadStatus != 0) {
            fprintf(stderr, "Error joining thread %ld, error code: %d\n", threadIndex, threadStatus);
            exit(EXIT_FAILURE);
        }
    }

    printf("All threads have completed execution.\n");
    return EXIT_SUCCESS;
}