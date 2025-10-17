// globals.c
#include "globals.h"
#include <stdio.h>

/* Definition of the external variable (storage allocated here) */
int shared_counter = 0;

/* Function that updates the shared variable */
void increment_shared(void) {
    shared_counter++;
    printf("[globals.c] shared_counter now = %d\n", shared_counter);
}
