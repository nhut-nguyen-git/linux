#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define ARRAY_SIZE 100

int numbers[ARRAY_SIZE];  // Global array with 100 integers
int evenCount = 0, oddCount = 0; // Shared counters

// Function for even counter thread
void *countEvens(void *arg) {
    int localEvenCount = 0; // Local variable to avoid race conditions
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (numbers[i] % 2 == 0) {
            localEvenCount++;
        }
    }
    evenCount = localEvenCount;
    pthread_exit(NULL);
}

// Function for odd counter thread
void *countOdds(void *arg) {
    int localOddCount = 0; // Local variable to avoid race conditions
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (numbers[i] % 2 != 0) {
            localOddCount++;
        }
    }
    oddCount = localOddCount;
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    // Generate random numbers (1 to 100)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        numbers[i] = rand() % 100 + 1;
    }

    pthread_t evenThread, oddThread;

    // Create threads
    pthread_create(&evenThread, NULL, countEvens, NULL);
    pthread_create(&oddThread, NULL, countOdds, NULL);

    // Wait for threads to complete
    pthread_join(evenThread, NULL);
    pthread_join(oddThread, NULL);

    // Print results
    printf("Total Even Numbers: %d\n", evenCount);
    printf("Total Odd Numbers: %d\n", oddCount);

    return 0;
}