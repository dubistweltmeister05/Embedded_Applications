#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>

void *thread_func(void *arg) {
    int thread_num = *(int *)arg;
    printf("Thread %d started with scheduling policy and priority\n", thread_num);

    struct sched_param param;
    int policy;
    pthread_getschedparam(pthread_self(), &policy, &param);

    const char *policy_name =
        (policy == SCHED_FIFO)  ? "SCHED_FIFO"  :
        (policy == SCHED_RR)    ? "SCHED_RR"    :
        (policy == SCHED_OTHER) ? "SCHED_OTHER" : "UNKNOWN";

    for (int i = 0; i < 5; i++) {
        printf("Thread %d running [%s, priority=%d]\n", thread_num, policy_name, param.sched_priority);
        usleep(100000); // sleep 0.1 sec to simulate work
    }

    printf("Thread %d finished\n", thread_num);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_attr_t attr1, attr2;
    struct sched_param param1, param2;
    int ret;

    // Initialize attributes
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    // Set scheduling policy to SCHED_RR (Round Robin)
    pthread_attr_setschedpolicy(&attr1, SCHED_RR);
    pthread_attr_setschedpolicy(&attr2, SCHED_RR);

    // Make attributes explicit (not inherited)
    pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);

    // Set priorities
    param1.sched_priority = 30;
    param2.sched_priority = 40;

    pthread_attr_setschedparam(&attr1, &param1);
    pthread_attr_setschedparam(&attr2, &param2);

    int id1 = 1, id2 = 2;

    printf("Creating threads with different priorities...\n");

    ret = pthread_create(&t1, &attr1, thread_func, &id1);
    if (ret != 0) perror("pthread_create t1");

    ret = pthread_create(&t2, &attr2, thread_func, &id2);
    if (ret != 0) perror("pthread_create t2");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_attr_destroy(&attr1);
    pthread_attr_destroy(&attr2);

    printf("All threads completed.\n");
    return 0;
}
