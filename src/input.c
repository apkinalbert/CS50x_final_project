#include "../include/input.h"
#include <stdio.h>


int get_input(char *buffer, size_t size) {
    printf("> ");
    if (fgets(buffer, size, stdin) == NULL) {
        return 0;
    }
    return 1;
}
