#include "utils.h"

int wait_for_sem()
{
    int id = semget(KEY, 1, 0);
    if(id < 0) {
        fprintf(stderr, "Unable to find semaphore.\n");
        exit(1);
    }
    while (semctl(id, 0, GETVAL) == 0) {
        ;
    }

    union semun arg;
    arg.val = 0;
    semctl(id, 0, SETVAL, arg);

    return id;
}

void relinquish_sem(int id) {
    union semun arg;
    arg.val = 1;
    semctl(id, 0, SETVAL, arg);
}

void print_file(char* path) {
    FILE *file = fopen(path, "r");
    if(!file) {
        fprintf(stderr, "Unable to open file %s.\n", path);
        exit(1);
    }

    char c;

    while((c = getc(file)) != EOF) {
        putc(c, stdout);
    }
    fclose(file);
}