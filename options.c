#include "options.h"
#include "utils.h"

//handles -c
void create() 
{
    int sem = semget(KEY, 1, 0666 | IPC_CREAT);
    if(sem < 0) {
        fprintf(stderr, "Error creating semaphore: %s\n", strerror(errno));
    }
    union semun arg = {.val = 1};
    if(semctl(sem, 0, SETVAL, arg) < 0) {
        fprintf(stderr, "Error initializing semaphore: %s\n", strerror(errno));
    }
    printf("Semaphore created.\n");

    int shared = shmget(KEY, 256, IPC_CREAT | IPC_EXCL | 0666);
    if(shared < 0) {
        fprintf(stderr, "Error creating shared memory: %s\n", strerror(errno));
        return;
    }

    size_t *mem = shmat(shared, 0, 0);
    *mem = 0;

    printf("Shared memory created.\n");

    if(open("./story", O_CREAT | O_EXCL | O_TRUNC, 0666) < 0) {
        fprintf(stderr, "Error creating file: %s\n", strerror(errno));
        return;
    }
    printf("File created.\n");
}

//handles -r
void rem() 
{
    int sem = wait_for_sem();

    printf("The story:\n");
    print_file("./story");
    printf("\n");

    if (semctl(sem, 0, IPC_RMID) < 0) {
        fprintf(stderr, "Failed to remove semaphore: %s\n", strerror(errno));
        exit(1);
    }
    printf("Removed semaphore.\n");

    int shared = shmget(KEY, 0, 0);
    if (shared < 0) {
        fprintf(stderr, "Failed to get shared memory: %s\n", strerror(errno));
        exit(1);
    }
    if (shmctl(shared, 0, IPC_RMID) < 0) {
        fprintf(stderr, "Failed to remove shared memory: %s\n", strerror(errno));
        exit(1);
    }
    printf("Removed shared memory.\n");

    if(remove("story") < 0) {
        fprintf(stderr, "Failed to delete file: %s\n", strerror(errno));
        exit(1);
    }
    printf("Removed file.\n");
}

//handles -v
void view() {
    printf("The story so far: \n");
    print_file("story");
    printf("\n");
}
