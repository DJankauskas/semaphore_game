#include "utils.h"

int main() {
    int sem = wait_for_sem();

    int shared = shmget(KEY, 256, 0);
    if(shared < 0) {
        fprintf(stderr, "Unable to get shared mem: %s\n", strerror(errno));
        return 1;
    }

    size_t *mem = shmat(shared, 0, 0);

    if(!mem) {
        fprintf(stderr, "Failed to shmat: %s\n", strerror(errno));
        exit(1);
    }

    int fd = open("story", O_RDONLY);
    if(fd < 0) {
        fprintf(stderr, "Unable to open file: %s\n", strerror(errno));
        return 1;
    }


    if(lseek(fd, (ssize_t)*mem * -1, SEEK_END) < 0) {
        printf("Failed to seek file: %s\n", strerror(errno));
        return 1;
    }

    char *last_line = malloc(*mem);
    read(fd, last_line, *mem);
    printf("%s\n", last_line);

    printf("Your addition: ");

    size_t input_size = 500;
    char *input = malloc(input_size);
    size_t size = getline(&input, &input_size, stdin);

    fd = open("story", O_WRONLY | O_APPEND);
    write(fd, input, size);

    *mem = size;

    relinquish_sem(sem);
    return 0;
}