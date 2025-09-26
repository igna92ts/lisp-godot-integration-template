#define API_BUILD
#include "simwrap.h"

#include <stdio.h>
#include <stdlib.h>

extern int initialize_lisp(int argc, char **argv);

int  (*simstart)(void);
void (*simstop)(void);

int init_sim() {
    static int initialized = 0;
    char *argv[] = {"", "--core", "lisp/sim.core", "--noinform", NULL};

    if (initialized) return 0;
    if (initialize_lisp(4, argv) != 0) {
        fprintf(stderr, "Failed to initialize Lisp runtime\n");
        return -1;
    }

    printf("Sim started\n");
    initialized = 1;
    return 0;
}

int start_simulation() {
  simstart();
    // if (simstart() != 0) {
    //     fprintf(stderr, "Failed to start simulation\n");
    //     return -1;
    // }
  return 0;
}

void stop_simulation() {
  simstop();
}
