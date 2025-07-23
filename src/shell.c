#include "../include/shell.h"
#include "../include/parser.h"
#include "../include/input.h"

int shell() {
    printf("Welcome to the shell!\n");
    printf("Type 'help' for a list of commands.\n");
    printf("Type 'exit' to exit the shell.\n");
    char input[MAX_INPUT_SIZE];
    char *argv[MAX_ARGC];
    int argc = 0;
    while (1) {

        if (!get_input(input, sizeof(input))) {
            fprintf(stderr, "Error reading input.\n");
            return EXIT_FAILURE;
        }

        int status = parse_input(input, argv, &argc);
        if (status != PARSE_OK) {
            continue; // Prompt for input again
        }

        // Execute the command
        status = execute_command(argv, argc);
        if (status == EXIT_SHELL) {
            break; // Exit the shell
        }
    }

    return EXIT_SUCCESS;
}

int execute_command(char **argv, int argc) {
    if (strcmp(argv[0], "exit") == 0) {
        return EXIT_SHELL;
    }
    if (strcmp(argv[0], "help") == 0) {
        printf("Available commands:\n");
        printf("  exit - Exit the shell\n");
        printf("  help - Show this help message\n");
        printf("  cd <directory> - Change directory\n");
        printf("  ls - List files in the current directory\n");
        return EXIT_SUCCESS;
    }
    if (strcmp(argv[0], "cd") == 0) {
        if (argc < 2) {
            fprintf(stderr, "Usage: cd <directory>\n");
            return EXIT_FAILURE;
        }
        if (chdir(argv[1]) != 0) {
            perror("chdir failed");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execvp(argv[0], argv);
        perror("execvp failed");
        _exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }

    return EXIT_SUCCESS;
}
