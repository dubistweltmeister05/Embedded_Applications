#include <stdio.h>
#include <stdatomic.h>
#include <pthread.h>
#include <unistd.h>

atomic_flag lock = ATOMIC_FLAG_INIT;  // Spinlock

void spin_lock(atomic_flag *lock) {
    while (atomic_flag_test_and_set(lock)) {
        // busy-wait (spin)
    }
}

void spin_unlock(atomic_flag *lock) {
    atomic_flag_clear(lock);
}

void *worker(void *arg) {
    int id = *(int *)arg;
    spin_lock(&lock);
    printf("Thread %d acquired lock\n", id);
    sleep(1);
    printf("Thread %d releasing lock\n", id);
    spin_unlock(&lock);
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    pthread_create(&t1, NULL, worker, &id1);
    pthread_create(&t2, NULL, worker, &id2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
