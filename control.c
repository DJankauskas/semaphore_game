#include <stdio.h>
#include <string.h>

#include "options.h"

int main(int argc, char** argv) {
    if(argc != 2) {
        fprintf(stderr, "Expected one argument.\n");
        return 1;
    }

    if(strcmp(argv[1], "-c") == 0) {
        create();
    }
    else if(strcmp(argv[1], "-v") == 0) {
        view();
    }
    else if(strcmp(argv[1], "-r") == 0) {
        rem();
    }
    else {
        fprintf(stderr, "Expected -c for resource creation, -v to output the story, "
        "or -r to remove resources, exclusive.\n");
        return 1;
    }
    return 0;
}