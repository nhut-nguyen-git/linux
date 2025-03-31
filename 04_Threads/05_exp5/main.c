#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>  // For sleep()

#define READERS 5
#define WRITERS 2

int data = 0; // Shared data variable
pthread_rwlock_t rwlock;

// Reader thread function
void *reader(void *arg) {
    int thread_id = *(int *)arg;
    free(arg);
    pthread_rwlock_rdlock(&rwlock);
    printf("Reader %d: Read data = %d\n", thread_id, data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

// Writer thread function
void *writer(void *arg) {
    int thread_id = *(int *)arg;
    free(arg);
    pthread_rwlock_wrlock(&rwlock);
    data++;
    printf("Writer %d: Incremented data to %d\n", thread_id, data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

int main() {
    pthread_t reader_threads[READERS], writer_threads[WRITERS];
    pthread_rwlock_init(&rwlock, NULL);

    // Create reader threads
    for (int i = 0; i < READERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, id);
    }

    // Create writer threads
    for (int i = 0; i < WRITERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&writer_threads[i], NULL, writer, id);
    }

    // Wait for all threads to finish
    for (int i = 0; i < READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }
    for (int i = 0; i < WRITERS; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);

    printf("Final data value: %d\n", data);
    return 0;
}