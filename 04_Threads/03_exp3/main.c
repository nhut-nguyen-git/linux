#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>  // For sleep()
#include <time.h>

#define ITERATIONS 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int data = 0;
int dataAvailable = 0; // Flag to track data readiness

// Producer function
void *producer(void *arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        sleep(1); // Simulate work
        pthread_mutex_lock(&mutex);
        data = rand() % 10 + 1; // Generate a random number between 1 and 10
        dataAvailable = 1;
        printf("Producer: Generated data %d\n", data);
        pthread_cond_signal(&cond); // Notify consumer that data is ready
        pthread_mutex_unlock(&mutex); // Unlock the mutex to allow consumer access
    }
    return NULL;
}

// Consumer function
void *consumer(void *arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);
        while (!dataAvailable) {
            pthread_cond_wait(&cond, &mutex); // Wait until producer signals data availability
        }
        printf("Consumer: Read data %d\n", data);
        dataAvailable = 0; // Reset flag to indicate data has been consumed
        pthread_mutex_unlock(&mutex); // Unlock the mutex to allow producer to generate new data
    }
    return NULL;
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    pthread_t producerThread, consumerThread;
    
    pthread_create(&producerThread, NULL, producer, NULL); // Create producer thread
    pthread_create(&consumerThread, NULL, consumer, NULL); // Create consumer thread
    
    pthread_join(producerThread, NULL); // Wait for producer thread to finish
    pthread_join(consumerThread, NULL); // Wait for consumer thread to finish
    
    pthread_mutex_destroy(&mutex); // Clean up mutex
    pthread_cond_destroy(&cond); // Clean up condition variable
    
    return 0;
}