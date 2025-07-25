#include "../include/input.h"

#include <stdio.h>

int get_input(char *buffer, size_t size) {
	char cwd[PATH_MAX];
	get_last_two_dirs(cwd);
	char prompt[PATH_MAX + 32];
	snprintf(prompt, sizeof(prompt), "[mysh] %s > ", cwd);
	char *input = readline(prompt);
	if (input == NULL) {
		return 0;  // EOF (Ctrl+D)
	}
	if (*input != '\0') {
		add_history(input);
	}
	strncpy(buffer, input, size - 1);
	buffer[size - 1] = '\0';

	free(input);
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
