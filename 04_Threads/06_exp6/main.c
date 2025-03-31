#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000000
#define NUM_THREADS 4

int array[ARRAY_SIZE];  // Array of integers
long long global_sum = 0;  // Global sum
pthread_mutex_t sum_mutex;  // Mutex to protect global_sum

// Function to calculate partial sum of the array
void* partial_sum(void* arg) {
    int thread_id = (int)arg;
    int start_index = (ARRAY_SIZE / NUM_THREADS) * thread_id;
    int end_index = (thread_id == NUM_THREADS - 1) ? ARRAY_SIZE : (ARRAY_SIZE / NUM_THREADS) * (thread_id + 1);

    long long partial_sum = 0;
    for (int i = start_index; i < end_index; i++) {
        partial_sum += array[i];
    }

    // Lock the mutex before updating the global sum
    pthread_mutex_lock(&sum_mutex);
    global_sum += partial_sum;
    pthread_mutex_unlock(&sum_mutex);

    return NULL;
}

int main() {
    // Initialize the array with random values
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100;  // Random numbers between 0 and 99
    }

    // Initialize mutex
    pthread_mutex_init(&sum_mutex, NULL);

    pthread_t threads[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, partial_sum, (void*)i);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the total sum
    printf("Total sum of the array: %lld", global_sum);

    // Destroy mutex
    pthread_mutex_destroy(&sum_mutex);

    return 0;
}