#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10
#define NUM_THREADS 4

int shared_array[ARRAY_SIZE];     // shared memory (global array)
pthread_mutex_t lock;             // mutex for synchronization

void *worker(void *arg) {
    int id = *(int *)arg;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        pthread_mutex_lock(&lock);              // lock critical section
        shared_array[i] += id;                  // modify shared memory
        printf("Thread %d updated index %d -> %d\n", id, i, shared_array[i]);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    // Initialize shared array and mutex
    for (int i = 0; i < ARRAY_SIZE; i++)
        shared_array[i] = 0;
    pthread_mutex_init(&lock, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, worker, &ids[i]);
    }

    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&lock);

    printf("\nFinal shared array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++)
        printf("%d ", shared_array[i]);
    printf("\n");

    return 0;
}
