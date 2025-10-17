// main.c
#include <stdio.h>
#include "globals.h"

int main(void) {
    printf("[main.c] initial shared_counter = %d\n", shared_counter);

    /* modify the external variable directly */
    shared_counter += 5;
    printf("[main.c] after +5, shared_counter = %d\n", shared_counter);

    /* call function from globals.c that also modifies it */
    increment_shared();

    return 0;
}
