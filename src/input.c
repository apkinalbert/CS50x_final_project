#include "../include/input.h"
#include <stdio.h>


int get_input(char *buffer, size_t size) {
    char cwd[PATH_MAX];
    get_last_two_dirs(cwd);
    printf("[mysh] %s > ", cwd);
    if (fgets(buffer, size, stdin) == NULL) {
        return 0;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        clear_stdin(); 
    }
    return 1;
}

void get_last_two_dirs(char *buf) {
    if (getcwd(buf, PATH_MAX) == NULL) {
        perror("getcwd failed");
    }
    char *last_slash = strrchr(buf, '/');
    if (last_slash == NULL) {
        return;
    }


    *last_slash = '\0'; 
    char *second_last_slash = strrchr(buf, '/');
    *last_slash = '/'; 

    if (second_last_slash == NULL)
        return; 
    else
        memmove(buf, second_last_slash, strlen(second_last_slash) + 1);
}

void clear_stdin() {
    int c;
    int count = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        count++;
    }
    if (count > 0) {
        fprintf(stderr, "Input too long, clearing stdin buffer.\n");
    }
}