#include "../include/parser.h"


int parse_input(char *input, char **argv, int *count) {
    if (input == NULL || argv == NULL) {
        fprintf(stderr, "Invalid input or arguments.\n");
        return PARSE_ERR;
    }

    if (strlen(input) == 0) {
        fprintf(stderr, "No command entered.\n");
        return PARSE_ERR;
    }

    // Tokenize the input string
    int argc = 0;
    char *token = strtok(input, " \t\n");
    while (token != NULL && argc < MAX_ARGC - 1) {
        argv[argc++] = token;
        token = strtok(NULL, " \t\n");
    }

    // Check for too many arguments or no command
    if (argc == MAX_ARGC - 1 && token != NULL) {
        fprintf(stderr, "Too many arguments, maximum is %d.\n", MAX_ARGC - 1);
        return PARSE_ERR;
    }

    // If no command was entered
    if (argc == 0) {
        fprintf(stderr, "No command entered.\n");
        return PARSE_ERR;
    }
    // Null-terminate the argument list
    argv[argc] = NULL;
    *count = argc;

    return PARSE_OK;
}
